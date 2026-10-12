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
    draws = [item for item in records if item.get('type') == 'draw-group']
    if completion.get('drawGroups') != len(draws) or sum(item['calls'] for item in draws) != completion.get('drawCalls'):
        raise ValueError('Inconsistent observed draw accounting')
    if sum(item['calls'] for item in draws if item['linked']) != completion.get('linkedDrawCalls'):
        raise ValueError('Inconsistent linked draw accounting')
    for item in draws:
        if item['linked'] and (not isinstance(item['matrixVariant'], int) or
                               not 0 <= item['matrixVariant'] < len(variants)):
            raise ValueError('Draw refers to absent camera variant')
    ordered = [item for item in records if item.get('type') == 'draw-order']
    if completion.get('orderedDraws', 0) != len(ordered):
        raise ValueError('Inconsistent ordered draw accounting')
    allowed_policy = {'identity-overlay', 'alpha-coverage', 'blended', 'opaque-depth-write', 'unblended-no-depth-write'}
    ordinals = {}
    observed_groups = {}
    runs = []
    for item in ordered:
        key = (item['frame'], item['thread'])
        if not 1 <= item['frame'] <= completion.get('orderedFrames', 0) or item['ordinal'] != ordinals.get(key, 0) + 1:
            raise ValueError('Ordered draw sequence is incomplete or non-monotonic')
        ordinals[key] = item['ordinal']
        group = item['group']
        if not isinstance(group, int) or not 0 <= group < len(draws):
            raise ValueError('Ordered draw refers to absent group')
        observed_groups[group] = observed_groups.get(group, 0) + 1
        if observed_groups[group] > draws[group]['calls']:
            raise ValueError('Ordered draw count exceeds group observations')
        policy = item['policyCandidate']
        if policy not in allowed_policy or policy != draws[group]['policyCandidate']:
            raise ValueError('Ordered draw policy disagrees with observed group')
        description = draws[group]['targetDescription']
        signature = (item['frame'], item['thread'], item['width'], item['height'], item['precedingViewportDepthClears'],
                     draws[group]['renderTarget'], policy)
        if not runs or runs[-1]['signature'] != signature:
            runs.append({'signature': signature, 'frame': item['frame'], 'width': item['width'], 'height': item['height'],
                         'clearSegment': item['precedingViewportDepthClears'], 'policyCandidate': policy,
                         'firstOrdinal': item['ordinal'], 'lastOrdinal': item['ordinal'], 'calls': 0,
                         'renderTarget': draws[group]['renderTarget'], 'targetDescription': description})
        run = runs[-1]
        run['calls'] += 1
        run['lastOrdinal'] = item['ordinal']
    for run in runs:
        del run['signature']
    objects = [item for item in records if item.get('type') == 'object-transform-group']
    if completion.get('objectTransformGroups', 0) != len(objects):
        raise ValueError('Inconsistent object observation accounting')
    for item in objects:
        if not 1 <= item['transformCount'] <= 256 or item['lifetimeQualified'] is not False:
            raise ValueError('Object count/lifetime observation invalid')
        difference(item['firstMatrix'], item['lastMatrix'])
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
        'candidateOnly': True, 'qualification': 'parameter-binding-draw-observations-only',
        'completion': completion,
        'boundedTraceClean': completion['reason'] == 'frame-limit' and completion['frames'] == 30
            and completion['errors'] == 0 and completion['overflow'] == 0,
        'variants': rows,
        'drawGroups': draws,
        'objectTransformGroups': objects,
        'orderedDraws': ordered,
        'drawPolicyRuns': runs,
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
          f"clean={summary['boundedTraceClean']} (draw/binding observations only)")
    for row in summary['variants']:
        print(f"  viewport={row['width']}x{row['height']} clear-segment={row['precedingViewportDepthClears']} reads={row['reads']} "
              f"camera={row['parameterCamera']} view-match={row['viewMatchesCameraForShaders']} "
              f"camera-relative-match={row['viewMatchesCameraRelative']} "
              f"identity-view={row['identityView']} RS-match={row['projectionMatchesRS']} "
              f"RS-depth-match={row['projectionMatchesRSDepth']}")
    print(f"DRAWS total={summary['completion']['drawCalls']} linked={summary['completion']['linkedDrawCalls']} "
          '(bound-buffer identity verified; contents and shader consumption unqualified)')
    print(f"OBJECTS groups={len(summary['objectTransformGroups'])} "
          f"single_transform_candidates={sum(r['rigidCandidate'] for r in summary['objectTransformGroups'])} "
          f"changed_groups={sum(r['changedPairs'] > 0 for r in summary['objectTransformGroups'])} "
          '(renderable lifetimes and dense object motion unqualified)')
    print(f"ORDER draws={len(summary['orderedDraws'])} policy_runs={len(summary['drawPolicyRuns'])} "
          '(blend/depth policies are candidates, not semantic opacity masks)')
    for run in summary['drawPolicyRuns']:
        target = run['targetDescription']
        if run['frame'] == 1 and target and target['format'] in (28, 87):
            print(f"  segment={run['clearSegment']} viewport={run['width']}x{run['height']} "
                  f"target={target['width']}x{target['height']} samples={target['samples']} "
                  f"draws={run['firstOrdinal']}..{run['lastOrdinal']} {run['policyCandidate']}")
    print(output)


if __name__ == '__main__':
    main()
