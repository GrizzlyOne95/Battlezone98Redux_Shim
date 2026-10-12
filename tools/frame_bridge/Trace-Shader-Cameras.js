// Bounded, read-only Ogre parameter trace. Load with bzr-frida.cmd against
// the PID owned by Game-Smoke-Test.ps1 -ShaderCameraTrace. Never spawn the game
// with Frida, eternalize this script, or use --kill-on-exit.
// Export names are the only locators; no object offsets or build RVAs.
'use strict';

const ogre = Process.getModuleByName('OgreMain.dll');
const dx11 = Process.getModuleByName('RenderSystem_Direct3D11.dll');
if (Process.arch !== 'ia32') throw new Error('Expected native x86 Ogre');

function body(module, name) {
    let address = module.getExportByName(name);
    for (let i = 0; i < 4; ++i) {
        if (address.compare(module.base) < 0 || address.add(32).compare(module.base.add(module.size)) > 0)
            throw new Error('Export thunk left module: ' + name);
        if (address.readU8() !== 0xe9) return address;
        address = address.add(5 + address.add(1).readS32());
    }
    throw new Error('Export thunk chain too long: ' + name);
}
function getter(name, result = 'pointer') {
    return new NativeFunction(body(ogre, name), result, ['pointer'], 'thiscall');
}
const cameraOf = getter('?getCurrentCamera@AutoParamDataSource@Ogre@@QBEPBVCamera@2@XZ');
const renderableOf = getter('?getCurrentRenderable@AutoParamDataSource@Ogre@@UBEPBVRenderable@2@XZ');
const viewportOf = getter('?_getViewport@RenderSystem@Ogre@@UAEPAVViewport@2@XZ');
const widthOf = getter('?getActualWidth@Viewport@Ogre@@QBEHXZ', 'int');
const heightOf = getter('?getActualHeight@Viewport@Ogre@@QBEHXZ', 'int');
const nearOf = getter('?getNearClipDistance@Camera@Ogre@@UBEMXZ', 'float');
const farOf = getter('?getFarClipDistance@Camera@Ogre@@UBEMXZ', 'float');
const projectionRS = getter('?getProjectionMatrixRS@Frustum@Ogre@@UBEABVMatrix4@2@XZ');
const projectionDepth = getter('?getProjectionMatrixWithRSDepth@Frustum@Ogre@@UBEABVMatrix4@2@XZ');
const viewOf = new NativeFunction(body(ogre, '?getViewMatrix@Camera@Ogre@@QBEABVMatrix4@2@_N@Z'),
    'pointer', ['pointer', 'bool'], 'thiscall');

let frame = 0, complete = false, errors = 0, overflow = 0;
const states = new Map();
const contexts = new Map();
const variants = new Map();
const listeners = [];
const maxFrames = 30, maxVariants = 128, maxSources = 32;
function emit(value) { console.log(JSON.stringify(value)); }
function matrix(pointer) {
    if (pointer.isNull()) throw new Error('Null matrix');
    const values = Array.from(new Float32Array(pointer.readByteArray(64)));
    if (!values.every(Number.isFinite)) throw new Error('Nonfinite matrix');
    return values;
}
function context(thread) {
    if (!contexts.has(thread)) {
        if (contexts.size >= 32) throw new Error('Thread observation limit exceeded');
        contexts.set(thread, { scenes: [], clears: new Map() });
    }
    return contexts.get(thread);
}
function source(pointer, thread) {
    const key = thread + ':' + pointer.toString();
    if (!states.has(key)) {
        if (states.size >= maxSources) { ++overflow; return null; }
        states.set(key, { view: null, projection: null });
    }
    return states.get(key);
}
function guarded(callback) {
    if (complete) return;
    try { callback(); } catch (error) {
        ++errors;
        if (errors <= 4) emit({ type: 'read-error', message: String(error), stack: String(error.stack) });
    }
}
function attach(module, name, callbacks) {
    const address = body(module, name);
    listeners.push(Interceptor.attach(address, callbacks));
    emit({ type: 'hook', module: module.name, export: name, address: address.toString() });
}
function finish(reason) {
    if (complete) return;
    complete = true;
    for (const listener of listeners) listener.detach();
    for (const variant of variants.values()) emit(variant);
    emit({ type: 'complete', reason, frames: Math.max(0, frame - 1), variants: variants.size, errors, overflow,
        qualification: 'parameter-getter-observations-only' });
}

