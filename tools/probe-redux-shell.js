// Battlezone 98 Redux GOG v2.2.301 shell/UI runtime probe.
//
// Read-only diagnostic for the static RE in:
//   reverse_engineering/REDUX_SHELL_UI_RE_MAP.md
//   reverse_engineering/REDUX_SHELL_UI_GATE_STATUS.md
//
// Usage (from the provisioned RE environment):
//   frida -n battlezone98redux.exe -l tools/probe-redux-shell.js
//
// Attach while the game is running. The script does not patch code, construct
// UI objects, or call Redux functions. It only attaches Interceptor observers
// and reads the validated cUI child/name fields.
//
// IMPORTANT: addresses below are the checked-in GOG battlezone98redux.exe
// v2.2.301 addresses. They are rebased from the preferred 0x00400000 image
// base at runtime, but they are NOT signatures and must not be reused on an
// unvalidated executable build.

'use strict';

const PREFERRED_IMAGE_BASE = 0x00400000;
// PE SizeOfImage, not the on-disk file length.
const EXPECTED_MODULE_SIZE = 0x0290f000;
const module = Process.mainModule;
const base = module.base;

function log(message) {
    console.log('[redux-shell] ' + message);
}

function hex(value) {
    try {
        return value.toString();
    } catch (_) {
        return String(value);
    }
}

function va(absoluteAddress) {
    return base.add(absoluteAddress - PREFERRED_IMAGE_BASE);
}

function safeReadPointer(address) {
    try {
        return address.readPointer();
    } catch (_) {
        return NULL;
    }
}

function safeReadU8(address) {
    try {
        return address.readU8();
    } catch (_) {
        return -1;
    }
}

function safeReadU32(address) {
    try {
        return address.readU32();
    } catch (_) {
        return 0xffffffff;
    }
}

function safeReadName(object) {
    if (object.isNull())
        return '<null>';
    try {
        // Frida's sized readUtf8String() decodes the entire requested byte
        // count instead of stopping at NUL in this installed runtime. Read a
        // bounded byte-at-a-time ASCII name so traversal remains fail-closed.
        const address = object.add(0x20);
        let result = '';
        for (let i = 0; i < 128; ++i) {
            const value = address.add(i).readU8();
            if (value === 0)
                return result.length === 0 ? '<empty-name>' : result;
            if (value < 0x20 || value > 0x7e)
                return '<non-ascii-name>';
            result += String.fromCharCode(value);
        }
        return '<unterminated-name>';
    } catch (e) {
        return '<unreadable-name:' + e + '>';
    }
}

function readChildVector(view, maxCount) {
    if (view.isNull())
        return null;

    try {
        const begin = view.add(0x12c).readPointer();
        const end = view.add(0x130).readPointer();
        if (begin.isNull() || end.isNull())
            return null;

        const byteCount = end.sub(begin).toInt32();
        if (byteCount < 0 || (byteCount % Process.pointerSize) !== 0)
            return null;

        const count = byteCount / Process.pointerSize;
        if (count < 0 || count > maxCount)
            return null;

        const children = [];
        for (let i = 0; i < count; ++i) {
            const child = begin.add(i * Process.pointerSize).readPointer();
            children.push({
                index: i,
                pointer: child,
                name: safeReadName(child),
                active: child.isNull() ? -1 : safeReadU8(child.add(0xe9))
            });
        }
        return children;
    } catch (_) {
        return null;
    }
}

function findChildByName(view, expectedName, maxCount) {
    const children = readChildVector(view, maxCount);
    if (children === null)
        return NULL;
    for (const child of children) {
        if (child.name === expectedName)
            return child.pointer;
    }
    return NULL;
}

function formatChildren(children) {
    if (children === null)
        return '<invalid child vector>';
    if (children.length === 0)
        return '<empty>';
    return children.map(c => '#' + c.index + ' ' + hex(c.pointer) +
        ' "' + c.name + '" active=' + c.active).join(' | ');
}

function childDelta(previous, current) {
    if (previous === null || current === null)
        return '<unavailable>';
    const key = child => hex(child.pointer) + ' "' + child.name + '" active=' + child.active;
    const before = new Set(previous.map(key));
    const after = new Set(current.map(key));
    const added = current.map(key).filter(value => !before.has(value));
    const removed = previous.map(key).filter(value => !after.has(value));
    if (added.length === 0 && removed.length === 0)
        return '<none>';
    return 'added=[' + added.join(', ') + '] removed=[' + removed.join(', ') + ']';
}

