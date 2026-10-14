"""Replay captured native building poses; never feeds stale poses into the live presenter."""
import argparse
import json
from pathlib import Path
import struct
import subprocess
import sys

import numpy as np
from PIL import Image


def metadata(path):
    return json.loads(path.read_text(encoding='utf-8-sig'))


def run(args):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('directory', type=Path)
    parser.add_argument('--revision', type=int, default=1)
    parser.add_argument('--crop', type=int, nargs=4, default=[0, 325, 800, 210])
    parser.add_argument('--helper', type=Path, default=Path(__file__).resolve().parents[2] /
                        'build/frame-bridge-x64/Release/frame_bridge_visible_rt_gpu_tests.exe')
    options = parser.parse_args(args)
    root = options.directory.resolve()
    helper = options.helper.resolve()
    terrain = root / f'native-terrain.bin.g{options.revision}.bin'
    casters = Path(str(terrain)+'.buildings.bin')
    info = metadata(Path(str(terrain)+'.json'))
    buildings = metadata(Path(str(casters)+'.json'))
    # GPU reader revalidates binary header/hash/bounds and same PID/mission.
    if (buildings['pid'], buildings['missionGeneration']) != (info['pid'], info['missionGeneration']):
        raise ValueError('Foreign building snapshot PID or mission')
    if not buildings['snapshotPoseOnly'] or buildings['liveLifetimeQualified']:
        raise ValueError('Expected explicit snapshot pose evidence')
    if not info['sunDirectionValid']:
        raise ValueError('Captured sunlight direction unavailable')
    direction = info['towardSunWorld']
    if len(direction) != 3 or not np.isfinite(direction).all() or abs(np.dot(direction, direction)-1) > .0001:
        raise ValueError('Invalid captured world sunlight direction')
    camera = metadata(root/'game-depth.pfm.json')['cameraObservation']
    if camera['observationQpc'] < buildings['observationQpc']:
        raise ValueError('Camera predates building pose snapshot')
    subprocess.run([sys.executable, str(Path(__file__).with_name('Prepare-RT-Capture.py')), str(root), '--scene-only'], check=True)
    capture = root/'rt-scene-input.bin'
    payload = capture.read_bytes()
    width, height = struct.unpack_from('<II', payload, 8)
    pixels = {}
    for mode in ('preview', 'mask'):
        for objects in (False, True):
            name = ('building' if objects else 'terrain-only')+'-shadow-'+mode
            output = root/(name+'.rgba')
            command = [str(helper), str(capture), str(output), str(terrain),
                       *[format(float(value), '.9g') for value in direction], mode]
            if objects:
                command.append(str(casters))
            subprocess.run(command, check=True)
            data = output.read_bytes()
            if len(data) != width*height*4:
                raise ValueError('Incomplete GPU replay output')
            rgba = np.frombuffer(data, np.uint8).reshape(height, width, 4)
            Image.fromarray(rgba).save(root/(name+'.png'))
            pixels[objects, mode] = rgba
    before = pixels[False, 'preview'].astype(np.int16)
    after = pixels[True, 'preview'].astype(np.int16)
    delta = np.abs(after[:, :, :3]-before[:, :, :3]).max(axis=2)
    original = np.asarray(Image.open(root/'game-scene.bmp').convert('RGBA'))
    masks = {}
    for objects in (False, True):
        mask = pixels[objects, 'mask']
        changed = np.max(np.abs(mask[:, :, :3].astype(np.int16)-original[:, :, :3]), axis=2) > 2
        masks[objects] = changed & (mask[:, :, 0] > 210) & (mask[:, :, 1] < 50) & (mask[:, :, 2] > 210)
    alpha_preserved = all(np.array_equal(image[:, :, 3], original[:, :, 3]) for image in pixels.values())
    if not alpha_preserved:
        raise ValueError('Replay altered source alpha')
    report = {'schema': 'bzr-building-shadow-replay-v1', 'frameId': metadata(root/'game-depth.pfm.json')['frameId'],
              'producerPid': info['pid'], 'missionGeneration': info['missionGeneration'],
              'terrainTriangles': info['triangles'], 'buildingTriangles': buildings['triangles'],
              'buildingSubmeshes': len(buildings['submeshes']), 'terrainGeometryHash': info['payloadHash'],
              'buildingGeometryHash': buildings['payloadHash'], 'towardSunWorld': direction,
              'terrainOnlyBlockedPixels': int(masks[False].sum()), 'withBuildingBlockedPixels': int(masks[True].sum()),
              'addedBlockedPixels': int((masks[True] & ~masks[False]).sum()),
              'changedPixelsOver2': int((delta > 2).sum()), 'maximumChannelDelta': int(delta.max()),
              'alphaPreserved': alpha_preserved, 'replayOnly': True, 'liveBuildingLifetimeQualified': False,
              'snapshotPoseSynchronizedToFinalFrame': False, 'wholeSceneQualified': False,
              'SDRLightingReplacement': False}
    (root/'building-shadow-replay-report.json').write_text(json.dumps(report, indent=2)+'\n', encoding='utf-8')
    subprocess.run([sys.executable, str(Path(__file__).with_name('Compare-RT-Captures.py')),
                    str(root/'terrain-only-shadow-preview.png'), str(root/'building-shadow-preview.png'),
                    str(root/'building-shadow-comparison.png'), '--crop', *map(str, options.crop),
                    '--before-label', 'Terrain rays only', '--after-label', 'Added native building casters'], check=True)
    print(json.dumps(report))


if __name__ == '__main__':
    run(sys.argv[1:])
