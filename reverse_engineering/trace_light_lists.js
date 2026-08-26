// Logs per-object light lists produced by SceneManager::_populateLightList
// so the headlight's presence/position in each renderable's list can be
// observed directly instead of inferred.
//
// Signature (thiscall, x86): void _populateLightList(
//     const Vector3& position, Real radius, LightList& destList, uint32 mask)
// Frida x86 Interceptor.args therefore are:
//   args[0] = &position   args[1] = radius (raw float bits)
//   args[2] = &destList   args[3] = mask      (this = ECX)
// LightList is std::vector<Light*>: {begin, end, capacity}.
//
// _populateLightList body RVA in shipped OgreMain.dll: 0x003B3930 (verified
// in docs/DX11_ENHANCED_DYNAMIC_LIGHT_AUDIT.md against the released DLL).

const SETTINGS_PTR_RVA = 0x54672c;
const APPLY_SHADOW_RVA = 0x280fe0;
const POPULATE_LIGHT_LIST_RVA = 0x3b3930;

const ogre = Process.getModuleByName("OgreMain.dll");
const exe = Process.getModuleByName("battlezone98redux.exe");

const getType = new NativeFunction(
    Module.getGlobalExportByName("?getType@Light@Ogre@@QBE?AW4LightTypes@12@XZ"),
    "int", ["pointer"]);

const exeBase = exe.base;
const settingsPtr = exeBase.add(SETTINGS_PTR_RVA).readPointer();
settingsPtr.add(0x25).writeS8(3);
settingsPtr.add(0x27).writeU8(0);
new NativeFunction(exeBase.add(APPLY_SHADOW_RVA), "void", [])();
console.log("[SHADOWSET] applied quality=3 detail=0");

function readStdString(sstr) {
    // MSVC x86 std::string: 16-byte SSO buffer/pointer union, then size (+16)
    // and capacity (+20). Heap-backed when capacity >= 16.
    try {
        const capacity = sstr.add(20).readU32();
        const size = sstr.add(16).readU32();
        const dataPtr = capacity >= 16 ? sstr.readPointer() : sstr;
        return dataPtr.readUtf8String(size);
    } catch (e) {
        return "<unreadable>";
    }
}

let headlight = null;
let calls = 0;
let logged = 0;
const LIMIT = 400;

Interceptor.attach(ogre.base.add(POPULATE_LIGHT_LIST_RVA), {
    onEnter: function (args) {
        this.positionPtr = args[0];
        this.listPtr = args[2];
    },
    onLeave: function (retval) {
        calls++;
        if (calls <= 5) {
            console.log("[LIGHTLIST] call#=" + calls +
                " ecx=" + this.context.ecx +
                " posPtr=" + this.positionPtr +
                " listPtr=" + this.listPtr);
        }
        if (logged >= LIMIT) return;
        let begin, end;
        try {
            begin = this.listPtr.readPointer();
            end = this.listPtr.add(4).readPointer();
        } catch (e) { return; }
        const count = end.sub(begin).toInt32() / 4;
        if (count <= 0 || count > 64) return;

        let px, py, pz;
        try {
            px = this.positionPtr.readFloat();
            py = this.positionPtr.add(4).readFloat();
            pz = this.positionPtr.add(8).readFloat();
        } catch (e) { return; }
        if (!isFinite(px) || Math.abs(px) > 100000) return;

        const parts = [];
        try {
            const n = Math.min(count, 6);
            for (let i = 0; i < n; i++) {
                const light = begin.add(i * 4).readPointer();
                const t = getType(light);
                if (t === 2 && headlight === null) {
                    headlight = light;
                    console.log("[LIGHTLIST] first spotlight (player headlight) = " + light);
                }
                parts.push(t + ":" + light.toString(16).slice(-6));
            }
        } catch (e) { return; }

        logged++;
        if (logged % 4 === 0) {
            const marker = (headlight !== null &&
                begin.readPointer().equals(headlight)) ? " HEADLIGHTFIRST" : "";
            console.log("[LIGHTLIST] pos=(" + px.toFixed(1) + "," +
                py.toFixed(1) + "," + pz.toFixed(1) + ") n=" + count +
                " [" + parts.join(",") + "]" + marker);
        }
    }
});
console.log("[LIGHTLIST] hooked " + ogre.base.add(POPULATE_LIGHT_LIST_RVA));
