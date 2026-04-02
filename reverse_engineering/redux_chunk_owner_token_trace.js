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
  throw new Error("unable to resolve main module");
}

const mainModule = resolveMainModule();
const moduleBase = mainModule.base;

const rvas = {
  createChunkParent: 0x000924f5,
  fragmentParentA: 0x000ac5e0
};

const budgets = {
  createChunkParent: 24,
  fragmentParentA: 24
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

function safeReadAscii(address, maxLen) {
  try {
    return ptr(address).readCString(maxLen);
  } catch (_e) {
    return "";
  }
}

function looksLikeGamePtr(value) {
  const n = ptr(value).toUInt32();
  return n >= 0x01000000 && n < 0x7fff0000 && (n % 4) === 0;
}

function normalizeToken(raw) {
  if (!raw) {
    return "";
  }
  return raw.replace(/\0.*$/, "").replace(/[^A-Za-z0-9_]/g, "").toLowerCase();
}

function readInlineOwnerNames(candidate) {
  if (ptr(candidate).isNull() || !looksLikeGamePtr(candidate)) {
    return null;
  }

  const baseC4 = safeReadAscii(ptr(candidate).add(0xc4), 16);
  const base84 = safeReadAscii(ptr(candidate).add(0x84), 16);
  const fileD4 = safeReadAscii(ptr(candidate).add(0xd4), 16);
  const file94 = safeReadAscii(ptr(candidate).add(0x94), 16);
  return {
    baseC4,
    base84,
    fileD4,
    file94
  };
}

function summarizeGameObject(gameObjectPtr) {
  const p = ptr(gameObjectPtr);
  if (p.isNull() || !looksLikeGamePtr(p)) {
    return null;
  }

  const obj76 = safeReadPtr(p.add(0xf4));
  const classPtr = safeReadPtr(p.add(0xf8));
  let odf = "";
  if (!classPtr.isNull()) {
    odf = normalizeToken(safeReadAscii(classPtr.add(0x20), 16));
  }
  const names = readInlineOwnerNames(p);
  return {
    ptr: p,
    obj76,
    classPtr,
    odf,
    names
  };
}

function summarizeObj76(objPtr) {
  const p = ptr(objPtr);
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

  return {
    ptr: p,
    classId,
    parent,
    sibling,
    child,
    gameObj,
    bridge
  };
}

function logObj76(label, summary) {
  if (!summary) {
    return;
  }

  log("[" + label + ".obj76] obj=" + hex(summary.ptr) +
    " class=" + summary.classId +
    " parent=" + hex(summary.parent) +
    " sibling=" + hex(summary.sibling) +
    " child=" + hex(summary.child) +
    " gameObj=" + hex(summary.gameObj) +
    " bridge=" + hex(summary.bridge));

  const go = summarizeGameObject(summary.gameObj);
  if (go) {
    const names = go.names || {};
    log("[" + label + ".gameObj] ptr=" + hex(go.ptr) +
      " obj76=" + hex(go.obj76) +
      " classPtr=" + hex(go.classPtr) +
      " odf=" + (go.odf || "<none>") +
      " baseC4=" + (names.baseC4 || "<none>") +
      " base84=" + (names.base84 || "<none>") +
      " fileD4=" + (names.fileD4 || "<none>") +
      " file94=" + (names.file94 || "<none>"));
  }
}

function candidatePtr(value) {
  return ptr(value);
}

function maybeLogRootChain(tag, context) {
  const candidates = [
    ["edx", candidatePtr(context.edx)],
    ["ecx", candidatePtr(context.ecx)],
    ["stack3", safeReadPtr(context.esp.add(0x0c))],
    ["stack4", safeReadPtr(context.esp.add(0x10))],
    ["stack5", safeReadPtr(context.esp.add(0x14))]
  ];

  for (const [label, candidate] of candidates) {
    const summary = summarizeObj76(candidate);
    if (!summary) {
      continue;
    }

    if (summary.classId === 1 || !summary.gameObj.isNull() || !summary.child.isNull()) {
      logObj76(tag + "." + label, summary);
    }
  }
}

function attachSite(name, rva, budgetKey, onEnterExtra) {
  const address = at(rva);
  try {
    Interceptor.attach(address, {
      onEnter(args) {
        if (budgets[budgetKey] <= 0) {
          return;
        }
        budgets[budgetKey]--;
        log("[" + name + "] at=" + hex(address) + " return=" + hex(this.returnAddress));
        onEnterExtra(this.context, args);
      }
    });
    log("[armed] " + name + " at " + hex(address) + " rva=0x" + rva.toString(16));
  } catch (e) {
    log("[arm-failed] " + name + " at " + hex(address) + " rva=0x" + rva.toString(16) + " error=" + e);
  }
}

attachSite("CreateChunkParent", rvas.createChunkParent, "createChunkParent", (context, _args) => {
  maybeLogRootChain("CreateChunkParent", context);
});

attachSite("FragmentParentA", rvas.fragmentParentA, "fragmentParentA", (context, _args) => {
  maybeLogRootChain("FragmentParentA", context);
});

log("redux chunk owner token trace armed base=" + hex(moduleBase));
