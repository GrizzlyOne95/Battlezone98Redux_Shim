"""Compare bounded Ogre parameter observations with camera API conventions.

This describes getter results, not shader coverage, draw/depth ownership or
motion-vector validity. Runtime identities and trace artifacts stay in build/.
"""
import argparse
import json
import math
from pathlib import Path


def difference(a, b):
    if len(a) != 16 or len(b) != 16 or not all(math.isfinite(x) for x in a + b):
        raise ValueError('Expected two finite 4x4 matrices')
    return max(abs(x - y) for x, y in zip(a, b))


def inspect(path):
    records = [json.loads(line) for line in path.read_text(encoding='utf-8-sig').splitlines()
               if line.startswith('{')]
    completions = [item for item in records if item.get('type') == 'complete']
    if len(completions) != 1:
        raise ValueError('Expected one completed trace')
    completion = completions[0]
    variants = [item for item in records if item.get('type') == 'variant']
    if not variants or completion['variants'] != len(variants):
        raise ValueError('Trace has no consistent matrix observations')
    identity = [1 if i % 5 == 0 else 0 for i in range(16)]
    rows = []
    for item in variants:
        view_delta = difference(item['view'], item['cameraViewForShaders'])
        rs_delta = difference(item['projection'], item['cameraProjectionRS'])
        depth_delta = difference(item['projection'], item['cameraProjectionWithRSDepth'])
        identity_delta = difference(item['view'], identity)
        relative_view = item['cameraViewForShaders'].copy()
        for at in (3, 7, 11):
            relative_view[at] = 0
        relative_delta = difference(item['view'], relative_view)
        rows.append({
            'firstFrame': item['firstFrame'], 'lastFrame': item['lastFrame'], 'reads': item['reads'],
            'width': item['width'], 'height': item['height'],
            'precedingViewportDepthClears': item['precedingViewportDepthClears'],
            'cameraRelative': item['cameraRelative'],
            'sceneCamera': item['sceneCamera'], 'parameterCamera': item['parameterCamera'],
            'viewMatchesCameraForShaders': view_delta < 0.0001,
            'identityView': identity_delta < 0.0001,
            'viewMatchesCameraRelative': item['cameraRelative'] is True and relative_delta < 0.0001,
            'projectionMatchesRS': rs_delta < 0.0001,
            'projectionMatchesRSDepth': depth_delta < 0.0001,
            'maxViewDifference': view_delta, 'maxProjectionRSDifference': rs_delta,
            'maxProjectionRSDepthDifference': depth_delta,
            'nearClip': item['nearClip'], 'farClip': item['farClip'],
        })
    summary = {
        'candidateOnly': True, 'qualification': 'parameter-getter-observations-only',
        'completion': completion,
        'boundedTraceClean': completion['reason'] == 'frame-limit' and completion['frames'] == 30
            and completion['errors'] == 0 and completion['overflow'] == 0,
        'variants': rows,
    }
    return summary


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('trace', type=Path)
    args = parser.parse_args()
    summary = inspect(args.trace)
    output = args.trace.with_suffix('.summary.json')
    output.write_text(json.dumps(summary, indent=2, allow_nan=False) + '\n', encoding='utf-8')
    print(f"TRACE frames={summary['completion']['frames']} variants={len(summary['variants'])} "
          f"clean={summary['boundedTraceClean']} (getter observations only)")
    for row in summary['variants']:
        print(f"  viewport={row['width']}x{row['height']} clear-segment={row['precedingViewportDepthClears']} reads={row['reads']} "
              f"camera={row['parameterCamera']} view-match={row['viewMatchesCameraForShaders']} "
              f"camera-relative-match={row['viewMatchesCameraRelative']} "
              f"identity-view={row['identityView']} RS-match={row['projectionMatchesRS']} "
              f"RS-depth-match={row['projectionMatchesRSDepth']}")
    print(output)


if __name__ == '__main__':
    main()