// Invalidate on renderable/camera changes. A pair is never assembled from
// different objects or frames. Copy returned matrices while the getter lives.
for (const name of [
    '?setCurrentRenderable@AutoParamDataSource@Ogre@@UAEXPBVRenderable@2@@Z',
    '?setCurrentCamera@AutoParamDataSource@Ogre@@UAEXPBVCamera@2@_N@Z'
]) attach(ogre, name, { onEnter(args) { guarded(() => {
    const state = source(this.context.ecx, this.threadId);
    if (state) {
        state.view = null; state.projection = null;
        // Observe the flag rather than infer origin policy from zeros.
        if (name.includes('setCurrentCamera')) state.cameraRelative = (args[1].toUInt32() & 255) !== 0;
    }
}); } });

attach(ogre, '?_renderScene@SceneManager@Ogre@@UAEXPAVCamera@2@PAVViewport@2@_N@Z', {
    onEnter(args) { guarded(() => {
        const viewport = args[1];
        const scenes = context(this.threadId).scenes;
        if (scenes.length >= 16) throw new Error('Scene recursion limit exceeded');
        scenes.push({ camera: args[0].toString(),
            width: widthOf(viewport), height: heightOf(viewport) });
        this.entered = true;
    }); },
    onLeave() { if (this.entered) context(this.threadId).scenes.pop(); }
});
attach(dx11, '?clearFrameBuffer@D3D11RenderSystem@Ogre@@UAEXIABVColourValue@2@MG@Z', {
    onEnter(args) { guarded(() => {
        const viewport = viewportOf(this.context.ecx);
        if (!viewport.isNull() && (args[0].toUInt32() & 2)) {
            const key = widthOf(viewport) + 'x' + heightOf(viewport);
            const clears = context(this.threadId).clears;
            if (!clears.has(key) && clears.size >= 32) throw new Error('Viewport observation limit exceeded');
            clears.set(key, (clears.get(key) || 0) + 1);
        }
    }); }
});

for (const [kind, name] of [
    ['view', '?getViewMatrix@AutoParamDataSource@Ogre@@UBEABVMatrix4@2@XZ'],
    ['projection', '?getProjectionMatrix@AutoParamDataSource@Ogre@@UBEABVMatrix4@2@XZ']
]) attach(ogre, name, {
    onEnter() { this.source = this.context.ecx; },
    onLeave(result) { guarded(() => {
        if (frame === 0) return; // discard the partial frame during attachment
        const state = source(this.source, this.threadId);
        if (!state) return;
        state[kind] = matrix(result);
        if (!state.view || !state.projection) return;
        const ctx = context(this.threadId);
        const scene = ctx.scenes[ctx.scenes.length - 1];
        if (!scene || scene.width < 500 || scene.height < 500) return;
        const camera = cameraOf(this.source);
        if (camera.isNull()) return;
        const renderable = renderableOf(this.source).toString();
        const clears = ctx.clears.get(scene.width + 'x' + scene.height) || 0;
        // Quantize solely for bounded variant grouping, retain original floats.
        const key = JSON.stringify([scene.width, scene.height, clears, camera.toString(), state.cameraRelative,
            state.view.map(x => Math.round(x * 1000)), state.projection.map(x => Math.round(x * 1000))]);
        if (!variants.has(key)) {
            if (variants.size >= maxVariants) { ++overflow; return; }
            variants.set(key, { type: 'variant', firstFrame: frame, lastFrame: frame, reads: 0,
                thread: this.threadId, width: scene.width, height: scene.height,
                precedingViewportDepthClears: clears, sceneCamera: scene.camera,
                cameraRelative: state.cameraRelative === undefined ? null : state.cameraRelative,
                parameterCamera: camera.toString(), firstRenderable: renderable,
                view: state.view.slice(), projection: state.projection.slice(),
                cameraViewForShaders: matrix(viewOf(camera, 1)),
                cameraProjectionRS: matrix(projectionRS(camera)),
                cameraProjectionWithRSDepth: matrix(projectionDepth(camera)),
                nearClip: nearOf(camera), farClip: farOf(camera) });
        }
        const variant = variants.get(key);
        ++variant.reads; variant.lastFrame = frame;
    }); }
});

attach(ogre, '?_fireFrameEnded@Root@Ogre@@QAE_NAAUFrameEvent@2@@Z', {
    onLeave() { guarded(() => {
        ++frame;
        states.clear();
        for (const ctx of contexts.values()) ctx.clears.clear();
        if (frame > maxFrames) finish('frame-limit');
    }); }
});
emit({ type: 'ready', pid: Process.id, arch: Process.arch, maxFrames, maxVariants });
setTimeout(() => finish('deadline'), 12000);
