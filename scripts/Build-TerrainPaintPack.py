#!/usr/bin/env python3
"""Build a map-bound four-material paint pack; never edit gameplay terrain."""
import argparse
import base64
import importlib.util
import io
import json
import math
from pathlib import Path
import re
import sys

from PIL import Image

_spec = importlib.util.spec_from_file_location("terrain_hd_pack", Path(__file__).with_name("Build-TerrainHdPack.py"))
_hd = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_hd)


def normalize(pixel):
    total = sum(pixel)
    if total == 0:
        return (255, 0, 0, 0)
    values = [v * 255 / total for v in pixel]
    result = [math.floor(v) for v in values]
    for i in sorted(range(4), key=lambda i: (values[i] - result[i], -i), reverse=True)[:255 - sum(result)]:
        result[i] += 1
    return tuple(result)


def paint_stroke(image, bounds, layer, x, z, radius, strength):
    """Circular soft brush in native world metres; rows increase toward +Z."""
    if type(layer) is not int or not 0 <= layer < 4 or any(
        type(v) not in (float, int) or not math.isfinite(v) for v in (x, z, radius, strength)
    ) or radius <= 0 or not 0 <= strength <= 1:
        raise ValueError("stroke needs layer 0..3, finite coordinates, positive radius and strength 0..1")
    sx = (bounds[2] - bounds[0]) / image.width
    sz = (bounds[3] - bounds[1]) / image.height
    pixels = image.load()
    for py in range(max(0, math.floor((z-radius-bounds[1])/sz)), min(image.height, math.ceil((z+radius-bounds[1])/sz))):
        for px in range(max(0, math.floor((x-radius-bounds[0])/sx)), min(image.width, math.ceil((x+radius-bounds[0])/sx))):
            distance = math.hypot(bounds[0]+(px+0.5)*sx-x, bounds[1]+(py+0.5)*sz-z) / radius
            if distance >= 1:
                continue
            influence = strength * (1-distance)**2 * (1+2*distance)
            old = normalize(pixels[px, py])
            pixels[px, py] = normalize([old[i]*(1-influence) + (255*influence if i == layer else 0) for i in range(4)])


def validate_map(mapping):
    if not isinstance(mapping, dict) or not re.fullmatch(r"[0-9a-f]{16}", mapping.get("terrainFingerprint", "")):
        raise ValueError("capture needs a paintMap from the current native exporter")
    bounds = mapping.get("boundsMeters", [])
    if len(bounds) != 4 or any(type(v) not in (int, float) or not math.isfinite(v) or abs(v) > 1000000 for v in bounds):
        raise ValueError("invalid paint map bounds")
    if bounds[2] <= bounds[0] or bounds[3] <= bounds[1] or mapping.get("rowZero") != "minZ":
        raise ValueError("paint map needs positive extents and minZ row order")
    return bounds


