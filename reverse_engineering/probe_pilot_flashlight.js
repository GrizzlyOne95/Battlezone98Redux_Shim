// Read-only pilot flashlight siting probe (released GOG battlezone98redux.exe).
//
// Answers, in one run, the questions the 2026-09-05 investigation left open:
//   1. Does the local Person's render bridge carry a first-person entity at
//      +0xC0 while on foot, and is it attached to a scene node?
//   2. Where is that node in world space relative to the world pilot node
//      at +0x98 (i.e. is the FP entity a world-space sibling, or parked at
//      the origin / attached to nothing)?
//   3. What are the *21mg1 gun bone's derived position and orientation in
//      the FP skeleton, so a light offset can be measured rather than guessed?
//   4. Does the pilot's world node orientation carry look pitch (the property
//      a node-attached, stock-style headlight would need to follow aim)?
//
// Nothing is created, attached, or mutated. Bridge field names come from the
// released FUN_0067f599 (world) and FUN_0067e6a8 (first person) setup bodies.

const exe = Process.getModuleByName('battlezone98redux.exe');
const ogre = Process.getModuleByName('OgreMain.dll');

function fn(name, ret, args) {
    return new NativeFunction(ogre.getExportByName(name), ret, args, 'thiscall');
}

const entGetSkeleton = fn('?getSkeleton@Entity@Ogre@@QBEPAVSkeletonInstance@2@XZ', 'pointer', ['pointer']);
const moGetName = fn('?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ', 'pointer', ['pointer']);
const moGetParentNode = fn('?getParentNode@MovableObject@Ogre@@UBEPAVNode@2@XZ', 'pointer', ['pointer']);
const moGetVisible = fn('?getVisible@MovableObject@Ogre@@UBE_NXZ', 'bool', ['pointer']);
const skelNumBones = fn('?getNumBones@Skeleton@Ogre@@UBEGXZ', 'uint16', ['pointer']);
const skelGetBone = fn('?getBone@Skeleton@Ogre@@UBEPAVBone@2@G@Z', 'pointer', ['pointer', 'uint16']);
const nodeGetName = fn('?getName@Node@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ', 'pointer', ['pointer']);
const nodeDerivedPos = fn('?_getDerivedPosition@Node@Ogre@@UBEABVVector3@2@XZ', 'pointer', ['pointer']);
const nodeDerivedOri = fn('?_getDerivedOrientation@Node@Ogre@@UBEABVQuaternion@2@XZ', 'pointer', ['pointer']);
const nodeGetParent = fn('?getParent@Node@Ogre@@UBEPAV12@XZ', 'pointer', ['pointer']);

// Person::Simulate on the released GOG build; the local-player object slot.
const kPersonSimulateRva = 0x19D340;
const kLocalPlayerRva = 0x517AFC;
const kPersonRenderBridge = 0xF0;

// Render bridge layout, from the released setup bodies.
const BRIDGE = {
    worldEntity: 0x94,
    worldNode: 0x98,
    worldSkeleton: 0xA4,
    headlight: 0xA8,
    gc1Bone: 0xAC,
    sm1Bone: 0xB0,
    fpEntity: 0xC0,
    fpIdleAnim: 0xC4,
    fpSkeleton: 0xCC,
    povBone: 0xE0,
};

function str(p) {
    if (p.isNull()) return '<null>';
    const cap = p.add(20).readU32();
    const len = p.add(16).readU32();
    const buf = cap >= 16 ? p.readPointer() : p;
    if (buf.isNull() || len > 512) return '<bad>';
    return buf.readUtf8String(len);
}

function v3(p) {
    if (p.isNull()) return null;
    return [p.readFloat(), p.add(4).readFloat(), p.add(8).readFloat()];
}

// Ogre stores Quaternion as w,x,y,z.
function quat(p) {
    if (p.isNull()) return null;
    return [p.readFloat(), p.add(4).readFloat(), p.add(8).readFloat(), p.add(12).readFloat()];
}

// Rotate a vector by an Ogre quaternion (w,x,y,z), so the probe can report
// where a bone/node actually points rather than raw components.
function rotate(q, v) {
    const [w, x, y, z] = q;
    const ux = y * v[2] - z * v[1];
    const uy = z * v[0] - x * v[2];
    const uz = x * v[1] - y * v[0];
    const vx = y * uz - z * uy;
    const vy = z * ux - x * uz;
    const vz = x * uy - y * ux;
    return [
        v[0] + 2 * (w * ux + vx),
        v[1] + 2 * (w * uy + vy),
        v[2] + 2 * (w * uz + vz),
    ];
}

