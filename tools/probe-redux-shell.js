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
        const s = object.add(0x20).readUtf8String(128);
        return s === null ? '<null-name>' : s;
    } catch (_) {
        return '<unreadable-name>';
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
            children.push({ index: i, pointer: child, name: safeReadName(child) });
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
    return children.map(c => '#' + c.index + ' ' + hex(c.pointer) + ' "' + c.name + '"').join(' | ');
}

const MAIN_SINGLETON = va(0x0094551c);
const OPTIONS_SINGLETON = va(0x009455c4);

let lastMain = NULL;
let lastOverlay = NULL;
let lastMainFingerprint = '';
let lastOverlayFingerprint = '';

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
        log(reason + ': main=' + hex(main) +
            ' options=' + hex(options) +
            ' overlay=' + hex(overlay));
        log('MainScreen children: ' + rootFingerprint);
        log('MainScreen_Overlay children: ' + overlayFingerprint);
    }

    lastMain = main;
    lastOverlay = overlay;
    lastMainFingerprint = rootFingerprint;
    lastOverlayFingerprint = overlayFingerprint;
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

attachProbe('RequestPush FUN_007c7930', 0x007c7930, {
    onEnter: function () {
        this.manager = this.context.ecx;
        this.stack0 = stackU32(this.context, 0);
        const pending = this.manager.isNull() ? -1 : safeReadU8(this.manager.add(0x27));
        log('RequestPush enter ecx/manager=' + hex(this.manager) +
            ' stack[0]=' + this.stack0 + ' (0x' + this.stack0.toString(16) + ')' +
            ' pending=' + pending);
    },
    onLeave: function () {
        const pending = this.manager.isNull() ? -1 : safeReadU8(this.manager.add(0x27));
        log('RequestPush leave manager=' + hex(this.manager) + ' pending=' + pending);
        dumpMainHierarchy('after RequestPush');
    }
});

attachProbe('BackPop FUN_007c79a0', 0x007c79a0, {
    onEnter: function () {
        this.manager = this.context.ecx;
        this.stack0 = stackU32(this.context, 0);
        const pending = this.manager.isNull() ? -1 : safeReadU8(this.manager.add(0x27));
        log('BackPop enter ecx/manager=' + hex(this.manager) +
            ' stack[0]=' + this.stack0 + ' (diagnostic only)' +
            ' pending=' + pending);
    },
    onLeave: function () {
        const pending = this.manager.isNull() ? -1 : safeReadU8(this.manager.add(0x27));
        log('BackPop leave manager=' + hex(this.manager) + ' pending=' + pending);
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
        this.ecx = this.context.ecx;
        this.stack0 = stackU32(this.context, 0);
        this.stack1 = stackU32(this.context, 1);
        log('Transition enter ecx=' + hex(this.ecx) +
            ' stack[0]=0x' + this.stack0.toString(16) +
            ' stack[1]=0x' + this.stack1.toString(16));
        dumpMainHierarchy('before Transition');
    },
    onLeave: function (retval) {
        log('Transition leave retval=' + hex(retval));
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
        log('MainScreen ctor leave self=' + hex(this.self) +
            ' retval=' + hex(retval) +
            ' singleton=' + hex(safeReadPointer(MAIN_SINGLETON)));
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
        log('MainScreen dtor leave self=' + hex(this.self) +
            ' singleton=' + hex(safeReadPointer(MAIN_SINGLETON)));
        dumpMainHierarchy('after MainScreen dtor');
    }
});

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
}, 500);