def build_pack(capture_path, recipe_path, source_root, output, size=2048, weight_size=1024,
               weights_path=None, prefix="openshim_mars_paint", force=False):
    capture = _hd.read_json(capture_path)
    recipe = _hd.read_json(recipe_path)
    if capture.get("schema") != "bzr-openshim-terrain-atlas-v1" or not capture.get("material") or not capture.get("diffuseResource"):
        raise ValueError("input must be a native atlas/map capture")
    mapping = capture.get("paintMap")
    bounds = validate_map(mapping)
    if recipe.get("schema") != "bzr-openshim-terrain-paint-art-v1" or len(recipe.get("layers", [])) != 4:
        raise ValueError("recipe needs exactly four material layers")
    if size not in (64,128,256,512,1024,2048) or weight_size not in (64,128,256,512,1024,2048):
        raise ValueError("material and weight sizes must be powers of two from 64 to 2048")
    if not re.fullmatch(r"[a-z][a-z0-9_]{0,63}", prefix):
        raise ValueError("invalid resource prefix")
    root = Path(source_root).resolve()
    output = Path(output)
    if output.exists() and any(output.iterdir()) and not force:
        raise ValueError("output is non-empty; use --force for this pack")
    # Validate all art and parameters before publishing resources/manifest.
    layers, identities, repeats = [], [], []
    for layer in recipe["layers"]:
        repeat = layer.get("repeatMeters")
        if type(repeat) not in (int,float) or not math.isfinite(repeat) or not 1 <= repeat <= 4096 or not layer.get("name"):
            raise ValueError("each layer needs a name and repeatMeters from 1 to 4096")
        art, identity = _hd.load_art(root, layer)
        layers.append(art.resize((size,size), Image.Resampling.LANCZOS).convert("RGBA"))
        identities.append(identity)
        repeats.append(repeat)
    if weights_path:
        with Image.open(weights_path) as source:
            if source.mode != "RGBA" or source.width != source.height or source.width not in (64,128,256,512,1024,2048):
                raise ValueError("weights must be a square RGBA PNG with four linear weight channels")
            weights = source.copy()
        weight_size = weights.width
    else:
        base = recipe.get("baseLayer", 0)
        if type(base) is not int or not 0 <= base < 4:
            raise ValueError("baseLayer must be 0..3")
        weights = Image.new("RGBA", (weight_size,weight_size), tuple(255 if i == base else 0 for i in range(4)))
        # Recipe strokes use normalized map coordinates so the demonstration
        # stays portable. They are authoring operations, not engine tile edits.
        for stroke in recipe.get("strokes", []):
            x, z, radius = stroke["x"], stroke["z"], stroke["radius"]
            if any(type(v) not in (int,float) or not math.isfinite(v) for v in (x,z,radius)):
                raise ValueError("stroke map coordinates must be finite")
            paint_stroke(weights, bounds, stroke["layer"], bounds[0]+x*(bounds[2]-bounds[0]),
                         bounds[1]+z*(bounds[3]-bounds[1]), radius*min(bounds[2]-bounds[0],bounds[3]-bounds[1]), stroke["strength"])
    weights.putdata([normalize(p) for p in weights.getdata()])
    # The prototype uses one five-slice array. All slices have the same upload
    # size, although the editable source control map has independent resolution.
    # RGBA image resizing premultiplies RGB by alpha. Alpha here is the fourth
    # weight, so resample four independent linear data channels instead.
    control = Image.merge("RGBA", tuple(channel.resize((size,size), Image.Resampling.BILINEAR)
                                         for channel in weights.split()))
    control.putdata([normalize(p) for p in control.getdata()])
    output.mkdir(parents=True, exist_ok=True)
    resources = [f"{prefix}_layer{i}.png" for i in range(4)] + [f"{prefix}_control.png"]
    for resource, image in zip(resources, layers+[control]):
        image.save(output/resource)
    weights.save(output/f"{prefix}_weights.png")
    paint = {"schema":"bzr-openshim-terrain-paint-v1", "terrainFingerprint":mapping["terrainFingerprint"],
             "boundsMeters":bounds, "rowZero":"minZ", "repeatMeters":repeats}
    binding = {"sliceCount":5, "diffuseResource":capture["diffuseResource"], "fallback":resources[0],
               "tiles":{str(i):name for i,name in enumerate(resources)}, "paint":paint}
    manifest = {"schema":"bzr-openshim-terrain-hd-v1", "materials":{capture["material"]:binding}}
    (output/f"{prefix}.json").write_text(json.dumps(manifest,indent=2)+"\n", encoding="utf-8")
    project = {"schema":"bzr-openshim-terrain-paint-project-v1", "paint":paint, "prefix":prefix,
               "materialSize":size, "weightSize":weight_size, "layers":recipe["layers"], "sources":identities}
    (output/f"{prefix}_project.json").write_text(json.dumps(project,indent=2)+"\n",encoding="utf-8")
    previews = []
    for image in layers:
        stream=io.BytesIO(); image.resize((128,128),Image.Resampling.LANCZOS).save(stream,format="PNG")
        previews.append("data:image/png;base64,"+base64.b64encode(stream.getvalue()).decode("ascii"))
    payload = dict(project, previews=previews, weights=base64.b64encode(weights.tobytes()).decode("ascii"))
    template = Path(__file__).with_name("terrain-paint-editor.html").read_text(encoding="utf-8")
    # Prevent artist-authored names from terminating the embedded JSON script.
    html = template.replace("__PAINT_PROJECT__",json.dumps(payload).replace("<","\\u003c"))
    html = html.replace("__PAINT_CODE__", Path(__file__).with_name("terrain-paint-codec.js").read_text(encoding="utf-8"))
    (output/f"{prefix}_editor.html").write_text(html,encoding="utf-8")
    return manifest


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ("capture","recipe","source-root","output"):
        parser.add_argument("--"+name,required=True)
    parser.add_argument("--size",type=int,default=2048)
    parser.add_argument("--weight-size",type=int,default=1024)
    parser.add_argument("--weights",help="edited RGBA PNG; overrides recipe strokes")
    parser.add_argument("--prefix",default="openshim_mars_paint")
    parser.add_argument("--force",action="store_true")
    args=parser.parse_args()
    try:
        result=build_pack(args.capture,args.recipe,args.source_root,args.output,args.size,args.weight_size,args.weights,args.prefix,args.force)
        print(f"Built four-material paint pack: {args.output}; map {next(iter(result['materials'].values()))['paint']['terrainFingerprint']}")
    except (OSError,ValueError,KeyError,TypeError) as error:
        parser.exit(1,f"Paint pack declined: {error}\n")


if __name__ == "__main__":
    main()