function readHistory(manager, maxCount) {
    if (manager.isNull())
        return null;
    try {
        const vector = manager.add(0x2c);
        const begin = vector.readPointer();
        const end = vector.add(4).readPointer();
        const capacity = vector.add(8).readPointer();
        if (begin.isNull() || end.isNull() || capacity.isNull() ||
            begin.compare(end) > 0 || end.compare(capacity) > 0)
            return null;
        const byteCount = end.sub(begin).toInt32();
        if (byteCount < 0 || (byteCount % 4) !== 0)
            return null;
        const count = byteCount / 4;
        if (count < 0 || count > maxCount)
            return null;
        const ids = [];
        for (let i = 0; i < count; ++i)
            ids.push(begin.add(i * 4).readU32());
        return { begin: begin, end: end, capacity: capacity, ids: ids };
    } catch (_) {
        return null;
    }
}

function formatHistory(history) {
    if (history === null)
        return '<invalid vector>';
    return 'begin=' + hex(history.begin) +
        ' end=' + hex(history.end) +
        ' capacity=' + hex(history.capacity) +
        ' ids=[' + history.ids.map(id => '0x' + id.toString(16)).join(',') + ']';
}

function formatManager(manager) {
    if (manager.isNull())
        return '<null manager>';
    return 'manager=' + hex(manager) +
        ' active=' + hex(safeReadPointer(manager.add(0x14))) +
        ' pending=' + safeReadU8(manager.add(0x27)) +
        ' history{' + formatHistory(readHistory(manager, 32)) + '}';
}

function preferredAddress(address) {
    return '0x' + address.sub(base).add(PREFERRED_IMAGE_BASE).toUInt32().toString(16);
}

function callerSummary(returnAddress) {
    try {
        const call = Instruction.parse(returnAddress.sub(5));
        const next = Instruction.parse(returnAddress);
        return 'return=' + hex(returnAddress) +
            ' preferred=' + preferredAddress(returnAddress) +
            ' call={' + call.address + ' ' + call.toString() + '}' +
            ' next={' + next.address + ' ' + next.toString() + '}';
    } catch (e) {
        return 'return=' + hex(returnAddress) + ' caller-disassembly-error=' + e;
    }
}

function bytesMatch(absoluteAddress, expected) {
    try {
        const actual = new Uint8Array(va(absoluteAddress).readByteArray(expected.length));
        for (let i = 0; i < expected.length; ++i) {
            if (actual[i] !== expected[i])
                return false;
        }
        return true;
    } catch (_) {
        return false;
    }
}

function originalOrOpenShimDetour(absoluteAddress, expected) {
    if (bytesMatch(absoluteAddress, expected))
        return true;
    try {
        const site = va(absoluteAddress);
        if (site.readU8() !== 0xe9)
            return false;
        const target = site.add(5).add(site.add(1).readS32());
        const owner = Process.findModuleByAddress(target);
        const accepted = owner !== null && owner.name.toLowerCase() === 'winmm.dll';
        if (accepted)
            log('accepted OpenShim detour at preferred ' + ptr(absoluteAddress) +
                ' -> ' + hex(target));
        return accepted;
    } catch (_) {
        return false;
    }
}

function validateBuild() {
    if (Process.pointerSize !== 4 || module.size !== EXPECTED_MODULE_SIZE)
        return false;
    return bytesMatch(0x007c7930, [0x55, 0x8b, 0xec, 0x51, 0x89, 0x4d, 0xfc]) &&
           bytesMatch(0x007c79a0, [0x55, 0x8b, 0xec, 0x51, 0x89, 0x4d, 0xfc]) &&
           originalOrOpenShimDetour(0x0078e670, [0x55, 0x8b, 0xec]) &&
           originalOrOpenShimDetour(0x0078eca0, [0x55, 0x8b, 0xec]);
}

const MAIN_SINGLETON = va(0x0094551c);
const OPTIONS_SINGLETON = va(0x009455c4);

let lastMain = NULL;
let lastOverlay = NULL;
let lastMainFingerprint = '';
let lastOverlayFingerprint = '';
let lastRootChildren = null;
let lastOverlayChildren = null;
let lastManager = NULL;
let mainGeneration = 0;
const retiredMainAddresses = new Set();

