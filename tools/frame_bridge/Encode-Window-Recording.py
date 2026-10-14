"""Encode owned WGC or renderer-input recordings with explicit evidence labels."""
import argparse
import json
import shutil
import struct
import subprocess
from pathlib import Path
from PIL import Image, ImageDraw

parser=argparse.ArgumentParser()
parser.add_argument('recording',type=Path)
parser.add_argument('output',type=Path)
args=parser.parse_args()
ffmpeg=shutil.which('ffmpeg')
if not ffmpeg:
    raise RuntimeError('ffmpeg is required to encode the recording')
with args.recording.open('rb') as source:
    magic=source.read(8)
    renderer_input=magic==b'BZRINP1\0'
    if magic not in (b'BZRVID1\0',b'BZRINP1\0'):
        raise ValueError('Invalid owned-window recording')
    dimensions=source.read(8)
    if len(dimensions)!=8:
        raise ValueError('Missing recording extent')
    width,height=struct.unpack('<II',dimensions)
    if not 1<=width<=8192 or not 1<=height<=8192:
        raise ValueError('Recording extent outside bounded range')
    frame_bytes=width*height*4
    process=subprocess.Popen([ffmpeg,'-hide_banner','-loglevel','warning','-y',
        '-f','rawvideo','-pixel_format','bgra','-video_size',f'{width}x{height}','-framerate','60','-i','pipe:0',
        '-vf','scale=trunc(iw/2)*2:trunc(ih/2)*2','-c:v','libx264','-preset','veryfast','-crf','18','-pix_fmt','yuv420p',str(args.output)],
        stdin=subprocess.PIPE)
    first_time=None
    previous_time=None
    previous=None
    captured=0
    encoded=0
    last_frame=0
    last_extra=0
    try:
        while timestamp:=source.read(8):
            if len(timestamp)!=8:
                raise ValueError('Truncated recording timestamp')
            time=struct.unpack('<q',timestamp)[0]
            if renderer_input:
                info=source.read(16)
                if len(info)!=16:
                    raise ValueError('Truncated renderer frame metadata')
                frame,extra,flags=struct.unpack('<QII',info)
                if frame<=last_frame or extra<last_extra or flags>15:
                    raise ValueError('Invalid renderer frame evidence')
                last_frame,last_extra=frame,extra
            if previous_time is not None and time<=previous_time:
                raise ValueError('Non-monotonic window capture timestamp')
            pixels=source.read(frame_bytes)
            if len(pixels)!=frame_bytes:
                raise ValueError('Truncated recording frame')
            if renderer_input:
                image=Image.frombytes('RGBA',(width,height),pixels,'raw','BGRA')
                draw=ImageDraw.Draw(image)
                draw.rectangle((0,0,width,42),fill=(12,16,20,255))
                draw.text((8,5),f'Battlezone preview | DX12 cinematic: {"ON" if flags&8 else "OFF"} | DXR AO: {"ON" if flags&1 else "OFF"} | DLSS SDK extra presents: {extra}',fill='white')
                draw.text((8,23),'Recorded renderer input frames; generated-frame count comes from SDK telemetry. Camera motion only / visible geometry only.',fill='#bbbbbb')
                pixels=image.tobytes('raw','BGRA')
            if first_time is None:
                first_time=time
            # WGC supplies system-relative timestamps in 100 ns units. Sample
            # the actual capture timeline at 60 Hz, repeating the last image.
            index=round((time-first_time)*60/10_000_000)
            while previous is not None and encoded<index:
                process.stdin.write(previous)
                encoded+=1
            previous=pixels
            previous_time=time
            captured+=1
        if previous is None:
            raise ValueError('Empty owned-window recording')
        process.stdin.write(previous)
        encoded+=1
    finally:
        process.stdin.close()
        status=process.wait()
    if status:
        raise RuntimeError(f'Video encoder failed: {status}')
metadata={'source':'renderer-input-frames' if renderer_input else 'WindowsGraphicsCapture-own-helper-window','capturedFrames':captured,
          'encodedFrames':encoded,'durationSeconds':encoded/60,'width':width,'height':height,
          'presentationBenchmark':False,'generatedFramesIndependentlyCounted':False,
          'lastCapturedFrameId':last_frame if renderer_input else None,'sdkReportedExtraPresents':last_extra if renderer_input else None}
args.output.with_suffix('.mp4.json').write_text(json.dumps(metadata,indent=2)+'\n',encoding='utf-8')
print(json.dumps(metadata))
