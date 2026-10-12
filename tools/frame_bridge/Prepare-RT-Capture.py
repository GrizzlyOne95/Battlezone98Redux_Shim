"""Package an owned matched scene/depth capture for the DXR GPU diagnostic."""
import argparse
import json
import struct
from pathlib import Path
from PIL import Image

parser=argparse.ArgumentParser()
parser.add_argument('directory',type=Path)
args=parser.parse_args()
root=args.directory
scene_metadata=json.loads((root/'game-scene.bmp.json').read_text(encoding='utf-8-sig'))
depth_metadata=json.loads((root/'game-depth.pfm.json').read_text(encoding='utf-8-sig'))
if scene_metadata['frameId']!=depth_metadata['frameId'] or scene_metadata['stage']!=1:
    raise ValueError('Requires matched before-overlay color and depth')
scene=Image.open(root/'game-scene.bmp').convert('RGBA')
final=Image.open(root/'game-frame.bmp').convert('RGBA')
width,height=scene.size
if final.size!=scene.size or (width,height)!=(scene_metadata['width'],scene_metadata['height']):
    raise ValueError('Capture extents differ')
with (root/'game-depth.pfm').open('rb') as source:
    if source.readline()!=b'Pf\n' or source.readline().strip()!=f'{width} {height}'.encode() or source.readline()!=b'-1.0\n':
        raise ValueError('Requires single-channel little-endian PFM')
    data=source.read()
if len(data)!=width*height*4:
    raise ValueError('Invalid depth payload size')
depth=b''.join(data[y*width*4:(y+1)*width*4] for y in range(height-1,-1,-1))
camera=scene_metadata['cameraObservation']
output=root/'rt-capture-input.bin'
output.write_bytes(b'BZRCAP1\0'+struct.pack('<II',width,height)+
                  struct.pack('<34f',*camera['projection'],*camera['view'],camera['nearClip'],camera['farClip'])+
                  depth+scene.tobytes()+final.tobytes())
print(f'PACKAGED frame={scene_metadata["frameId"]} {width}x{height} {output}')
