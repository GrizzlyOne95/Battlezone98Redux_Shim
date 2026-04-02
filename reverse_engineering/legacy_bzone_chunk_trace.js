function readAscii(ptrValue, maxLen) {
  try {
    if (ptrValue.isNull()) {
      return null;
    }
    return Memory.readCString(ptrValue, maxLen);
  } catch (_e) {
    return null;
  }
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

Interceptor.attach(ptr("0x004886F7"), {
  onEnter(args) {
    const self = this.context.ecx;
    const objPtr = self.add(0xE8).readPointer();
    const namePtr = self.add(0x17C).readPointer();
    const name = readAscii(namePtr, 64) || "<none>";
    log("[Craft::Explode] this=" + hex(self) + " obj=" + hex(objPtr) + " name=" + name);
  }
});

Interceptor.attach(ptr("0x004BEF90"), {
  onEnter(args) {
    const self = this.context.ecx;
    const objPtr = args[0];
    log("[PartialFragmentObject] this=" + hex(self) + " obj=" + hex(objPtr));
  }
});

Interceptor.attach(ptr("0x004BF08B"), {
  onEnter(args) {
    const self = this.context.ecx;
    const objPtr = args[0];
    log("[FullFragmentObject] this=" + hex(self) + " obj=" + hex(objPtr));
  }
});

Interceptor.attach(ptr("0x004BE555"), {
  onEnter(args) {
    const self = this.context.ecx;
    const objPtr = args[0];
    log("[CreateChunk] this=" + hex(self) + " obj=" + hex(objPtr));
  }
});

Interceptor.attach(ptr("0x004BF165"), {
  onEnter(args) {
    const self = this.context.ecx;
    log("[CreateChunklet] this=" + hex(self));
  }
});

log("legacy chunk trace armed");
