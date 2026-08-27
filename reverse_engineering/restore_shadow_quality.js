// Restores the shadow-quality setting this workstation originally had
// (quality = -1, shadows disabled; observed before any harness mutation) and
// re-applies, so the game persists the original value on exit exactly as if
// the harness had never touched it.

const SETTINGS_PTR_RVA = 0x54672c;
const APPLY_SHADOW_RVA = 0x280fe0;

const exe = Process.getModuleByName("battlezone98redux.exe");
const settingsPtr = exe.base.add(SETTINGS_PTR_RVA).readPointer();
console.log(
    "[SHADOWRESTORE] before quality=" + settingsPtr.add(0x25).readS8() +
    " detail=" + settingsPtr.add(0x27).readU8());

settingsPtr.add(0x25).writeS8(-1);
settingsPtr.add(0x27).writeU8(0);
new NativeFunction(exe.base.add(APPLY_SHADOW_RVA), "void", [])();

console.log(
    "[SHADOWRESTORE] applied quality=" + settingsPtr.add(0x25).readS8() +
    " detail=" + settingsPtr.add(0x27).readU8());
