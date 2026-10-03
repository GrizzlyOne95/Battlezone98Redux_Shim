// Exercise the production observer's ABI reads and rejection behavior.
// This is a synthetic memory/Frida harness; never label it live evidence.
'use strict';
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');
const catalog = JSON.parse(fs.readFileSync(path.join(__dirname, '../scripts/patches.json'), 'utf8'));
const rows = catalog.resolves.filter(r => r.name.startsWith('WeaponPresentation::'));
const source = fs.readFileSync(path.join(__dirname, 'probe_weapon_presentation.js'), 'utf8');

function harness(limit = 4096, failHook = 0) {
    const memory = Buffer.alloc(0x700000);
    const hooks = new Map();
    const events = [];
    let detached = 0;
    class Pointer {
        constructor(value) { this.value = typeof value === 'string' ? Number(value) : value; }
        add(offset) { return new Pointer(this.value + offset); }
        equals(other) { return this.value === other.value; }
        compare(other) { return Math.sign(this.value - other.value); }
        isNull() { return this.value === 0; }
        toString() { return `0x${this.value.toString(16)}`; }
        readPointer() { return new Pointer(memory.readUInt32LE(this.value)); }
        readFloat() { return memory.readFloatLE(this.value); }
        readDouble() { return memory.readDoubleLE(this.value); }
        readS32() { return memory.readInt32LE(this.value); }
        readByteArray(size) {
            if (this.value + size > memory.length) throw Error('unreadable');
            return Uint8Array.from(memory.subarray(this.value, this.value + size)).buffer;
        }
    }
    const ptr = value => new Pointer(value);
    const config = { pid: 42, module_path: 'C:\\GOG\\battlezone98redux.exe', image_base: '0x400000',
        sites: {}, guards: [], max_events: limit, model_ids: ['barrel'] };
    for (const row of rows) {
        const name = row.name.split('::')[1];
        const site = Number(row.fallback);
        config.sites[name] = row.fallback;
        config.guards.push({ address: ptr(site - row.offset).toString(), bytes: row.pattern });
        Buffer.from(row.pattern.replace(/ /g, ''), 'hex').copy(memory, site - row.offset);
    }
    const context = { Process: { platform: 'windows', arch: 'ia32', pointerSize: 4, id: 42,
        mainModule: { name: 'battlezone98redux.exe', path: config.module_path, base: ptr(0x400000), size: 0x310000 } },
        ptr, Uint8Array, rpc: {}, send: payload => events.push(...payload.events),
        setInterval: () => 1, clearInterval: () => {},
        Interceptor: { attach: (site, callbacks) => {
            if (failHook && hooks.size + 1 === failHook) throw Error('attach failure');
            hooks.set(site.toString(), callbacks);
            return { detach: () => ++detached };
        }, flush: () => {} } };
    vm.createContext(context);
    vm.runInContext(source, context);
    const sp = 0x200000, ebp = 0x201000;
    function invoke(name, ecx, args, ret = '0x0', returnAddress = 0x1234) {
        args.forEach((arg, i) => memory.writeUInt32LE(arg >>> 0, sp + 4 + i * 4));
        const invocation = { context: { sp: ptr(sp), ebp: ptr(ebp), ecx: ptr(ecx) },
            returnAddress: ptr(returnAddress), threadId: 7 };
        const callbacks = hooks.get(ptr(config.sites[name]).toString());
        if (callbacks.onEnter) callbacks.onEnter.call(invocation);
        if (callbacks.onLeave) callbacks.onLeave.call(invocation, ptr(ret));
        return invocation;
    }
    return { config, context, hooks, events, memory, ptr, sp, ebp, invoke, detached: () => detached };
}

