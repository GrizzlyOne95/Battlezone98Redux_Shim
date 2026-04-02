const moduleName = "battlezone98redux.exe";

function resolveMainModule() {
  const modules = Process.enumerateModules();
  for (const mod of modules) {
    if ((mod.name || "").toLowerCase() === moduleName) {
      return mod;
    }
  }

  for (const mod of modules) {
    const path = (mod.path || "").toLowerCase();
    if (path.endsWith("\\" + moduleName)) {
      return mod;
    }
  }

  if (modules.length > 0) {
    return modules[0];
  }

  throw new Error("unable to resolve main module");
}

const mainModule = resolveMainModule();
const moduleBase = mainModule.base;

const rvas = {
  createChunk: 0x00092aa0,
  createChunkParent: 0x000924f5,
  fragmentParentA: 0x000ac5e0,
  fragmentParentB: 0x000ee768,
  fragmentParentC: 0x000df34a
};

const budgets = {
  createChunk: 12,
  createChunkParent: 20,
  fragmentParentA: 20,
  fragmentParentB: 12,
  fragmentParentC: 12
};

function at(rva) {
  return moduleBase.add(rva);
}

function now() {
  return new Date().toISOString();
}

function log(message) {
  console.log("[" + now() + "] " + message);
}

function hex(value) {
  return ptr(value).toString();
}

function safeReadU32(address) {
  try {
    return ptr(address).readU32();
  } catch (_e) {
    return null;
  }
}

function safeReadPtr(address) {
  try {
    return ptr(address).readPointer();
  } catch (_e) {
    return ptr(0);
  }
}

function formatBacktrace(context) {
  let frames = [];
  try {
    frames = Thread.backtrace(context, Backtracer.ACCURATE);
  } catch (_e) {
    frames = Thread.backtrace(context, Backtracer.FUZZY);
  }
  return frames.slice(0, 10).map((addr, index) => {
    return "#" + index + " " + DebugSymbol.fromAddress(addr).toString();
  }).join(" | ");
}

function formatRegs(context) {
  return "eax=" + hex(context.eax) +
    " ecx=" + hex(context.ecx) +
    " edx=" + hex(context.edx) +
    " ebx=" + hex(context.ebx) +
    " esi=" + hex(context.esi) +
    " edi=" + hex(context.edi) +
    " ebp=" + hex(context.ebp) +
    " esp=" + hex(context.esp);
}

function formatStackWords(stackPtr, count) {
  const parts = [];
  for (let i = 0; i < count; i++) {
    const addr = ptr(stackPtr).add(i * 4);
    const value = safeReadU32(addr);
    if (value === null) {
      parts.push("[" + i + "]=<fault>");
      break;
    }
    parts.push("[" + i + "]=0x" + value.toString(16));
  }
  return parts.join(" ");
}

function looksLikeGamePtr(value) {
  const n = ptr(value).toUInt32();
  return n >= 0x10000000 && n < 0x7fff0000 && (n % 4) === 0;
}

function summarizeObj76(value) {
  const p = ptr(value);
  if (p.isNull() || !looksLikeGamePtr(p)) {
    return null;
  }

  const classId = safeReadU32(p.add(0x84));
  const parent = safeReadPtr(p.add(0x78));
  const sibling = safeReadPtr(p.add(0x7c));
  const child = safeReadPtr(p.add(0x80));
  const gameObj = safeReadPtr(p.add(0x8c));
  const bridge = safeReadPtr(p.add(0xf0));

  if (classId === null) {
    return null;
  }

  return (
    "obj=" + hex(p) +
    " class=" + classId +
    " parent=" + hex(parent) +
    " sibling=" + hex(sibling) +
    " child=" + hex(child) +
    " gameObj=" + hex(gameObj) +
    " bridge=" + hex(bridge)
  );
}

function logCandidateSet(tag, context) {
  const candidates = [
    ["eax", context.eax],
    ["ecx", context.ecx],
    ["edx", context.edx],
    ["ebx", context.ebx],
    ["esi", context.esi],
    ["edi", context.edi],
    ["stack0", safeReadPtr(context.esp.add(0x0))],
    ["stack1", safeReadPtr(context.esp.add(0x4))],
    ["stack2", safeReadPtr(context.esp.add(0x8))],
    ["stack3", safeReadPtr(context.esp.add(0xc))],
    ["stack4", safeReadPtr(context.esp.add(0x10))],
    ["stack5", safeReadPtr(context.esp.add(0x14))],
    ["stack6", safeReadPtr(context.esp.add(0x18))],
    ["stack7", safeReadPtr(context.esp.add(0x1c))]
  ];

  for (const [label, value] of candidates) {
    const summary = summarizeObj76(value);
    if (summary !== null) {
      log("[" + tag + ".cand] " + label + " " + summary);
    }
  }
}

function attachSite(name, rva, budgetKey) {
  const address = at(rva);
  try {
    Interceptor.attach(address, {
      onEnter(args) {
        if (budgets[budgetKey] <= 0) {
          return;
        }
        budgets[budgetKey]--;
        log("[" + name + "] at=" + hex(address) + " return=" + hex(this.returnAddress));
        log("[" + name + ".regs] " + formatRegs(this.context));
        log("[" + name + ".stack] " + formatStackWords(this.context.esp, 10));
        logCandidateSet(name, this.context);
        log("[" + name + ".bt] " + formatBacktrace(this.context));
      }
    });
    log("[armed] " + name + " at " + hex(address) + " rva=0x" + rva.toString(16));
  } catch (e) {
    log("[arm-failed] " + name + " at " + hex(address) + " rva=0x" + rva.toString(16) + " error=" + e);
  }
}

attachSite("CreateChunk", rvas.createChunk, "createChunk");
attachSite("CreateChunkParent", rvas.createChunkParent, "createChunkParent");
attachSite("FragmentParentA", rvas.fragmentParentA, "fragmentParentA");
attachSite("FragmentParentB", rvas.fragmentParentB, "fragmentParentB");
attachSite("FragmentParentC", rvas.fragmentParentC, "fragmentParentC");

log("redux direct fragment pointer trace armed base=" + hex(moduleBase));
