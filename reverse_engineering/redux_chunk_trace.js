const moduleName = "battlezone98redux.exe";
const moduleBase = Process.getModuleByName(moduleName).base;

const rvAs = {
  chunkEffectSimulate: 0x000917F0,
  createChunk: 0x00092AA0,
  createChunklet: 0x000927D0,
  observedChunkletCallerSite: 0x000AAC35
};

const budgets = {
  createChunk: 8,
  createChunklet: 16,
  observedCallerSite: 12
};

function at(rva) {
  return moduleBase.add(rva);
}

function hex(value) {
  return ptr(value).toString();
}

function now() {
  return new Date().toISOString();
}

function log(message) {
  console.log("[" + now() + "] " + message);
}

function attachSafe(name, rva, callbacks) {
  const address = at(rva);
  try {
    Interceptor.attach(address, callbacks);
    log("[armed] " + name + " at " + hex(address) + " rva=0x" + rva.toString(16));
  } catch (e) {
    log("[arm-failed] " + name + " at " + hex(address) + " rva=0x" + rva.toString(16) + " error=" + e);
  }
}

function safeReadPointer(address) {
  try {
    return ptr(address).readPointer();
  } catch (_e) {
    return ptr(0);
  }
}

function safeReadFloat(address) {
  try {
    return ptr(address).readFloat();
  } catch (_e) {
    return NaN;
  }
}

function formatVec3(ptrValue) {
  if (ptr(ptrValue).isNull()) {
    return "<null>";
  }
  const x = safeReadFloat(ptrValue);
  const y = safeReadFloat(ptr(ptrValue).add(4));
  const z = safeReadFloat(ptr(ptrValue).add(8));
  return "(" + x.toFixed(4) + ", " + y.toFixed(4) + ", " + z.toFixed(4) + ")";
}

function formatBacktrace(context) {
  let frames = [];
  try {
    frames = Thread.backtrace(context, Backtracer.ACCURATE);
  } catch (_e) {
    frames = Thread.backtrace(context, Backtracer.FUZZY);
  }
  frames = frames.slice(0, 12).map((addr, index) => {
    const symbol = DebugSymbol.fromAddress(addr);
    return "#" + index + " " + symbol.toString();
  });
  return frames.join(" | ");
}

function safeReadU32(address) {
  try {
    return ptr(address).readU32();
  } catch (_e) {
    return null;
  }
}

function formatStackWords(stackPtr, count) {
  if (ptr(stackPtr).isNull()) {
    return "<null>";
  }
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

attachSafe("ChunkEffect::CreateChunk", rvAs.createChunk, {
  onEnter(args) {
    const self = this.context.ecx;
    const objPtr = args[0];
    const velocityPtr = args[1];
    const preserveFlag = args[2].toInt32() & 0xFF;
    if (budgets.createChunk > 0) {
      budgets.createChunk--;
      log("[CreateChunk] this=" + hex(self) +
        " obj=" + hex(objPtr) +
        " preserve=" + preserveFlag +
        " vel=" + formatVec3(velocityPtr) +
        " caller=" + hex(this.returnAddress));
      log("[CreateChunk.regs] " + formatRegs(this.context));
      log("[CreateChunk.stack] " + formatStackWords(this.context.esp, 8));
      log("[CreateChunk.bt] " + formatBacktrace(this.context));
    }
  }
});

attachSafe("ChunkEffect::CreateChunklet", rvAs.createChunklet, {
  onEnter(args) {
    const self = this.context.ecx;
    const positionPtr = args[0];
    const velocityPtr = args[1];
    const preserveFlag = args[2].toInt32() & 0xFF;
    if (budgets.createChunklet > 0) {
      budgets.createChunklet--;
      log("[CreateChunklet] this=" + hex(self) +
        " pos=" + formatVec3(positionPtr) +
        " vel=" + formatVec3(velocityPtr) +
        " preserve=" + preserveFlag +
        " caller=" + hex(this.returnAddress));
      log("[CreateChunklet.regs] " + formatRegs(this.context));
      log("[CreateChunklet.stack] " + formatStackWords(this.context.esp, 10));
      log("[CreateChunklet.bt] " + formatBacktrace(this.context));
    }
  }
});

attachSafe("ChunkEffect::Simulate", rvAs.chunkEffectSimulate, {
  onEnter(_args) {
  }
});

attachSafe("ObservedCallerSite_0xAAC35", rvAs.observedChunkletCallerSite, {
  onEnter(_args) {
    if (budgets.observedCallerSite > 0) {
      budgets.observedCallerSite--;
      log("[CallerSite 0xAAC35] ecx=" + hex(this.context.ecx) +
        " eax=" + hex(this.context.eax) +
        " return=" + hex(safeReadPointer(this.context.esp)));
      log("[CallerSite.regs] " + formatRegs(this.context));
      log("[CallerSite.stack] " + formatStackWords(this.context.esp, 10));
      log("[CallerSite.bt] " + formatBacktrace(this.context));
    }
  }
});

log("redux chunk trace armed base=" + hex(moduleBase));