function dumpMainHierarchy(reason) {
    const main = safeReadPointer(MAIN_SINGLETON);
    const options = safeReadPointer(OPTIONS_SINGLETON);

    if (main.isNull()) {
        if (!lastMain.isNull())
            log(reason + ': MainScreen singleton cleared; previous=' + hex(lastMain));
        lastMain = NULL;
        lastOverlay = NULL;
        lastMainFingerprint = '';
        lastOverlayFingerprint = '';
        return;
    }

    const rootChildren = readChildVector(main, 64);
    const rootFingerprint = formatChildren(rootChildren);
    const overlay = findChildByName(main, 'MainScreen_Overlay', 64);
    const overlayChildren = overlay.isNull() ? null : readChildVector(overlay, 128);
    const overlayFingerprint = formatChildren(overlayChildren);

    const generationChanged = lastMain.isNull() || !main.equals(lastMain);
    const hierarchyChanged = rootFingerprint !== lastMainFingerprint ||
                             !overlay.equals(lastOverlay) ||
                             overlayFingerprint !== lastOverlayFingerprint;

    if (generationChanged || hierarchyChanged) {
        const manager = safeReadPointer(main.add(0x138));
        if (!manager.isNull())
            lastManager = manager;
        log(reason + ': main=' + hex(main) +
            ' options=' + hex(options) +
            ' overlay=' + hex(overlay) +
            ' generation=' + mainGeneration +
            ' managerFromMain+0x138=' + hex(manager));
        log('shell state: ' + formatManager(manager));
        log('active-is-main=' +
            (!manager.isNull() && safeReadPointer(manager.add(0x14)).equals(main)));
        log('MainScreen children: ' + rootFingerprint);
        log('MainScreen_Overlay children: ' + overlayFingerprint);
        if (lastRootChildren !== null)
            log('MainScreen delta: ' + childDelta(lastRootChildren, rootChildren));
        if (lastOverlayChildren !== null)
            log('MainScreen_Overlay delta: ' + childDelta(lastOverlayChildren, overlayChildren));
    }

    lastMain = main;
    lastOverlay = overlay;
    lastMainFingerprint = rootFingerprint;
    lastOverlayFingerprint = overlayFingerprint;
    lastRootChildren = rootChildren;
    lastOverlayChildren = overlayChildren;
}

function stackU32(context, zeroBasedIndex) {
    // x86 call-site stack: [esp] return address, [esp+4] first stack arg.
    if (Process.pointerSize !== 4)
        return 0xffffffff;
    return safeReadU32(context.esp.add(4 + zeroBasedIndex * 4));
}

function attachProbe(name, absoluteAddress, callbacks) {
    const target = va(absoluteAddress);
    try {
        Interceptor.attach(target, callbacks);
        log('hooked ' + name + ' @ ' + hex(target) +
            ' (preferred ' + ptr(absoluteAddress) + ')');
    } catch (e) {
        log('FAILED to hook ' + name + ' @ ' + hex(target) + ': ' + e);
    }
}

if (!validateBuild()) {
    log('UNSUPPORTED BUILD: refusing to attach hooks; module=' + module.name +
        ' size=' + module.size + ' pointerSize=' + Process.pointerSize);
    throw new Error('Redux shell probe build validation failed');
}

attachProbe('RequestPush FUN_007c7930', 0x007c7930, {
    onEnter: function () {
        this.manager = this.context.ecx;
        lastManager = this.manager;
        this.entryEsp = this.context.esp;
        this.returnAddress = safeReadPointer(this.entryEsp);
        this.stack0 = stackU32(this.context, 0);
        log('RequestPush enter ecx=' + hex(this.manager) +
            ' edx=' + hex(this.context.edx) +
            ' esp=' + hex(this.entryEsp) +
            ' stack[0]=' + this.stack0 + ' (0x' + this.stack0.toString(16) + ') ' +
            callerSummary(this.returnAddress));
        log('RequestPush before: ' + formatManager(this.manager));
    },
    onLeave: function () {
        const exitEsp = this.context.esp;
        log('RequestPush leave entryEsp=' + hex(this.entryEsp) +
            ' exitEsp=' + hex(exitEsp) +
            ' delta=' + exitEsp.sub(this.entryEsp).toInt32() +
            ' (RET 4 should consume return address + one 4-byte argument)');
        log('RequestPush after: ' + formatManager(this.manager));
        dumpMainHierarchy('after RequestPush');
    }
});

attachProbe('BackPop FUN_007c79a0', 0x007c79a0, {
    onEnter: function () {
        this.manager = this.context.ecx;
        lastManager = this.manager;
        this.entryEsp = this.context.esp;
        this.returnAddress = safeReadPointer(this.entryEsp);
        this.stack0 = stackU32(this.context, 0);
        log('BackPop enter ecx=' + hex(this.manager) +
            ' edx=' + hex(this.context.edx) +
            ' esp=' + hex(this.entryEsp) +
            ' stack[0]=0x' + this.stack0.toString(16) + ' (not an argument) ' +
            callerSummary(this.returnAddress));
        log('BackPop before: ' + formatManager(this.manager));
    },
    onLeave: function () {
        const exitEsp = this.context.esp;
        log('BackPop leave entryEsp=' + hex(this.entryEsp) +
            ' exitEsp=' + hex(exitEsp) +
            ' delta=' + exitEsp.sub(this.entryEsp).toInt32() +
            ' (RET should consume return address only)');
        log('BackPop after: ' + formatManager(this.manager));
        dumpMainHierarchy('after BackPop');
    }
});

