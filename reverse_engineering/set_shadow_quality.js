// Shadow-cutoff probe: sets BZR's shadow-quality/detail settings bytes,
// re-applies the shadow configuration exactly as the game's own options
// setters do, then interposes Light::getShadowFarDistance for a bounded
// window to record what the CPU shadow-camera fit actually clips against.
//
// Addresses are GOG 2.2.301 VAs minus the 0x400000 default image base:
//   DAT_0094672c -> settings struct pointer      (VA 0x0094672c)
//   FUN_00680fe0  -> shadow/viewport apply       (VA 0x00680fe0)
//   Light::getShadowFarDistance export

const SETTINGS_PTR_RVA = 0x54672c;
const APPLY_SHADOW_RVA = 0x280fe0;

const mod = Process.getModuleByName("battlezone98redux.exe");
const base = mod.base;
const settingsPtr = base.add(SETTINGS_PTR_RVA).readPointer();
console.log(
    "[SHADOWSET] base=" + base +
    " settings=" + settingsPtr +
    " quality=" + settingsPtr.add(0x25).readS8() +
    " detail=" + settingsPtr.add(0x27).readU8());

settingsPtr.add(0x25).writeS8(3);   // 3 = PSSM, 2048
settingsPtr.add(0x27).writeU8(0);   // scheme detail "high"

const applyShadowConfig = new NativeFunction(
    base.add(APPLY_SHADOW_RVA), "void", []);
applyShadowConfig();

console.log(
    "[SHADOWSET] applied quality=" + settingsPtr.add(0x25).readS8() +
    " detail=" + settingsPtr.add(0x27).readU8());

// Interpose the per-light shadow far distance for a bounded number of calls.
// The Focused/PSSM body-B clip uses this value, so the logged numbers are
// what actually bounds the fitted cascade coverage. The shipped OgreMain
// exports this non-virtually (QBEM, not vanilla 1.10's UBEM).
const getShadowFarDistanceAddr =
    Module.getGlobalExportByName("?getShadowFarDistance@Light@Ogre@@QBEMXZ");
if (getShadowFarDistanceAddr) {
    let calls = 0;
    const seen = {};
    const interceptor = Interceptor.attach(getShadowFarDistanceAddr, {
        onLeave: function (retval) {
            calls++;
            const value = retval.toFloat().toFixed(2);
            seen[value] = (seen[value] || 0) + 1;
            if (calls >= 2000) {
                console.log("[SHADOWFAR] calls=" + calls +
                    " values=" + JSON.stringify(seen));
                interceptor.detach();
            }
        }
    });
    setTimeout(function () {
        console.log("[SHADOWFAR] window-end calls=" + calls +
            " values=" + JSON.stringify(seen));
    }, 8000);
} else {
    console.log("[SHADOWFAR] export not found");
}

// Also record what the scene manager is told: this is the origin of the clip.
const setShadowFarDistanceAddr =
    Module.getGlobalExportByName("?setShadowFarDistance@SceneManager@Ogre@@UAEXM");
if (setShadowFarDistanceAddr) {
    Interceptor.attach(setShadowFarDistanceAddr, {
        onEnter: function (args) {
            console.log("[SHADOWFAR] setShadowFarDistance(" +
                args[0].toFloat() + ")");
        }
    });
}
