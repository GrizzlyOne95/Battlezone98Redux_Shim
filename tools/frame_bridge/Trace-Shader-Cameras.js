// Bounded, read-only Ogre parameter trace. Load with bzr-frida.cmd against
// the PID owned by Game-Smoke-Test.ps1 -ShaderCameraTrace. Never spawn the game
// with Frida, eternalize this script, or use --kill-on-exit.
// Export names locate engine objects; no game object offsets or build RVAs.
// Returned strings use the bounded MSVC x86 ABI, checked against PlayerCam.
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
        const next = address.add(5 + address.add(1).readS32());
        // Allow the task's qualified native parameter observer at an export
        // body; attach there and observe its normal return. Other external
        // trampolines still fail closed.
        const owner = Process.findModuleByAddress(next);
        if (owner && owner.name.toLowerCase() === 'openshim.dll') return address;
        address = next;
    }
    throw new Error('Export thunk chain too long: ' + name);
}
function getter(name, result = 'pointer') {
    return new NativeFunction(body(ogre, name), result, ['pointer'], 'thiscall');
}
const cameraOf = getter('?getCurrentCamera@AutoParamDataSource@Ogre@@QBEPBVCamera@2@XZ');
const renderableOf = getter('?getCurrentRenderable@AutoParamDataSource@Ogre@@UBEPBVRenderable@2@XZ');
const worldCountOf = getter('?getWorldMatrixCount@AutoParamDataSource@Ogre@@UBEIXZ', 'uint');
const cameraPositionOf = getter('?getDerivedPosition@Camera@Ogre@@QBEABVVector3@2@XZ');
const cameraNameOf = getter('?getName@MovableObject@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ');
const passOf = getter('?getCurrentPass@AutoParamDataSource@Ogre@@UBEPBVPass@2@XZ');
const techniqueOf = getter('?getParent@Pass@Ogre@@QBEPAVTechnique@2@XZ');
const materialOf = getter('?getParent@Technique@Ogre@@QBEPAVMaterial@2@XZ');
const materialNameOf = getter('?getName@Resource@Ogre@@UBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ');
const passNameOf = getter('?getName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ');
const fragmentNameOf = getter('?getFragmentProgramName@Pass@Ogre@@QBEABV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ');
const alphaFunctionOf = getter('?getAlphaRejectFunction@Pass@Ogre@@QBE?AW4CompareFunction@2@XZ','uint');
const alphaValueOf = getter('?getAlphaRejectValue@Pass@Ogre@@QBEEXZ','uchar');
const viewportOf = getter('?_getViewport@RenderSystem@Ogre@@UAEPAVViewport@2@XZ');
const widthOf = getter('?getActualWidth@Viewport@Ogre@@QBEHXZ', 'int');
const heightOf = getter('?getActualHeight@Viewport@Ogre@@QBEHXZ', 'int');
const nearOf = getter('?getNearClipDistance@Camera@Ogre@@UBEMXZ', 'float');
const farOf = getter('?getFarClipDistance@Camera@Ogre@@UBEMXZ', 'float');
const projectionRS = getter('?getProjectionMatrixRS@Frustum@Ogre@@UBEABVMatrix4@2@XZ');
const projectionDepth = getter('?getProjectionMatrixWithRSDepth@Frustum@Ogre@@UBEABVMatrix4@2@XZ');
const viewOf = new NativeFunction(body(ogre, '?getViewMatrix@Camera@Ogre@@QBEABVMatrix4@2@_N@Z'),
    'pointer', ['pointer', 'bool'], 'thiscall');
const deviceOf = new NativeFunction(body(dx11, '?_getDevice@D3D11RenderSystem@Ogre@@QAEAAVD3D11Device@2@XZ'),
    'pointer', ['pointer'], 'thiscall');
const immediateOf = new NativeFunction(body(dx11, '?GetImmediateContext@D3D11Device@Ogre@@QAEPAUID3D11DeviceContext@@XZ'),
    'pointer', ['pointer'], 'thiscall');