attachProbe('ShellUpdate FUN_007c7820', 0x007c7820, {
    onEnter: function () {
        // Keep this low-volume: only log when the observed ECX object has the
        // recovered pending flag set. The decompiler prototype is not trusted.
        const candidate = this.context.ecx;
        if (!candidate.isNull() && safeReadU8(candidate.add(0x27)) === 1) {
            log('ShellUpdate pending ecx=' + hex(candidate) +
                ' stack[0]=' + stackU32(this.context, 0));
        }
    }
});

attachProbe('Transition FUN_007c7070', 0x007c7070, {
    onEnter: function () {
        this.entryEcx = this.context.ecx;
        this.manager = ptr(stackU32(this.context, 0));
        this.transitionFlag = stackU32(this.context, 1);
        lastManager = this.manager;
        this.shouldLog = !this.manager.isNull() &&
            safeReadU8(this.manager.add(0x27)) === 1;
        if (!this.shouldLog)
            return;
        log('Transition enter ecx=' + hex(this.entryEcx) +
            ' stack[0]/manager=' + hex(this.manager) +
            ' stack[1]/flag=0x' + this.transitionFlag.toString(16));
        log('Transition before: ' + formatManager(this.manager));
        dumpMainHierarchy('before Transition');
    },
    onLeave: function (retval) {
        if (!this.shouldLog)
            return;
        log('Transition leave retval=' + hex(retval));
        log('Transition after: ' + formatManager(this.manager));
        dumpMainHierarchy('after Transition');
    }
});

attachProbe('Factory FUN_007c7ad0', 0x007c7ad0, {
    onEnter: function () {
        this.manager = this.context.ecx;
        this.screenId = stackU32(this.context, 0);
        log('Factory enter ecx/manager=' + hex(this.manager) +
            ' screenId=' + this.screenId + ' (0x' + this.screenId.toString(16) + ')');
    },
    onLeave: function (retval) {
        log('Factory leave screenId=0x' + this.screenId.toString(16) +
            ' screen=' + hex(retval));
        dumpMainHierarchy('after Factory');
    }
});

attachProbe('MainScreenCtor FUN_0078e670', 0x0078e670, {
    onEnter: function () {
        this.self = this.context.ecx;
        log('MainScreen ctor enter ecx/self=' + hex(this.self));
    },
    onLeave: function (retval) {
        ++mainGeneration;
        const reused = retiredMainAddresses.has(hex(this.self));
        log('MainScreen ctor leave self=' + hex(this.self) +
            ' retval=' + hex(retval) +
            ' singleton=' + hex(safeReadPointer(MAIN_SINGLETON)) +
            ' generation=' + mainGeneration +
            ' allocatorAddressReused=' + reused);
        dumpMainHierarchy('after MainScreen ctor');
    }
});

attachProbe('MainScreenDtor FUN_0078eca0', 0x0078eca0, {
    onEnter: function () {
        this.self = this.context.ecx;
        log('MainScreen dtor enter ecx/self=' + hex(this.self) +
            ' singleton=' + hex(safeReadPointer(MAIN_SINGLETON)));
    },
    onLeave: function () {
        retiredMainAddresses.add(hex(this.self));
        log('MainScreen dtor leave self=' + hex(this.self) +
            ' singleton=' + hex(safeReadPointer(MAIN_SINGLETON)));
        dumpMainHierarchy('after MainScreen dtor');
    }
});

log('build validation passed for GOG 2.2.301');
log('attached to ' + module.name +
    ' base=' + hex(base) +
    ' size=0x' + module.size.toString(16) +
    ' pointerSize=' + Process.pointerSize);
log('MainScreen singleton slot=' + hex(MAIN_SINGLETON) +
    ' Options singleton slot=' + hex(OPTIONS_SINGLETON));
log('This probe is read-only. Exercise Main -> Options -> Back, SP/MP/Mods, and Credits/Intro.');

dumpMainHierarchy('initial');

setInterval(function () {
    dumpMainHierarchy('poll');
    if (!lastManager.isNull() && safeReadU8(lastManager.add(0x27)) === 1)
        log('poll pending: ' + formatManager(lastManager));
}, 500);
