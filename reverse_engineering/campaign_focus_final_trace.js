// One-run custom-final campaign/focus trace for exact Redux 2.2.301 builds.
// This script is observational only: it installs no executable patches.

const mainName = "battlezone98redux.exe";
const main = Process.enumerateModules().find(m => (m.name || "").toLowerCase() === mainName);
if (main === undefined) {
  throw new Error("battlezone98redux.exe module not found");
}
const base = main.base;

function at(rva) { return base.add(rva); }
function now() { return new Date().toISOString(); }
function log(text) { console.log("[" + now() + "] " + text); }
function hex(value) { try { return ptr(value).toString(); } catch (_) { return "<invalid>"; } }
function readU32(address) { try { return ptr(address).readU32(); } catch (_) { return null; } }
function readS32(address) { try { return ptr(address).readS32(); } catch (_) { return null; } }
function readPtr(address) { try { return ptr(address).readPointer(); } catch (_) { return ptr(0); } }
function readCString(address, maximum) {
  try {
    const value = ptr(address).readCString(maximum || 512);
    return value === null ? "<null>" : value;
  } catch (_) { return "<unreadable>"; }
}
function readUtf16(address, maximum) {
  try {
    const value = ptr(address).readUtf16String(maximum || 512);
    return value === null ? "<null>" : value;
  } catch (_) { return "<unreadable>"; }
}

function bytesMatch(rva, expected) {
  try {
    const actual = new Uint8Array(at(rva).readByteArray(expected.length));
    return expected.every((value, index) => actual[index] === value);
  } catch (_) { return false; }
}

const gates = [
  [0x00219340, [0x55, 0x8b, 0xec]],
  [0x003d3850, [0x55, 0x8b, 0xec, 0x6a, 0xff]],
  [0x003d3dd0, [0x55, 0x8b, 0xec, 0x51]],
  [0x0021994e, [0xff, 0x15, 0xec, 0x9f, 0x86, 0x00]]
];
for (const gate of gates) {
  if (!bytesMatch(gate[0], gate[1])) {
    throw new Error("exact-byte gate failed at " + at(gate[0]));
  }
}

function user32(name, returnType, argumentTypes) {
  return new NativeFunction(Process.getModuleByName("user32.dll").getExportByName(name),
    returnType, argumentTypes, "stdcall");
}
function kernel32(name, returnType, argumentTypes) {
  return new NativeFunction(Process.getModuleByName("kernel32.dll").getExportByName(name),
    returnType, argumentTypes, "stdcall");
}

const getForegroundWindow = user32("GetForegroundWindow", "pointer", []);
const getWindowThreadProcessId = user32("GetWindowThreadProcessId", "uint32", ["pointer", "pointer"]);
const getWindowTextW = user32("GetWindowTextW", "int", ["pointer", "pointer", "int"]);
const openProcess = kernel32("OpenProcess", "pointer", ["uint32", "int", "uint32"]);
const queryFullProcessImageNameW = kernel32("QueryFullProcessImageNameW", "bool",
  ["pointer", "uint32", "pointer", "pointer"]);
const closeHandle = kernel32("CloseHandle", "bool", ["pointer"]);

function describeWindow(hwnd) {
  if (ptr(hwnd).isNull()) return "hwnd=0x0 pid=0 title=<none> process=<none>";
  const pidOut = Memory.alloc(4);
  pidOut.writeU32(0);
  getWindowThreadProcessId(hwnd, pidOut);
  const pid = pidOut.readU32();
  const titleBuffer = Memory.alloc(1024);
  getWindowTextW(hwnd, titleBuffer, 512);
  let processPath = "<unavailable>";
  const processHandle = openProcess(0x1000, 0, pid);
  if (!processHandle.isNull()) {
    const pathBuffer = Memory.alloc(2048);
    const chars = Memory.alloc(4);
    chars.writeU32(1024);
    if (queryFullProcessImageNameW(processHandle, 0, pathBuffer, chars)) {
      processPath = readUtf16(pathBuffer, chars.readU32());
    }
    closeHandle(processHandle);
  }
  return "hwnd=" + hex(hwnd) + " pid=" + pid + " title=\"" + readUtf16(titleBuffer, 512) +
    "\" process=\"" + processPath + "\"";
}

let lastMissionCount = null;
let lastMissionIndexGetter = null;
let lastResultMedia = "<not-seen>";

function snapshot(tag) {
  const runState = readS32(at(0x004e706c));       // DAT_008E706C
  const screenId = readS32(at(0x00518328));       // DAT_00918328
  const resultMarker = readS32(at(0x0051830c));   // DAT_0091830C
  const archiveReplay = readS32(at(0x00518314));  // DAT_00918314
  const missionIndexGlobal = readS32(at(0x0051831c));
  const shellProgress = readS32(at(0x00518330));
  const fullscreen = readS32(at(0x005183b8));
  const active = readS32(at(0x004eaaa4));
  const campaign = readMsvcString(at(0x0054fee0)); // DAT_0094FEE0
  const foreground = describeWindow(getForegroundWindow());
  log("[STATE] tag=" + tag + " run=" + runState + " screen=0x" +
    (screenId === null ? "?" : screenId.toString(16)) + " campaign=\"" + campaign +
    "\" missionGlobal=" + missionIndexGlobal + " missionGetter=" + lastMissionIndexGetter +
    " missionCount=" + lastMissionCount + " resultMarker=" + resultMarker +
    " archiveReplay=" + archiveReplay + " shellProgress=" + shellProgress +
    " fullscreen=" + fullscreen + " active=" + active +
    " resultMedia=\"" + lastResultMedia + "\" foreground={" + foreground + "}");
}