let frame = 0, complete = false, errors = 0, overflow = 0;
const states = new Map();
const contexts = new Map();
const variants = new Map();
const parameters = new Map();
const draws = new Map();
const drawHooks = new Set();
const transforms = new Map();
const orderedDraws = [];
const listeners = [];
const maxFrames = 30, maxVariants = 128, maxSources = 32;
let drawCalls = 0, linkedDrawCalls = 0;
let stringLayoutChecked=false;
function stringOf(value) {
    if(value.isNull()) throw new Error('Null returned Ogre string');
    const size=value.add(16).readU32(),capacity=value.add(20).readU32();
    if(size>512||capacity<size||capacity>1024*1024) throw new Error('Returned string ABI/bounds mismatch');
    const data=capacity<16?value:value.readPointer();
    const text=size?data.readUtf8String(size):'';
    if(text.includes('\u0000')) throw new Error('Embedded null in observed name');
    return text;
}
function passInfo(source) {
    if(!stringLayoutChecked) {
        const camera=cameraOf(source);
        if(camera.isNull()||stringOf(cameraNameOf(camera))!=='PlayerCam') return null;
        stringLayoutChecked=true;
    }
    const pass=passOf(source);
    if(pass.isNull()) return null;
    const technique=techniqueOf(pass),material=technique.isNull()?ptr(0):materialOf(technique);
    return {material:material.isNull()?null:stringOf(materialNameOf(material)),pass:stringOf(passNameOf(pass)),
        fragmentProgram:stringOf(fragmentNameOf(pass)),alphaRejectFunction:alphaFunctionOf(pass),alphaRejectValue:alphaValueOf(pass)};
}
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
        contexts.set(thread, { scenes: [], clears: new Map(), bindings: [], renders: [], vertex: null, apiDepth: 0, drawOrdinal: 0 });
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
    for (const draw of draws.values()) emit(draw);
    for (const transform of transforms.values()) emit(transform);
    for (const draw of orderedDraws) emit(draw);
    emit({ type: 'complete', reason, frames: Math.max(0, frame - 1), variants: variants.size, errors, overflow,
        drawGroups: draws.size, drawCalls, linkedDrawCalls,
        objectTransformGroups: transforms.size,
        orderedDraws: orderedDraws.length, orderedFrames: Math.min(3, Math.max(0, frame - 1)),
        stringLayoutChecked,
        qualification: 'parameter-binding-draw-observations-only' });
}