function r3(a) {
    return a ? a.map(function (n) { return Math.round(n * 10000) / 10000; }) : null;
}

function ptr32(p, off) {
    const q = p.add(off).readPointer();
    return q.isNull() ? null : q;
}

function nodeInfo(node) {
    if (!node) return null;
    const q = quat(nodeDerivedOri(node));
    return {
        p: node,
        name: str(nodeGetName(node)),
        pos: r3(v3(nodeDerivedPos(node))),
        quat: r3(q),
        // -Z is Ogre's conventional forward; +Y its up.
        fwd: r3(rotate(q, [0, 0, -1])),
        up: r3(rotate(q, [0, 1, 0])),
        parent: (function () {
            const par = nodeGetParent(node);
            return par.isNull() ? null : str(nodeGetName(par));
        })(),
    };
}

function bones(skel, filter) {
    if (!skel) return [];
    const out = [];
    const n = skelNumBones(skel);
    for (let i = 0; i < n; i++) {
        const b = skelGetBone(skel, i);
        if (b.isNull()) continue;
        const name = str(nodeGetName(b));
        if (filter && !filter.test(name)) continue;
        const q = quat(nodeDerivedOri(b));
        out.push({
            i: i,
            name: name,
            dpos: r3(v3(nodeDerivedPos(b))),
            dquat: r3(q),
            dfwd: r3(rotate(q, [0, 0, -1])),
            parent: (function () {
                const par = nodeGetParent(b);
                return par.isNull() ? null : str(nodeGetName(par));
            })(),
        });
    }
    return out;
}

let last = 0;
let samples = 0;
const INTERVAL_MS = 1000;
// A gun bone matches *21mg1; the aim/head candidates are kept for contrast.
const INTERESTING = /(21mg1|11gc1|11pov|Bip01_Head|Bip01_Neck|Bip01$)/i;

Interceptor.attach(exe.base.add(kPersonSimulateRva), {
    onEnter: function () {
        this.person = this.context.ecx;
    },
    onLeave: function () {
        const now = Date.now();
        if (now - last < INTERVAL_MS) return;
        let local;
        try {
            local = exe.base.add(kLocalPlayerRva).readPointer();
        } catch (e) {
            return;
        }
        if (!local.equals(this.person)) return;
        last = now;
        samples++;

        try {
            const bridge = ptr32(this.person, kPersonRenderBridge);
            if (!bridge) {
                console.log(JSON.stringify({ sample: samples, err: 'no render bridge' }));
                return;
            }

            const fields = {};
            for (const k in BRIDGE) fields[k] = ptr32(bridge, BRIDGE[k]);

            const worldNode = fields.worldNode;
            const fpEntity = fields.fpEntity;
            const fpParent = fpEntity ? (function () {
                const n = moGetParentNode(fpEntity);
                return n.isNull() ? null : n;
            })() : null;

            const rec = {
                sample: samples,
                person: this.person,
                bridge: bridge,
                fields: fields,
                worldEntity: fields.worldEntity ? {
                    name: str(moGetName(fields.worldEntity)),
                    visible: moGetVisible(fields.worldEntity),
                } : null,
                fpEntityInfo: fpEntity ? {
                    name: str(moGetName(fpEntity)),
                    visible: moGetVisible(fpEntity),
                    parentIsWorldNode: !!(fpParent && worldNode && fpParent.equals(worldNode)),
                } : null,
                worldNode: nodeInfo(worldNode),
                fpParentNode: nodeInfo(fpParent),
                povBone: fields.povBone ? nodeInfo(fields.povBone) : null,
                fpBones: bones(fields.fpSkeleton, INTERESTING),
                worldBones: bones(fields.worldSkeleton, INTERESTING),
            };
            console.log('PFL ' + JSON.stringify(rec));
        } catch (e) {
            console.log('PFL_ERR ' + String(e));
        }
    },
});

console.log('PILOT_FLASHLIGHT_PROBE_READY pid=' + Process.id +
    ' exe=' + exe.base + ' ogre=' + ogre.base);
