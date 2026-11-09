"""Copy a multi-map terrain HD manifest and add each world's autopaint recipe
as paint.live, so OPENSHIM_TERRAIN_PAINT_LIVE=1 can paint missions that have
no baked entry. Baked entries are left exactly as they are.

    python scripts/Add-LivePaintRecipe.py <cr_terrain_hd.json> <output.json>

The world comes from the material's diffuseResource (<world>_atlas_d.dds); the
recipe from scripts/terrain-packs/<world>-autopaint-<N>layer.json when present
(N = the pack's layer count, e.g. CR's 4-layer Mars pack), else
<world>-autopaint.json. Materials without a multi-map paint block, without a
recipe, or whose recipe has a different layer count from the pack are copied
unchanged.
"""
import json
from pathlib import Path
import sys

RECIPES = Path(__file__).with_name("terrain-packs")


def main(source, output):
    manifest = json.loads(Path(source).read_text(encoding="utf-8"))
    for name, material in manifest["materials"].items():
        paint = material.get("paint")
        world = material.get("diffuseResource", "").split("_atlas_d.")[0]
        # 18 slices = 8 layers, as the loader counts them.
        layers = 8 if len(material.get("tiles", [])) == 18 else 4
        recipe = RECIPES / f"{world}-autopaint-{layers}layer.json"
        if not recipe.exists():
            recipe = RECIPES / f"{world}-autopaint.json"
        if not paint or not paint.get("maps") or not recipe.exists():
            print(f"{name}: unchanged")
            continue
        live = json.loads(recipe.read_text(encoding="utf-8"))
        if len(live["layers"]) != layers:
            print(f"{name}: unchanged, {recipe.name} has {len(live['layers'])} layers and the pack {layers}")
            continue
        paint["live"] = live
        print(f"{name}: live recipe {recipe.name}, {layers} layers")
    Path(output).write_text(json.dumps(manifest, indent=2), encoding="utf-8")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    main(*sys.argv[1:])
