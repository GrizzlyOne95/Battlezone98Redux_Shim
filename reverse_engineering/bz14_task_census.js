// ============================================================================
// bz14_task_census.js - live Redux AI task/process census for bz14atk runs.
//
// Answers, from a LIVE process only:
//   - which attack/task-family DoState bodies actually execute (how often),
//   - which process classes drive them,
//   - what state ids the live tasks hold,
//   - whether the generic AttackTask::DoState body executes at all.
//
// Method notes (2026-08-24):
//   The shipped exe is packed. Module pages around the AttackTask cluster
//   have been observed holding non-code data at various times while other
//   module code kept executing (recovery report §6.3), so NEITHER byte
//   validation NOR static-VTA vtable seeding proves anything here. This
//   census therefore:
//     1. locates function BODIES by unique-prologue pattern scans across
//        all r-x ranges (the only method proven to reach real executing
//        copies on this build, including private RWX arena copies),
//     2. discovers live subtask objects through the proven process seams
//        (OffensiveProcess::DoSubTask, WingmanProcess::ShouldAttack) and
//        records their RUNTIME vtable pointer values,
//     3. opportunistically attaches counters to vtable slot +0x30 contents
//        only when they hold plausible code pointers at hook time.
//   A body with zero calls here is execution-dead for this workload no
//   matter how valid its bytes are.
//
// Usage (attach mode, after the mission is running):
//   python run_bz14_task_census.py --scenarios avtank:attack
// Output: one "[census] {...}" JSON line every REPORT_SECONDS.
// ============================================================================

'use strict';

const MODULE_NAME = 'battlezone98redux.exe';
const REPORT_SECONDS = 5;
const SPACE_SKIP_TICKS = 10;

const MAX_RANGE_BYTES = 96 * 1024 * 1024; // skip oversized (non-module) ranges

// Unique prologues (proven unique across r-x ranges on GOG 2.2.301).
const PATTERNS = {
    AttackTask_DoState: '55 8b ec 83 ec 7c 89 4d fc',
    OffProc_DoSubTask: '55 8b ec 83 ec 58 89 4d f8 8b 45 f8 83 78 18 00 75 07',
    Wing_ShouldAttack: '55 8b ec 83 ec 10 89 4d fc 8b 45 08 89 45 f8 83 7d f8 07 74 18',
    RocketTank_DoState: '55 8b ec 83 ec 1c 89 4d f8 8b 45 f8 83 78 08 0d 75 05'
};

const bodies = Object.create(null);      // body addr -> record
const vtablesSeen = Object.create(null); // vt ptr value -> {rtti, labels}
const processesSeen = Object.create(null);
const counters = {
    doSubTaskCalls: 0,
    shouldAttackCalls: 0
};
let installed = false;

function findBase() {
    return Process.enumerateModules().find(
        x => x.name.toLowerCase() === MODULE_NAME) || null;
}

function safeRtti(vt) {
    try {
        const col = vt.sub(4).readPointer();
        const td = col.add(4).readPointer();
        const name = td.add(8).readCString();
        if (name && name.indexOf('.?A') === 0)
            return name;
    } catch (e) {}
    return null;
}

function plausibleCode(p) {
    try {
        return !p.isNull() && p.compare(ptr('0x401000')) > 0;
    } catch (e) {
        return false;
    }
}

function recordBody(bodyAddr, label) {
    const key = bodyAddr.toString();
    let b = bodies[key];
    if (!b) {
        b = bodies[key] = {
            addr: key,
            labels: {},
            calls: 0,
            lastCur: -1,
            lastNext: -1,
            hist: {},
            crafts: 0
        };
        try {
            Interceptor.attach(bodyAddr, {
                onEnter() {
                    b.calls++;
                    try {
                        const task = this.context.ecx;
                        b.lastCur = task.add(8).readS32();
                        b.lastNext = task.add(0xC).readS32();
                        const k = String(b.lastCur);
                        b.hist[k] = (b.hist[k] || 0) + 1;
                        if (!b._crafts) b._crafts = {};
                        const ck = task.add(0x10).readPointer().toString();
                        if (!b._crafts[ck]) {
                            b._crafts[ck] = true;
                            b.crafts++;
                        }
                    } catch (e) {}
                }
            });
            console.log('[census] hooked ' + label + ' @ ' + key);
        } catch (e) {
            b.attachError = '' + e;
            console.log('[census] attach FAILED ' + label + ' @ ' + key +
                        ': ' + e);
        }
    }
    if (!b.labels[label])
        b.labels[label] = true;
}