// Invalidate on renderable/camera changes. A pair is never assembled from
// different objects or frames. Copy returned matrices while the getter lives.
for (const name of [
    '?setCurrentRenderable@AutoParamDataSource@Ogre@@UAEXPBVRenderable@2@@Z',
    '?setCurrentCamera@AutoParamDataSource@Ogre@@UAEXPBVCamera@2@_N@Z'
]) attach(ogre, name, { onEnter(args) { guarded(() => {
    const state = source(this.context.ecx, this.threadId);
    if (state) {
        state.view = null; state.projection = null; state.variantKey = null; state.world = null;
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

attach(ogre, '?getWorldMatrix@AutoParamDataSource@Ogre@@UBEABVMatrix4@2@XZ', {
    onEnter() { this.source = this.context.ecx; },
    onLeave(result) { guarded(() => {
        const ctx = context(this.threadId);
        if (frame === 0 || ctx.readingWorld) return;
        const state = source(this.source, this.threadId);
        if (!state) return;
        const renderable = renderableOf(this.source);
        if (renderable.isNull()) { state.world = null; return; }
        let count;
        ctx.readingWorld = true;
        try { count = worldCountOf(this.source); } finally { ctx.readingWorld = false; }
        if (!count || count > 256) { state.world = null; ++overflow; return; }
        const camera = cameraOf(this.source);
        if (camera.isNull()) { state.world = null; return; }
        const position = Array.from(new Float32Array(cameraPositionOf(camera).readByteArray(12)));
        if (!position.every(Number.isFinite)) throw new Error('Nonfinite camera origin');
        state.world = { matrix: matrix(result), count, renderable: renderable.toString(), position };
    }); }
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
        if (!scene || scene.width < 1 || scene.height < 1 || scene.width > 8192 || scene.height > 8192) return;
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
        state.variantKey = key;
    }); }
});

// Cache only owned observation identities for this frame, never Ogre objects.
// A partial parameter update can retain an earlier complete pair only for the
// same source/renderable generation (setCurrentRenderable invalidates it).
attach(ogre, '?_updateAutoParams@GpuProgramParameters@Ogre@@QAEXPBVAutoParamDataSource@2@G@Z', {
    onEnter(args) {
        this.parameter = this.context.ecx.toString(); this.source = args[0];
        parameters.delete(this.threadId + ':' + this.parameter);
    },
    onLeave() { guarded(() => {
        if (frame === 0) return;
        const state = source(this.source, this.threadId);
        if (!state || !state.variantKey) return;
        const key = this.threadId + ':' + this.parameter;
        if (!parameters.has(key) && parameters.size >= 1024) { ++overflow; return; }
        parameters.set(key, { variantKey: state.variantKey, frame, world: state.world || null, pass:passInfo(this.source) });
    }); }
});
attach(dx11, '?bindGpuProgramParameters@D3D11RenderSystem@Ogre@@UAEXW4GpuProgramType@2@V?$SharedPtr@VGpuProgramParameters@Ogre@@@2@G@Z', {
    onEnter(args) { guarded(() => {
        const ctx = context(this.threadId);
        if (ctx.bindings.length >= 16) throw new Error('Parameter binding recursion limit exceeded');
        // GOG x86 exported ABI: enum + by-value two-pointer Ogre SharedPtr.
        // The first SharedPtr word is the parameter identity. No fields read.
        ctx.bindings.push({ stage: args[0].toUInt32(), parameter: args[1].toString(), buffer: null,
            observation: parameters.get(this.threadId + ':' + args[1].toString()) || null });
        this.entered = true;
    }); },
    onLeave() { guarded(() => {
        if (!this.entered) return;
        const ctx = context(this.threadId), binding = ctx.bindings.pop();
        if (binding.stage === 0) ctx.vertex = binding;
    }); }
});
attach(dx11, '?getConstantBuffer@D3D11HLSLProgram@Ogre@@QAEPAUID3D11Buffer@@V?$SharedPtr@VGpuProgramParameters@Ogre@@@2@G@Z', {
    onEnter(args) { this.parameter = args[0].toString(); },
    onLeave(result) { guarded(() => {
        const stack = context(this.threadId).bindings;
        const binding = stack[stack.length - 1];
        if (binding && binding.parameter === this.parameter) binding.buffer = result.toString();
    }); }
});

function com(object, slot, result, args) {
    return new NativeFunction(object.readPointer().add(slot * 4).readPointer(), result,
        ['pointer', ...args], 'stdcall');
}
function release(object) { if (!object.isNull()) com(object, 2, 'uint', [])(object); }
function recordTransform(observation, scene, clears) {
    if (!observation.world || !scene) return;
    const world = observation.world, variant = variants.get(observation.variantKey);
    const close = (a, b) => a.every((v, i) => Math.abs(v - b[i]) < 0.0001);
    const expectedView = variant.cameraViewForShaders.slice();
    if (variant.cameraRelative === true) for (const at of [3, 7, 11]) expectedView[at] = 0;
    const affine = world.matrix.slice(12).every((v, i) => Math.abs(v - (i === 3 ? 1 : 0)) < 0.0001);
    const rigidCandidate = world.count === 1 && affine && variant.cameraRelative !== null &&
        close(variant.view, expectedView) && close(variant.projection, variant.cameraProjectionWithRSDepth) &&
        Math.abs(variant.projection[15]) < 0.0001 && Math.abs(variant.projection[14]) > 0.9;
    const absolute = world.matrix.slice();
    if (rigidCandidate && variant.cameraRelative) for (let i = 0; i < 3; ++i) absolute[i * 4 + 3] += world.position[i];
    const key = JSON.stringify([world.renderable, scene.width, scene.height, clears, variant.parameterCamera, world.count, rigidCandidate]);
    if (!transforms.has(key)) {
        if (transforms.size >= 2048) { ++overflow; return; }
        transforms.set(key, { type: 'object-transform-group', renderable: world.renderable, width: scene.width, height: scene.height,
            precedingViewportDepthClears: clears, parameterCamera: variant.parameterCamera,
            transformCount: world.count, rigidCandidate, lifetimeQualified: false,
            matrixSpace: rigidCandidate ? 'absolute-world-candidate' : 'raw-auto-param-first-matrix',
            firstFrame: frame, lastFrame: frame, calls: 0, consecutivePairs: 0, changedPairs: 0, withinFrameConflicts: 0,
            firstMatrix: absolute.slice(), lastMatrix: absolute.slice(), cameraRelative: variant.cameraRelative });
    }
    const record = transforms.get(key);
    if (record.calls) {
        const changed = !close(record.lastMatrix, absolute);
        if (frame === record.lastFrame && changed) ++record.withinFrameConflicts;
        else if (frame === record.lastFrame + 1) {
            ++record.consecutivePairs; if (changed) ++record.changedPairs;
        }
    }
    ++record.calls; record.lastFrame = frame; record.lastMatrix = absolute;
}
function bindingsAtDraw(immediate) {
    const bufferOut = Memory.alloc(4), depthOut = Memory.alloc(4), stateOut = Memory.alloc(4), stencil = Memory.alloc(4);
    bufferOut.writePointer(ptr(0)); depthOut.writePointer(ptr(0)); stateOut.writePointer(ptr(0));
    const blendOut=Memory.alloc(4), factors=Memory.alloc(16), mask=Memory.alloc(4), targetOut=Memory.alloc(4), shaderOut=Memory.alloc(4);
    blendOut.writePointer(ptr(0)); targetOut.writePointer(ptr(0)); shaderOut.writePointer(ptr(0));
    let buffer = ptr(0), depth = ptr(0), depthState = ptr(0), blend=ptr(0), target=ptr(0), resource=ptr(0), shader=ptr(0);
    try {
        // Documented D3D11 API slots; getters AddRef, balanced in finally.
        com(immediate, 72, 'void', ['uint', 'uint', 'pointer'])(immediate, 0, 1, bufferOut);
        buffer = bufferOut.readPointer();
        com(immediate, 89, 'void', ['uint', 'pointer', 'pointer'])(immediate, 1, targetOut, depthOut);
        depth = depthOut.readPointer();
        target = targetOut.readPointer();
        com(immediate, 92, 'void', ['pointer', 'pointer'])(immediate, stateOut, stencil);
        depthState = stateOut.readPointer();
        let depthPolicy = { enabled:true, writeMask:1, comparison:2, defaultState:true };
        if (!depthState.isNull()) {
            const desc = Memory.alloc(52);
            com(depthState, 7, 'void', ['pointer'])(depthState, desc);
            depthPolicy = { enabled: desc.readU32() !== 0, writeMask: desc.add(4).readU32(), comparison: desc.add(8).readU32(), defaultState:false };
        }
        com(immediate,91,'void',['pointer','pointer','pointer'])(immediate,blendOut,factors,mask);
        blend=blendOut.readPointer();
        let blendPolicy={enabled:false,alphaToCoverage:false,independent:false,source:2,destination:1,operation:1,
            sourceAlpha:2,destinationAlpha:1,operationAlpha:1,writeMask:15,defaultState:true};
        if(!blend.isNull()) {
            const desc=Memory.alloc(264); com(blend,7,'void',['pointer'])(blend,desc);
            const rt=desc.add(8);
            blendPolicy={enabled:rt.readU32()!==0,alphaToCoverage:desc.readU32()!==0,independent:desc.add(4).readU32()!==0,
                source:rt.add(4).readU32(),destination:rt.add(8).readU32(),operation:rt.add(12).readU32(),
                sourceAlpha:rt.add(16).readU32(),destinationAlpha:rt.add(20).readU32(),operationAlpha:rt.add(24).readU32(),
                writeMask:rt.add(28).readU8(),defaultState:false};
        }
        blendPolicy.sampleMask=mask.readU32();
        let targetDescription=null;
        if(!target.isNull()) {
            const out=Memory.alloc(4); out.writePointer(ptr(0)); com(target,7,'void',['pointer'])(target,out); resource=out.readPointer();
            if(!resource.isNull()) {
                const type=Memory.alloc(4); com(resource,7,'void',['pointer'])(resource,type);
                if(type.readU32()===3) { // D3D11_RESOURCE_DIMENSION_TEXTURE2D.
                    const desc=Memory.alloc(44); com(resource,10,'void',['pointer'])(resource,desc);
                    targetDescription={width:desc.readU32(),height:desc.add(4).readU32(),format:desc.add(16).readU32(),samples:desc.add(20).readU32()};
                }
            }
        }
        com(immediate,74,'void',['pointer','pointer','pointer'])(immediate,shaderOut,ptr(0),ptr(0)); shader=shaderOut.readPointer();
        let description = null;
        if (!depth.isNull()) {
            const desc = Memory.alloc(24);
            com(depth, 8, 'void', ['pointer'])(depth, desc);
            description = { format: desc.readU32(), dimension: desc.add(4).readU32() };
        }
        return { buffer: buffer.toString(), depth: depth.toString(), depthDescription: description, depthPolicy,
            blendPolicy,target:target.toString(),targetDescription,pixelShader:shader.toString() };
    } finally { release(shader); release(resource); release(target); release(blend); release(depthState); release(depth); release(buffer); }
}
function attachDraws(immediate) {
    for (const [slot, name] of [[12, 'DrawIndexed'], [13, 'Draw'], [20, 'DrawIndexedInstanced'],
        [21, 'DrawInstanced'], [38, 'DrawAuto'], [39, 'DrawIndexedInstancedIndirect'], [40, 'DrawInstancedIndirect']]) {
        const address = immediate.readPointer().add(slot * 4).readPointer();
        const hookKey = name + ':' + address;
        if (drawHooks.has(hookKey)) continue;
        if (drawHooks.size >= 64) { ++overflow; return; }
        drawHooks.add(hookKey);
        listeners.push(Interceptor.attach(address, {
            onEnter(args) { guarded(() => {
                if (frame === 0) return;
                const ctx = context(this.threadId), render = ctx.renders[ctx.renders.length - 1];
                if (!render || !args[0].equals(render.immediate)) return;
                // Wrapper/internal forwarding can hit multiple observed slots.
                ++ctx.apiDepth; this.entered = true;
                if (ctx.apiDepth !== 1) return;
                ++drawCalls;
                const bindings = bindingsAtDraw(args[0]);
                const vertex = ctx.vertex;
                const observation = vertex && vertex.observation;
                const linked = !!(vertex && vertex.buffer && vertex.buffer !== '0x0' &&
                    vertex.buffer === bindings.buffer && observation && observation.frame === frame);
                if (linked) ++linkedDrawCalls;
                const scene = ctx.scenes[ctx.scenes.length - 1];
                const clears = scene ? ctx.clears.get(scene.width + 'x' + scene.height) || 0 : 0;
                const variantKey = linked ? observation.variantKey : null;
                if (linked) recordTransform(observation, scene, clears);
                const variant=linked?variants.get(variantKey):null;
                const identity=!!(variant&&variant.view.every((v,i)=>Math.abs(v-(i%5===0?1:0))<.00001));
                const b=bindings.blendPolicy,d=bindings.depthPolicy;
                const mixes=b.enabled&&!(b.source===2&&b.destination===1&&b.operation===1);
                const policyCandidate=identity?'identity-overlay':b.alphaToCoverage?'alpha-coverage':mixes?'blended':
                    d.enabled&&d.writeMask===1?'opaque-depth-write':'unblended-no-depth-write';
                const key = JSON.stringify([name, scene && scene.width, scene && scene.height, clears,
                    bindings.depth, bindings.buffer, bindings.depthPolicy,bindings.blendPolicy,bindings.target,bindings.pixelShader,linked?observation.pass:null,variantKey]);
                if (!draws.has(key)) {
                    if (draws.size >= 2048) { ++overflow; return; }
                    draws.set(key, { type: 'draw-group', method: name, firstFrame: frame, lastFrame: frame,
                        calls: 0, width: scene ? scene.width : 0, height: scene ? scene.height : 0,
                        precedingViewportDepthClears: clears, depthView: bindings.depth,
                        depthDescription: bindings.depthDescription, vertexConstantBuffer: bindings.buffer,
                        depthPolicy: bindings.depthPolicy,
                        blendPolicy:bindings.blendPolicy,renderTarget:bindings.target,targetDescription:bindings.targetDescription,
                        pixelShader:bindings.pixelShader,policyCandidate,
                        passObservation:linked?observation.pass:null,
                        linked, parameterCamera: linked ? variants.get(variantKey).parameterCamera : null,
                        matrixVariant: linked ? Array.from(variants.keys()).indexOf(variantKey) : null });
                }
                const draw = draws.get(key); ++draw.calls; draw.lastFrame = frame;
                ++ctx.drawOrdinal;
                if(frame<=3) {
                    if(orderedDraws.length>=4096) { ++overflow; return; }
                    orderedDraws.push({type:'draw-order',frame,thread:this.threadId,ordinal:ctx.drawOrdinal,
                        group:Array.from(draws.keys()).indexOf(key),method:name,
                        count:slot===38||slot===39||slot===40?null:args[1].toUInt32(),
                        width:draw.width,height:draw.height,precedingViewportDepthClears:clears,
                        policyCandidate,renderable:linked&&observation.world?observation.world.renderable:null});
                }
            }); },
            onLeave() { if (this.entered) --context(this.threadId).apiDepth; }
        }));
        emit({ type: 'draw-hook', method: name, address: address.toString() });
    }
}
attach(dx11, '?_render@D3D11RenderSystem@Ogre@@UAEXABVRenderOperation@2@@Z', {
    onEnter() { guarded(() => {
        const ctx = context(this.threadId);
        if (ctx.renders.length >= 16) throw new Error('Render recursion limit exceeded');
        const immediate = immediateOf(deviceOf(this.context.ecx));
        if (immediate.isNull()) throw new Error('Missing immediate context');
        attachDraws(immediate);
        ctx.renders.push({ immediate }); this.entered = true;
    }); },
    onLeave() { if (this.entered) context(this.threadId).renders.pop(); }
});

attach(ogre, '?_fireFrameEnded@Root@Ogre@@QAE_NAAUFrameEvent@2@@Z', {
    onLeave() { guarded(() => {
        ++frame;
        states.clear();
        parameters.clear();
        for (const ctx of contexts.values()) { ctx.clears.clear(); ctx.vertex = null; ctx.drawOrdinal=0; }
        if (frame > maxFrames) finish('frame-limit');
    }); }
});
emit({ type: 'ready', pid: Process.id, arch: Process.arch, maxFrames, maxVariants });
setTimeout(() => finish('deadline'), 12000);
