"""Describe observed scene layers without inferring an opacity mask from blend state."""
import argparse
import importlib.util
import json
from pathlib import Path


def classify(draw):
    info = draw.get('passObservation') or {}
    program = info.get('fragmentProgram')
    depth = draw.get('depthPolicy') or {}
    blend = draw.get('blendPolicy') or {}
    if draw.get('policyCandidate') == 'identity-overlay':
        return 'compositor' if program and 'Glow' in program else 'identity-overlay'
    if not program:
        return 'unknown'
    if program == 'Sky_fragment':
        return 'sky'
    if program == 'Effect_fragment' and depth.get('enabled') and depth.get('writeMask') == 0 and blend.get('enabled'):
        return 'world-effect-candidate'
    if depth.get('enabled') and depth.get('writeMask') == 1:
        return 'depth-writing-material'
    return 'unknown'


def analyze(summary):
    if not summary['boundedTraceClean'] or not summary['completion'].get('stringLayoutChecked'):
        raise ValueError('Requires clean bounded trace with checked material-string ABI')
    groups = summary['drawGroups']
    targets = [d['targetDescription'] for d in groups if d.get('targetDescription') and d['targetDescription']['format'] in (28, 87)
               and d.get('policyCandidate') == 'identity-overlay']
    if not targets:
        raise ValueError('No observed identity-overlay SDR color target')
    target = max(targets, key=lambda d: d['width'] * d['height'])
    width, height = target['width'], target['height']
    inventory = {}
    for draw in groups:
        if (draw['width'], draw['height']) != (width, height):
            continue
        info = draw.get('passObservation') or {}
        layer = classify(draw)
        key = (info.get('material'), info.get('fragmentProgram'), layer, draw['precedingViewportDepthClears'])
        if key not in inventory:
            inventory[key] = {'material': key[0], 'fragmentProgram': key[1], 'layerCandidate': layer, 'clearSegment': key[3], 'calls': 0}
        inventory[key]['calls'] += draw['calls']
    per_frame = {}
    for order in summary['orderedDraws']:
        if (order['width'], order['height']) != (width, height):
            continue
        draw = groups[order['group']]
        key = (order['frame'], order['thread'])
        state = per_frame.setdefault(key, {'frame': order['frame'], 'thread': order['thread'], 'firstWorldEffectOrdinal': None,
                                           'laterDepthWritingDraws': 0, 'worldEffectDraws': 0, 'overlayDraws': 0})
        layer = classify(draw)
        if layer == 'world-effect-candidate':
            state['worldEffectDraws'] += 1
            if state['firstWorldEffectOrdinal'] is None:
                state['firstWorldEffectOrdinal'] = order['ordinal']
        elif layer == 'depth-writing-material' and state['firstWorldEffectOrdinal'] is not None:
            state['laterDepthWritingDraws'] += 1
        elif layer == 'identity-overlay':
            state['overlayDraws'] += 1
    frames = list(per_frame.values())
    if not frames or not any(f['worldEffectDraws'] for f in frames):
        raise ValueError('No ordered main-view world effects')
    return {'diagnosticOnly': True, 'opacityMaskQualified': False, 'opaqueSceneQualified': False,
            'mainView': {'width': width, 'height': height}, 'observedFrames': frames, 'materials': list(inventory.values()),
            'firstBlendedDrawIsSafeOpaqueBoundary': False,
            'worldEffectsInterleavedWithDepthWriters': any(f['laterDepthWritingDraws'] for f in frames)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('trace', type=Path)
    args = parser.parse_args()
    spec = importlib.util.spec_from_file_location('shader_camera_inspector', Path(__file__).with_name('Inspect-Shader-Cameras.py'))
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    result = analyze(module.inspect(args.trace))
    output = args.trace.with_suffix('.layers.json')
    output.write_text(json.dumps(result, indent=2) + '\n', encoding='utf-8')
    print(f"LAYERS {result['mainView']} interleaved={result['worldEffectsInterleavedWithDepthWriters']} opacity_mask_qualified=False")
    for frame in result['observedFrames']:
        print(f"  frame={frame['frame']} effect_draws={frame['worldEffectDraws']} later_depth_writers={frame['laterDepthWritingDraws']} overlay_draws={frame['overlayDraws']}")
    print(output)


if __name__ == '__main__':
    main()
