// Observational GOG 2.2.301 probe. Run with capture_daywrecker_lifecycle.py.
// Never invoke engine functions, change arguments/state, or infer map lookup results.
'use strict';
const mod = Process.getModuleByName('battlezone98redux.exe');
if (Process.arch !== 'ia32' || !mod.base.equals(ptr('0x400000')))
    throw new Error('This probe requires the qualified x86 image at 0x400000');
const sites = [
    ['ctor', 0x004b0420, '558bec51894dfc8b'],
    ['sim', 0x004b0460, '558bec83ec4ca100'],
    ['explode', 0x004b07d0, '558bec83ec4ca100'],
    ['collision', 0x004b0610, '558bec83ec2ca100'],
    ['remove', 0x004dae70, '558bec83ec38894d'],
    ['destroy', 0x004b7bd0, '558bec83ec485389'],
    ['dtor', 0x004b79f0, '558bec83ec24894d'],
    ['set_remote', 0x004b7f20, '558bec83ec20894d'],
    ['set_local', 0x004b8460, '558bec83ec14894d'],
    ['ordinary_rx', 0x004b8590, '558bec81ec600100'],
    ['permanent_rx', 0x004b8fa0, '558bec83ec68568d'],
    ['create', 0x004b9350, '558bec6aff684f9a'],
    ['crater', 0x007809d0, '558bec83ec30833d'],
    ['explosion_build', 0x004cb7b0, '558bec83ec10894d'],
    ['armory_finish', 0x004732c0, '558bec83ec08894d'],
    ['lobber_sim', 0x00582190, '558bec81ec8c0200'],
    ['object_build', 0x004e1190, '558bec81ec180100'],
];
// Validate everything before installing anything. Existing shim detours fail closed.
for (const [name, address, expected] of sites) {
    const actual = Array.from(new Uint8Array(ptr(address).readByteArray(expected.length / 2)))
        .map(b => b.toString(16).padStart(2, '0')).join('');
    if (actual !== expected) throw new Error(name + ' entry-byte mismatch: ' + actual);
}
function safe(fn) { try { return fn(); } catch (_) { return null; } }
function hx(p) { return p === null ? null : ptr(p).toString(); }
function u32(p) { return safe(() => p.readU32()); }
function u8(p) { return safe(() => p.readU8()); }
function pp(p) { return safe(() => p.readPointer()); }
function f32(p) { return safe(() => p.readFloat()); }
function pos(p) { return [0, 4, 8].map(o => f32(p.add(o))); }
const live = new Map(); // pointer -> constructor generation, even on allocator reuse
let generation = 0;
let invocation = 0;
let seq = 0;
let budget = 20000;
const scopes = new Map();
function stack(tid) { if (!scopes.has(tid)) scopes.set(tid, []); return scopes.get(tid); }
function current(tid, kind) { return stack(tid).slice().reverse().find(s => s.kind === kind); }
function emit(event, fields) {
    if (budget-- > 0) send(Object.assign({event, seq: ++seq, pid: Process.id,
        utc: new Date().toISOString()}, fields));
    else if (budget === -1) send({event: 'budget_exhausted', pid: Process.id});
}
function isDw(p) { return safe(() => p.readPointer().equals(ptr('0x878508'))) === true; }
function snapshot(p) {
    const obj = pp(p.add(0xf4));
    const veh = pp(p.add(0x228));
    const type = u8(p.add(0x80));
    return {ptr: hx(p), generation: live.get(hx(p)) || null,
        id: type === 1 || type === 2 ? hx(u32(p.add(0x7c))) : null,
        type, activnet_id: safe(() => p.add(0x7a).readU16()),
        consumed: u8(p.add(0x230)), position: pos(p.add(0x108)),
        object_flags: obj && !obj.isNull() ? u32(obj.add(0x14)) : null,
        vehicle_flags: veh && !veh.isNull() ? u32(veh.add(0x114)) : null};
}
function origin(tid) {
    const rx = current(tid, 'rx');
    const lobber = current(tid, 'lobber');
    return {receive: rx || null, lobber: lobber || null};
}
function attach(name, callbacks) {
    const site = sites.find(s => s[0] === name);
    Interceptor.attach(ptr(site[1]), callbacks);
}
attach('ctor', {
    onEnter() { this.p = this.context.ecx; this.origin = origin(this.threadId);
        this.caller = hx(this.returnAddress); },
    onLeave() {
        live.set(hx(this.p), ++generation);
        emit('construct', Object.assign(snapshot(this.p), this.origin, {caller: this.caller}));
    }
});
for (const [name, adjusted] of [['sim', false], ['explode', true], ['collision', false]]) {
    attach(name, {
        onEnter(args) {
            const p = adjusted ? this.context.ecx.sub(0x18) : this.context.ecx;
            this.s = {kind: 'dw', path: name, invocation: ++invocation, ...snapshot(p)};
            stack(this.threadId).push(this.s);
            // Flying simulation is context for later effects, not a detonation event.
            if (name !== 'sim' || (this.s.vehicle_flags !== null && !(this.s.vehicle_flags & 4)))
                emit(name + '_entry', {...this.s, caller: hx(this.returnAddress),
                    dt: name === 'sim' ? f32(this.context.esp.add(4)) : null,
                    contact: name === 'collision' ? hx(args[0]) : null});
        },
        onLeave() { stack(this.threadId).pop(); }
    });
}
for (const name of ['remove', 'destroy', 'dtor']) {
    attach(name, {
        onEnter() {
            const p = this.context.ecx.sub(0x18);
            // Base destructor replaces the vtable: use known constructor lifetimes too.
            if (!isDw(p) && !live.has(hx(p))) return;
            const s = snapshot(p);
            emit(name, {...s, caller: hx(this.returnAddress)});
            if (name === 'dtor') live.delete(hx(p));
        }
    });
}
for (const name of ['set_local', 'set_remote']) {
    attach(name, {
        onEnter() { this.p = this.context.ecx.sub(0x18);
            this.dw = isDw(this.p); if (this.dw) this.before = snapshot(this.p); },
        onLeave() { if (this.dw) emit(name, {before: this.before,
            after: snapshot(this.p), ...origin(this.threadId)}); }
    });
}
for (const [name, route] of [['ordinary_rx', 'ordinary'], ['permanent_rx', 'permanent']]) {
    attach(name, {
        onEnter(args) {
            // Preserve reader context only. Each reader can process multiple records;
            // a record is sampled at Create, where the actual record pointer is known.
            stack(this.threadId).push({kind: 'rx', route, sender: args[0].toUInt32() & 0xffff,
                packet_time: route === 'ordinary' ? f32(this.context.esp.add(16)) : null});
        },
        onLeave() { stack(this.threadId).pop(); }
    });
}
attach('create', {
    onEnter(args) {
        const p = args[1];
        stack(this.threadId).push({kind: 'rx', route: current(this.threadId, 'rx')?.route || 'other',
            reader: current(this.threadId, 'rx') || null,
            wire_id: hx(u32(p.add(2))), record_size: u8(p), record_flags: u8(p.add(1)),
            record: hx(p), caller: hx(this.returnAddress)});
    },
    onLeave() { stack(this.threadId).pop(); }
});
attach('lobber_sim', {
    onEnter() {
        const p = this.context.ecx;
        const carrier = pp(p.add(0xc4));
        stack(this.threadId).push({kind: 'lobber', ptr: hx(p), carrier: hx(carrier),
            carrier_type: carrier ? u8(carrier.add(0x80)) : null,
            carrier_id: carrier ? hx(u32(carrier.add(0x7c))) : null,
            triggered: u8(p.add(0xd0))});
    },
    onLeave() { stack(this.threadId).pop(); }
});
attach('armory_finish', {
    onEnter() { emit('armory_finish', {ptr: hx(this.context.ecx), caller: hx(this.returnAddress)}); }
});
attach('object_build', {
    onEnter() { this.origin = origin(this.threadId); this.caller = hx(this.returnAddress); },
    onLeave(result) { if (!result.isNull() && isDw(result))
        emit('build_return', {...snapshot(result), ...this.origin, caller: this.caller}); }
});
for (const name of ['crater', 'explosion_build']) {
    attach(name, {
        onEnter(args) {
            const s = current(this.threadId, 'dw');
            if (!s) return;
            // Snapshot retained on entry: Remove can destroy the object before Build.
            emit(name + '_call', {...s, caller: hx(this.returnAddress),
                x: name === 'crater' ? f32(this.context.esp.add(4)) : null,
                z: name === 'crater' ? f32(this.context.esp.add(8)) : null,
                radius: name === 'crater' ? f32(this.context.esp.add(12)) : null,
                explosion_class: name === 'explosion_build' ? hx(this.context.ecx) : null});
        }
    });
}
emit('ready', {base: hx(mod.base), module_path: mod.path, sites: sites.length,
    limitation: 'Only new constructors have generations; crater call is not proof of buffer mutation or damage.'});