function readMsvcString(object) {
  try {
    const value = ptr(object);
    const size = value.add(16).readU32();
    const capacity = value.add(20).readU32();
    if (size > 32768 || capacity > 0x1000000) return "<invalid-string>";
    const bytes = capacity < 16 ? value : value.readPointer();
    return bytes.readCString(size) || "";
  } catch (_) { return "<unreadable-string>"; }
}

const messageNames = {
  0x0005: "WM_SIZE",
  0x0006: "WM_ACTIVATE",
  0x0007: "WM_SETFOCUS",
  0x0008: "WM_KILLFOCUS",
  0x001c: "WM_ACTIVATEAPP",
  0x0112: "WM_SYSCOMMAND"
};

Interceptor.attach(at(0x00219340), {
  onEnter(args) {
    const message = args[1].toUInt32();
    const name = messageNames[message];
    if (name === undefined) return;
    const wParam = args[2].toUInt32();
    const lParam = args[3].toUInt32();
    log("[WNDPROC] message=" + name + "(0x" + message.toString(16) + ") hwnd=" + hex(args[0]) +
      " wParam=0x" + wParam.toString(16) + " lParam=0x" + lParam.toString(16));
    snapshot("WndProc." + name);
  }
});

const showWindowAddress = Process.getModuleByName("user32.dll").getExportByName("ShowWindow");
Interceptor.attach(showWindowAddress, {
  onEnter(args) {
    this.hwnd = args[0];
    this.command = args[1].toInt32();
    this.caller = this.returnAddress;
    log("[SHOWWINDOW] enter hwnd=" + hex(this.hwnd) + " command=" + this.command +
      " caller=" + DebugSymbol.fromAddress(this.caller) + " foreground={" +
      describeWindow(getForegroundWindow()) + "}");
  },
  onLeave(result) {
    log("[SHOWWINDOW] leave hwnd=" + hex(this.hwnd) + " command=" + this.command +
      " result=" + result.toInt32() + " foreground={" + describeWindow(getForegroundWindow()) + "}");
    snapshot("ShowWindow." + this.command);
  }
});

Interceptor.attach(at(0x00034170), {
  onEnter(args) { this.next = args[0].toInt32(); snapshot("SetRunning.before." + this.next); },
  onLeave(_) { snapshot("SetRunning.after." + this.next); }
});
Interceptor.attach(at(0x001d5150), {
  onEnter(_) { snapshot("ResultTransitionLoop.enter"); },
  onLeave(_) { snapshot("ResultTransitionLoop.leave"); }
});
Interceptor.attach(at(0x003c7ad0), {
  onEnter(_) { snapshot("ScreenFactory.enter"); },
  onLeave(result) { log("[SCREEN] factory result=" + hex(result)); snapshot("ScreenFactory.leave"); }
});
Interceptor.attach(at(0x000885d0), {
  onLeave(result) { lastMissionCount = result.toInt32(); log("[CAMPAIGN] missionCount=" + lastMissionCount); }
});
Interceptor.attach(at(0x000888b0), {
  onLeave(result) { lastMissionIndexGetter = result.toInt32(); log("[CAMPAIGN] missionIndexGetter=" + lastMissionIndexGetter); }
});

Interceptor.attach(at(0x003d3850), {
  onEnter(args) {
    log("[THEORA] result-media prepare owner=" + hex(this.context.ecx));
    snapshot("Theora.prepare.enter");
  },
  onLeave(_) { snapshot("Theora.prepare.leave"); }
});
Interceptor.attach(at(0x003d3dd0), {
  onEnter(args) {
    const owner = this.context.ecx;
    const clip = owner.isNull() ? ptr(0) : readPtr(owner.add(0x140));
    log("[THEORA] playback wrapper owner=" + hex(owner) + " clip=" + hex(clip) +
      " flag=" + args[0].toInt32());
    snapshot("Theora.playback");
  }
});

const createClipTarget = readPtr(at(0x00469eec));
if (!createClipTarget.isNull()) {
  Interceptor.attach(createClipTarget, {
    onEnter(args) {
      lastResultMedia = readMsvcString(args[0]);
      log("[THEORA] createClip filename=\"" + lastResultMedia + "\" group=\"" +
        readMsvcString(args[1]) + "\" manager=" + hex(this.context.ecx));
    },
    onLeave(result) { log("[THEORA] createClip result=" + hex(result)); }
  });
}
const playTarget = readPtr(at(0x00469ef8));
if (!playTarget.isNull()) {
  Interceptor.attach(playTarget, {
    onEnter(args) {
      log("[THEORA] clip.play clip=" + hex(this.context.ecx) + " flag=" + args[0].toInt32());
    }
  });
}

log("[TRACE] ready module=\"" + main.path + "\" base=" + base + " size=" + main.size +
  " createClip=" + createClipTarget + " play=" + playTarget);
snapshot("trace-ready");