{
    const h = harness();
    h.config.pid = 99;
    assert.throws(() => h.context.rpc.exports.start(h.config), /Wrong process/);
    assert.equal(h.hooks.size, 0);
}
{
    const h = harness();
    h.memory.writeUInt8(0xe9, Number(h.config.sites.WeaponCtor));
    assert.throws(() => h.context.rpc.exports.start(h.config), /Live bytes changed/);
    assert.equal(h.hooks.size, 0);
}
{
    const h = harness(4096, 3);
    assert.throws(() => h.context.rpc.exports.start(h.config), /attach failure/);
    assert.equal(h.detached(), 2);
}
{
    const h = harness();
    const started = h.context.rpc.exports.start(h.config);
    assert.equal(started.installed_listeners, 9);
    assert.equal(started.activation_qualified, false);
    const weapon = 0x100000, matrix = 0x110000, root = 0x120000, objectClass = 0x130000;
    h.memory.writeUInt32LE(weapon, h.ebp - 0x190);
    h.memory.writeUInt32LE(objectClass, h.ebp - 0x3c);
    h.memory.writeUInt32LE(objectClass + 4, h.ebp - 0x4c);
    for (let i = 0; i < 9; ++i) h.memory.writeFloatLE(i + 0.25, matrix + i * 4);
    [40, 48, 56].forEach((offset, i) => h.memory.writeDoubleLE(i + 100.5, matrix + offset));
    h.invoke('WeaponCtor', weapon, [0x140000, objectClass], weapon);
    h.invoke('OrdnanceFactory', objectClass, [matrix, root], 0x150000, Number(h.config.sites.CannonShotCall) + 5);
    h.invoke('OrdnanceFactory', objectClass, [matrix, root], 0, Number(h.config.sites.CannonShotCall) + 5);
    h.invoke('OrdnanceFactory', objectClass, [matrix, root], 0x150000, 0x777777); // unrelated spawn
    h.invoke('PopScope', 0x160000, [], 0, Number(h.config.sites.WeaponClassPopCall) + 5);
    h.invoke('PopScope', 0x170000, [], 0, Number(h.config.sites.CraftClassPopCall) + 5);
    // Float stack bits, rather than an integer/pointer interpretation of dt.
    const dt = Buffer.alloc(4); dt.writeFloatLE(0.125);
    h.invoke('SimulationPass', 0, [dt.readUInt32LE()]);
    const slot = 0x180000, renderer = 0x190000;
    h.memory.writeUInt32LE(renderer, slot);
    h.memory.writeUInt32LE(slot, renderer + 0x68);
    h.invoke('RenderUpdate', slot, [matrix]);
    const node = 0x1a0000;
    h.memory.write('barrel\0', node + 8, 'ascii');
    h.invoke('ModelPose', 0, [node, matrix]);
    h.invoke('WeaponDtor', weapon, []);
    const summary = h.context.rpc.exports.stop();
    assert.equal(summary.complete, true);
    assert.equal(summary.tracked_weapons, 0);
    const shots = h.events.filter(e => e.kind === 'cannon_factory');
    assert.equal(shots.length, 2);
    assert.equal(shots[0].weapon, h.ptr(weapon).toString());
    assert.equal(shots[0].ordnance_class, h.ptr(objectClass).toString());
    assert.equal(shots[0].owner_root, h.ptr(root).toString());
    assert.equal(shots[0].observed_generation, 1);
    assert.deepEqual(Array.from(shots[0].final_pose.position), [100.5, 101.5, 102.5]);
    assert.equal(h.events.filter(e => e.kind === 'cannon_factory_return' && e.accepted).length, 1);
    assert.equal(h.events.find(e => e.kind === 'weapon_scope_pop').object_class, h.ptr(objectClass).toString());
    assert.equal(h.events.find(e => e.kind === 'craft_scope_pop').object_class, h.ptr(objectClass + 4).toString());
    assert.equal(h.events.find(e => e.kind === 'simulation_begin').dt, 0.125);
    assert.equal(h.events.find(e => e.kind === 'render_update').backref_matches, true);
    assert.equal(h.events.find(e => e.kind === 'model_pose').mesh_id, 'barrel');
    assert.equal(h.detached(), 9);
}
{
    const h = harness(1);
    h.context.rpc.exports.start(h.config);
    h.invoke('SimulationPass', 0, [0]);
    const summary = h.context.rpc.exports.stop();
    assert.equal(summary.complete, false);
    assert.equal(summary.event_cap_reached, true);
    assert.equal(h.events.length, 1);
}
console.log('Weapon presentation observer rejection, rollback, ABI and bounded-capture tests passed');
