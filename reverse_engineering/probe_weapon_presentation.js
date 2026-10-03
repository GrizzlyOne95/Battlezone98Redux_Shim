// GOG qualification observer. Started only by capture_weapon_presentation_live.py
// after exact disk identity and settled live-byte checks. Interceptor changes
// code temporarily; this script never changes arguments, returns, game data,
// calls native engine functions, creates renderers or enables OpenShim patches.
'use strict';

const expectedNames = [
    'WeaponCtor', 'WeaponDtor', 'SimulationPass', 'SetWeapon', 'ModelPose',
    'OrdnanceFactory', 'PopScope', 'RawGet', 'RenderFind', 'RenderUpdate',
    'RenderDetach', 'CannonShotCall', 'WeaponClassPopCall', 'CraftClassPopCall'
];
let listeners = [];
let timer = null;
let config = null;
let sites = null;
let sequence = 0;
let emitted = 0;
let readErrors = 0;
let capped = false;
let stopped = false;
let queue = [];
let step = 0;
let generation = 0;
const weapons = new Map();
const counts = {};
const threads = new Map();

function read(fn) {
    try { return fn(); }
    catch (_) { ++readErrors; return null; }
}
function pointer(p) { return p === null ? null : p.toString(); }
function at(p, offset) { return read(() => p.add(offset).readPointer()); }
function finite(n) { return Number.isFinite(n) ? n : null; }
function matrix(p) {
    if (p === null || p.isNull()) return null;
    return read(() => ({
        basis: Array.from({ length: 9 }, (_, i) => finite(p.add(i * 4).readFloat())),
        position: [40, 48, 56].map(offset => finite(p.add(offset).readDouble()))
    }));
}
function meshId(p) {
    return read(() => {
        const bytes = new Uint8Array(p.add(8).readByteArray(8));
        let result = '';
        for (const b of bytes) {
            if (b === 0) break;
            if (b < 0x20 || b > 0x7e) return null;
            result += String.fromCharCode(b);
        }
        return result;
    });
}
function slotSnapshot(slot) {
    const renderer = at(slot, 0);
    const backref = renderer !== null && !renderer.isNull() ? at(renderer, 0x68) : null;
    return { slot: pointer(slot), renderer: pointer(renderer), backref: pointer(backref),
             backref_matches: backref !== null ? backref.equals(slot) : null };
}
function weaponSnapshot(weapon) {
    return { weapon: pointer(weapon), observed_generation: weapons.get(weapon.toString()) || null,
             object_class: pointer(at(weapon, 8)), object: pointer(at(weapon, 0x10)),
             owner_root: pointer(at(weapon, 0x18)), mount_pose: matrix(weapon.add(0x28)) };
}
function flush() {
    if (queue.length) { const batch = queue; queue = []; send({ type: 'events', events: batch }); }
}
function admit(kind, threadId) {
    if (stopped) return false;
    counts[kind] = (counts[kind] || 0) + 1;
    const key = `${kind}:${threadId}`;
    if (!threads.has(key) && threads.size >= 128) { capped = true; return false; }
    threads.set(key, (threads.get(key) || 0) + 1);
    if (emitted >= config.max_events) { capped = true; return false; }
    return true;
}
function emit(kind, invocation, fields) {
    // onLeave may run after later entries used the remaining budget.
    if (stopped || emitted >= config.max_events) { capped = true; return; }
    ++emitted;
    queue.push(Object.assign({ sequence: ++sequence, kind, thread_id: invocation.threadId,
        wall_time_ms: Date.now(), simulation_step: step }, fields));
    if (queue.length >= 64) flush();
}
function hook(name, callbacks) { listeners.push(Interceptor.attach(sites[name], callbacks)); }
function normalized(path) { return path.replace(/\//g, '\\').toLowerCase(); }

function start(input) {
    if (config !== null) throw new Error('Observer is single-use');
    if (Process.platform !== 'windows' || Process.arch !== 'ia32' || Process.pointerSize !== 4 ||
        Process.id !== input.pid) throw new Error('Wrong process/platform/architecture');
    const exe = Process.mainModule;
    if (exe.name.toLowerCase() !== 'battlezone98redux.exe' ||
        normalized(exe.path) !== normalized(input.module_path) ||
        !exe.base.equals(ptr(input.image_base)) || input.image_base !== '0x400000')
        throw new Error('Wrong live executable module');
    if (Object.keys(input.sites).sort().join() !== expectedNames.slice().sort().join() ||
        input.guards.length !== 14 || !Number.isInteger(input.max_events) ||
        input.max_events < 1 || input.max_events > 20000 || !Array.isArray(input.model_ids) ||
        input.model_ids.length > 16 || input.model_ids.some(n => !/^[\x20-\x7e]{1,8}$/.test(n)))
        throw new Error('Incomplete or invalid observer configuration');
    const end = exe.base.add(exe.size);
    const addresses = new Set();
    for (const name of expectedNames) {
        const p = ptr(input.sites[name]);
        if (p.compare(exe.base) < 0 || p.compare(end) >= 0 || addresses.has(p.toString()))
            throw new Error('Invalid or duplicate native site');
        addresses.add(p.toString());
    }
    // Check every full signature BEFORE instrumentation overwrites any prologue.
    for (const guard of input.guards) {
        const p = ptr(guard.address);
        const tokens = guard.bytes.trim().split(/\s+/);
        if (!tokens.length || tokens.some(b => !/^[0-9a-f]{2}$/i.test(b)) ||
            p.compare(exe.base) < 0 || p.add(tokens.length).compare(end) > 0)
            throw new Error('Invalid live signature guard');
        const actual = new Uint8Array(p.readByteArray(tokens.length));
        if (tokens.some((b, i) => Number.parseInt(b, 16) !== actual[i]))
            throw new Error('Live bytes changed before instrumentation');
    }
    config = input;
    sites = Object.fromEntries(expectedNames.map(n => [n, ptr(input.sites[n])]));
    try {
        hook('WeaponCtor', {
            onEnter() {
                this.weapon = this.context.ecx;
                this.selected = admit('weapon_ctor', this.threadId);
                if (this.selected) emit('weapon_ctor', this, {
                    weapon: pointer(this.weapon), hardpoint: pointer(at(this.context.sp, 4)),
                    object_class: pointer(at(this.context.sp, 8)) });
            },
            onLeave(result) {
                if (!result.isNull()) {
                    const key = result.toString();
                    if (!weapons.has(key) && weapons.size >= 4096) capped = true;
                    else weapons.set(key, ++generation);
                }
                if (this.selected) emit('weapon_ctor_return', this, {
                    weapon: pointer(this.weapon), result: result.toString(),
                    observed_generation: weapons.get(result.toString()) || null });
            }
        });
        hook('WeaponDtor', { onEnter() {
            const weapon = this.context.ecx;
            if (admit('weapon_dtor', this.threadId)) emit('weapon_dtor', this, weaponSnapshot(weapon));
            weapons.delete(weapon.toString());
        }});
        hook('OrdnanceFactory', {
            onEnter() {
                this.selected = this.returnAddress.equals(sites.CannonShotCall.add(5)) &&
                    admit('cannon_factory', this.threadId);
                if (!this.selected) return;
                // At callee entry EBP is still the CALLER's frame. Never use
                // generic args at the middle-of-function cannon call site.
                const weapon = at(this.context.ebp, -0x190);
                this.weapon = pointer(weapon);
                this.pose = at(this.context.sp, 4);
                emit('cannon_factory', this, {
                    ordnance_class: pointer(this.context.ecx), caller_ebp: pointer(this.context.ebp),
                    weapon: this.weapon, observed_generation: weapon !== null ? weapons.get(weapon.toString()) || null : null,
                    matrix_address: pointer(this.pose), final_pose: matrix(this.pose),
                    owner_root: pointer(at(this.context.sp, 8)), return_address: this.returnAddress.toString() });
            },
            onLeave(result) {
                if (this.selected) emit('cannon_factory_return', this, {
                    weapon: this.weapon, result: result.toString(), accepted: !result.isNull(),
                    matrix_after: matrix(this.pose) });
            }
        });
        hook('PopScope', { onEnter() {
            let kind, offset;
            if (this.returnAddress.equals(sites.WeaponClassPopCall.add(5))) { kind = 'weapon_scope_pop'; offset = -0x3c; }
            else if (this.returnAddress.equals(sites.CraftClassPopCall.add(5))) { kind = 'craft_scope_pop'; offset = -0x4c; }
            else return;
            if (admit(kind, this.threadId)) emit(kind, this, {
                scope: pointer(this.context.ecx), object_class: pointer(at(this.context.ebp, offset)),
                caller_ebp: pointer(this.context.ebp), return_address: this.returnAddress.toString() });
        }});
        hook('SimulationPass', {
            onEnter() {
                ++step;
                this.selected = admit('simulation_begin', this.threadId);
                this.step = step;
                if (this.selected) emit('simulation_begin', this, {
                    dt: read(() => finite(this.context.sp.add(4).readFloat())) });
            },
            onLeave() { if (this.selected) emit('simulation_end', this, { entry_step: this.step }); }
        });
        hook('SetWeapon', { onEnter() {
            if (!admit('set_weapon', this.threadId)) return;
            const slot = read(() => this.context.sp.add(4).readS32());
            emit('set_weapon', this, { carrier: pointer(this.context.ecx), slot,
                previous: slot !== null && slot >= 0 && slot < 5 ? pointer(at(this.context.ecx, 0x18 + slot * 4)) : null,
                replacement: pointer(at(this.context.sp, 8)) });
        }});
        hook('ModelPose', { onEnter() {
            if (!admit('model_pose', this.threadId)) return;
            const node = at(this.context.sp, 4);
            const id = node !== null && !node.isNull() ? meshId(node) : null;
            if (config.model_ids.length && !config.model_ids.includes(id)) return;
            emit('model_pose', this, { node: pointer(node), mesh_id: id,
                parent: node !== null && !node.isNull() ? pointer(at(node, 0x78)) : null,
                native_pose: matrix(at(this.context.sp, 8)), return_address: this.returnAddress.toString() });
        }});
        for (const name of ['RenderUpdate', 'RenderDetach']) {
            hook(name, {
                onEnter() {
                    this.kind = name === 'RenderUpdate' ? 'render_update' : 'render_detach';
                    this.selected = admit(this.kind, this.threadId);
                    if (!this.selected) return;
                    this.slot = this.context.ecx;
                    emit(this.kind, this, Object.assign(slotSnapshot(this.slot), {
                        pose: matrix(at(this.context.sp, 4)),
                        detach_time: name === 'RenderDetach' ? read(() => finite(this.context.sp.add(8).readFloat())) : null }));
                },
                onLeave() { if (this.selected) emit(`${this.kind}_return`, this, slotSnapshot(this.slot)); }
            });
        }
        Interceptor.flush();
        timer = setInterval(flush, 100);
        return { pid: Process.id, installed_listeners: listeners.length, activation_qualified: false };
    } catch (error) {
        stop(); // roll back every listener installed before a failure
        throw error;
    }
}

function stop() {
    if (stopped) throw new Error('Observer already stopped');
    stopped = true;
    if (timer !== null) { clearInterval(timer); timer = null; }
    for (const listener of listeners) listener.detach();
    listeners = [];
    Interceptor.flush();
    flush();
    return { complete: !capped && readErrors === 0, event_cap_reached: capped,
        read_errors: readErrors, events_emitted: emitted, observed_calls: counts,
        thread_counts: Object.fromEntries(threads), tracked_weapons: weapons.size,
        observation_only: true, activation_qualified: false,
        not_observed: ['Ogre queue/scene seams', 'renderer factory/destructor and self-expiry',
            'native model lifetime', 'SP/MP state', 'visible flash/recoil behavior'] };
}

rpc.exports = { start, stop };