function observeVtable(vt, label) {
    if (!plausibleCode(vt))
        return;
    const key = vt.toString();
    let entry = vtablesSeen[key];
    if (!entry) {
        entry = vtablesSeen[key] = { rtti: safeRtti(vt), labels: {} };
    }
    if (!entry.labels[label])
        entry.labels[label] = true;
    // Opportunistic slot +0x30 hook: only trust a live-looking pointer.
    if (!entry.bodyTried) {
        entry.bodyTried = true;
        try {
            const body = vt.add(0x30).readPointer();
            entry.body = body.toString();
            if (plausibleCode(body))
                recordBody(body, 'vt:' + key);
        } catch (e) {}
    }
}

function scanRanges(pattern) {
    const hits = [];
    for (const r of Process.enumerateRanges('r-x')) {
        if (r.size > MAX_RANGE_BYTES)
            continue;
        try {
            for (const f of Memory.scanSync(r.base, r.size, pattern))
                hits.push(f.address);
        } catch (e) {}
    }
    return hits;
}

function install() {
    let allFound = true;
    const seamAddrs = [];
    for (const tag of Object.keys(PATTERNS)) {
        const hits = scanRanges(PATTERNS[tag]);
        if (hits.length === 0) {
            allFound = false;
            continue;
        }
        if (hits.length > 1) {
            // Known case: the same body can exist as a module copy plus an
            // unpacked RWX arena copy. Hook every copy; report ambiguity.
            console.log('[census] ' + tag + ': ' + hits.length +
                        ' copies @ ' + hits.map(String).join(','));
        }
        if (tag === 'OffProc_DoSubTask' || tag === 'Wing_ShouldAttack')
            seamAddrs.push({ tag: tag, addrs: hits });
        for (const h of hits)
            recordBody(h, tag);
    }

    // Wire dynamic subtask/vtable discovery onto every process-seam copy.
    for (const seam of seamAddrs) {
        for (const addr of seam.addrs) {
            try {
                Interceptor.attach(addr, {
                    onEnter() {
                        try {
                            counters[seam.tag === 'OffProc_DoSubTask'
                                         ? 'doSubTaskCalls'
                                         : 'shouldAttackCalls']++;
                            const proc = this.context.ecx;
                            const procVt = proc.readPointer();
                            const pk = procVt.toString();
                            if (!processesSeen[pk]) {
                                processesSeen[pk] = {
                                    rtti: safeRtti(procVt),
                                    count: 0
                                };
                            }
                            processesSeen[pk].count++;
                            let task = null;
                            try {
                                task = proc.add(0x38).readPointer();
                            } catch (e) {}
                            if (task && !task.isNull()) {
                                observeVtable(task.readPointer(),
                                              'dyn:' + seam.tag);
                            }
                        } catch (e) {}
                    }
                });
                console.log('[census] seam wired ' + seam.tag + ' @ ' + addr);
            } catch (e) {}
        }
    }

    if (!allFound) {
        console.log('[census] some bodies not located yet; rescanning');
        return false;
    }
    console.log('[census] installation complete');
    return true;
}

(function spaceSkip() {
    const kb = new NativeFunction(
        Process.getModuleByName('user32.dll').getExportByName('keybd_event'),
        'void', ['uchar', 'uchar', 'uint', 'pointer']);
    let ticks = 0;
    const iv = setInterval(() => {
        ticks++;
        kb(0x20, 0, 0, ptr(0));
        kb(0x20, 0, 2, ptr(0));
        if (ticks >= SPACE_SKIP_TICKS)
            clearInterval(iv);
    }, 2000);
})();

const waitIv = setInterval(() => {
    if (!installed && findBase() && install()) {
        installed = true;
        clearInterval(waitIv);
    }
}, 2000);

setInterval(report, REPORT_SECONDS * 1000);

function report() {
    const snapshot = {
        counters: counters,
        processes: processesSeen,
        vtables: {},
        bodies: {}
    };
    for (const vk of Object.keys(vtablesSeen)) {
        const v = vtablesSeen[vk];
        snapshot.vtables[vk] = {
            rtti: v.rtti,
            labels: Object.keys(v.labels),
            body: v.body || null
        };
    }
    for (const bk of Object.keys(bodies)) {
        const x = bodies[bk];
        snapshot.bodies[bk] = {
            labels: Object.keys(x.labels),
            calls: x.calls,
            lastCur: x.lastCur,
            lastNext: x.lastNext,
            hist: x.hist,
            crafts: x.crafts,
            error: x.attachError || null
        };
    }
    console.log('[census] ' + JSON.stringify(snapshot));
}
