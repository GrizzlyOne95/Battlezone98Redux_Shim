"""
Batch-export per-bone chunk payload meshes from Battlezone Redux `.mesh` files.

Typical usage from Blender:

    blender --background --python scripts/export_chunk_mesh_payloads.py -- \
        --mesh "C:\\Users\\istuart\\Documents\\Battlezone 98 Redux\\BZ_ASSETS\\common\\models\\avtank.mesh" \
        --output-dir "C:\\temp\\chunk_meshes"

This Shim-local copy is intended for chunk rendering experiments. It imports the
source mesh through the BZ98 Blender toolkit Ogre path, isolates geometry by
exact vertex-group membership via Blender's own selection/separate operators,
rebases each extracted piece to the matching bone pivot, strips armature
dependencies, and exports one standalone `.mesh` per chunk name.
"""

from __future__ import annotations

import argparse
import importlib
import os
import re
import sys
import traceback
from collections import defaultdict
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Sequence, Tuple

import bpy
from mathutils import Matrix, Vector


class ScriptOperator:
    """Minimal stand-in for Blender operators used by the toolkit backend."""

    def report(self, levels: Iterable[str], message: str) -> None:
        joined = ",".join(sorted(set(levels)))
        print(f"[{joined}] {message}")


def _default_toolkit_repo_root() -> Path:
    env_root = os.environ.get("BZR_BLENDER_TOOLKIT_ROOT")
    if env_root:
        return Path(env_root).expanduser().resolve()

    shim_repo_root = Path(__file__).resolve().parents[1]
    sibling_root = shim_repo_root.parent / "BZ98RBlenderToolKit"
    return sibling_root.resolve()


def _parse_args(argv: Sequence[str]) -> argparse.Namespace:
    if "--" in argv:
        argv = argv[list(argv).index("--") + 1 :]
    else:
        argv = []

    parser = argparse.ArgumentParser(description=__doc__)
    input_group = parser.add_mutually_exclusive_group(required=True)
    input_group.add_argument("--mesh", help="Input Ogre .mesh file")
    input_group.add_argument(
        "--mesh-root",
        help="Recursively process every .mesh under this directory",
    )
    parser.add_argument("--output-dir", required=True, help="Directory for exported chunk meshes")
    parser.add_argument(
        "--repo-root",
        default=str(_default_toolkit_repo_root()),
        help="Path to the BZ98RBlenderToolKit repo root",
    )
    parser.add_argument(
        "--xml-converter",
        default="",
        help="Optional OgreXMLConverter.exe path for fallback import/export",
    )
    parser.add_argument(
        "--keep-xml",
        action="store_true",
        help="Keep intermediate XML when the fallback Ogre XML path is used",
    )
    parser.add_argument(
        "--include-regex",
        default=".*",
        help="Only export chunk groups whose bone or vertex-group name matches this regex",
    )
    parser.add_argument(
        "--exclude-regex",
        default="^$",
        help="Skip chunk groups whose bone or vertex-group name matches this regex",
    )
    parser.add_argument(
        "--preserve-case",
        action="store_true",
        help="Preserve group name case in exported filenames",
    )
    parser.add_argument(
        "--export-materials",
        action="store_true",
        help="Also emit .material files next to each exported mesh",
    )
    parser.add_argument(
        "--skip-pivot-rebase",
        action="store_true",
        help="Leave extracted vertices in model space instead of shifting them to the bone pivot",
    )
    parser.add_argument(
        "--verbose",
        action="store_true",
        help="Print extra progress logs",
    )
    return parser.parse_args(argv)


def _bootstrap_toolkit(repo_root: Path):
    repo_root = repo_root.resolve()
    if not repo_root.exists():
        raise FileNotFoundError(f"Toolkit repo root does not exist: {repo_root}")

    repo_root_text = str(repo_root)
    if repo_root_text not in sys.path:
        sys.path.insert(0, repo_root_text)

    for module_name in list(sys.modules.keys()):
        if module_name == "bz98tools" or module_name.startswith("bz98tools."):
            del sys.modules[module_name]

    ogre_backend = importlib.import_module("bz98tools.ogrefast.backend")
    OgreImport = importlib.import_module("bz98tools.ogretools.OgreImport")
    OgreExport = importlib.import_module("bz98tools.ogretools.OgreExport")

    return ogre_backend, OgreImport, OgreExport


def _clear_scene() -> None:
    bpy.ops.object.select_all(action="SELECT")
    bpy.ops.object.delete(use_global=False)

    for collection in list(bpy.data.collections):
        if collection.users == 0:
            bpy.data.collections.remove(collection)

    for data_block in (
        bpy.data.meshes,
        bpy.data.armatures,
        bpy.data.materials,
        bpy.data.images,
        bpy.data.objects,
    ):
        for item in list(data_block):
            if item.users == 0:
                data_block.remove(item)


def _sanitize_filename(name: str, preserve_case: bool) -> str:
    safe = re.sub(r"[^A-Za-z0-9_.-]+", "_", name.strip())
    if not preserve_case:
        safe = safe.lower()
    return safe or "chunk"


def _find_imported_objects(before_names: set[str]) -> Tuple[List[bpy.types.Object], Optional[bpy.types.Object]]:
    imported_meshes: List[bpy.types.Object] = []
    imported_armature: Optional[bpy.types.Object] = None

    for obj in bpy.data.objects:
        if obj.name in before_names:
            continue
        if obj.type == "MESH":
            imported_meshes.append(obj)
        elif obj.type == "ARMATURE" and imported_armature is None:
            imported_armature = obj

    if not imported_meshes:
        imported_meshes = [obj for obj in bpy.data.objects if obj.type == "MESH"]
    if imported_armature is None:
        for mesh_obj in imported_meshes:
            armature = mesh_obj.find_armature()
            if armature is not None:
                imported_armature = armature
                break

    return imported_meshes, imported_armature


def _collect_input_meshes(mesh_path: Optional[Path], mesh_root: Optional[Path]) -> List[Path]:
    if mesh_path is not None:
        if not mesh_path.exists():
            raise FileNotFoundError(f"Input mesh does not exist: {mesh_path}")
        return [mesh_path]

    if mesh_root is None or not mesh_root.exists():
        raise FileNotFoundError(f"Input mesh root does not exist: {mesh_root}")

    mesh_paths = sorted(path for path in mesh_root.rglob("*.mesh") if path.is_file())
    if not mesh_paths:
        raise FileNotFoundError(f"No .mesh files found under {mesh_root}")
    return mesh_paths


def _get_allowed_group_names(
    obj: bpy.types.Object,
    armature: Optional[bpy.types.Object],
    include_pattern: re.Pattern[str],
    exclude_pattern: re.Pattern[str],
) -> List[str]:
    allowed_names: set[str] = set()
    if armature and armature.type == "ARMATURE":
        allowed_names.update(bone.name for bone in armature.data.bones)
    else:
        allowed_names.update(group.name for group in obj.vertex_groups)

    return sorted(
        name
        for name in allowed_names
        if include_pattern.search(name) and not exclude_pattern.search(name)
    )


def _strip_vertex_group_data(piece_obj: bpy.types.Object, source_obj: bpy.types.Object) -> None:
    vertex_count = len(piece_obj.data.vertices)
    if vertex_count == 0:
        return

    all_indices = list(range(vertex_count))
    for source_group in source_obj.vertex_groups:
        piece_group = piece_obj.vertex_groups.new(name=source_group.name)
        try:
            piece_group.remove(all_indices)
        except RuntimeError:
            pass

    while piece_obj.vertex_groups:
        piece_obj.vertex_groups.remove(piece_obj.vertex_groups[-1])


def _strip_armature_dependencies(piece_obj: bpy.types.Object) -> None:
    piece_obj.parent = None
    piece_obj.matrix_parent_inverse = Matrix.Identity(4)

    for modifier in list(piece_obj.modifiers):
        if modifier.type == "ARMATURE":
            piece_obj.modifiers.remove(modifier)


def _get_bone_pivot(
    source_obj: bpy.types.Object,
    armature: Optional[bpy.types.Object],
    bone_name: str,
) -> Vector:
    if armature is None or bone_name not in armature.data.bones:
        return Vector((0.0, 0.0, 0.0))

    bone = armature.data.bones[bone_name]
    pivot_world = armature.matrix_world @ bone.head_local
    return source_obj.matrix_world.inverted() @ pivot_world


def _rebase_piece_to_pivot(
    piece_obj: bpy.types.Object,
    pivot_local: Vector,
    rebase_to_pivot: bool,
) -> None:
    if not rebase_to_pivot or pivot_local.length_squared == 0.0:
        piece_obj.matrix_world = Matrix.Identity(4)
        return

    for vertex in piece_obj.data.vertices:
        vertex.co -= pivot_local
    piece_obj.data.update()
    piece_obj.matrix_world = Matrix.Identity(4)


def _duplicate_mesh_object(
    source_obj: bpy.types.Object,
    pieces_collection: bpy.types.Collection,
) -> bpy.types.Object:
    piece_mesh = source_obj.data.copy()
    piece_obj = source_obj.copy()
    piece_obj.data = piece_mesh
    piece_obj.animation_data_clear()
    piece_obj.matrix_world = source_obj.matrix_world.copy()
    pieces_collection.objects.link(piece_obj)
    return piece_obj


def _deselect_all() -> None:
    for obj in bpy.context.view_layer.objects:
        if obj is not None:
            obj.select_set(False)


def _extract_piece_object_by_group(
    source_obj: bpy.types.Object,
    group_name: str,
    pieces_collection: bpy.types.Collection,
    pivot_local: Vector,
    rebase_to_pivot: bool,
) -> Optional[bpy.types.Object]:
    if group_name not in source_obj.vertex_groups:
        return None

    temp_obj = _duplicate_mesh_object(source_obj, pieces_collection)
    view_layer = bpy.context.view_layer
    before_names = {obj.name for obj in bpy.data.objects}

    _deselect_all()
    temp_obj.select_set(True)
    view_layer.objects.active = temp_obj
    bpy.ops.object.mode_set(mode="EDIT")
    bpy.ops.mesh.select_mode(type="VERT")
    bpy.ops.mesh.select_all(action="DESELECT")
    temp_obj.vertex_groups.active_index = temp_obj.vertex_groups[group_name].index
    bpy.ops.object.vertex_group_select()

    selected_vert_count = sum(1 for vertex in temp_obj.data.vertices if vertex.select)
    if selected_vert_count == 0:
        bpy.ops.object.mode_set(mode="OBJECT")
        bpy.data.objects.remove(temp_obj, do_unlink=True)
        return None

    bpy.ops.mesh.separate(type="SELECTED")
    bpy.ops.object.mode_set(mode="OBJECT")

    created_objects = [obj for obj in bpy.data.objects if obj.name not in before_names]
    piece_obj = next((obj for obj in created_objects if obj.type == "MESH"), None)
    if piece_obj is None:
        bpy.data.objects.remove(temp_obj, do_unlink=True)
        return None

    bpy.data.objects.remove(temp_obj, do_unlink=True)
    piece_obj.name = f"{source_obj.name}__{group_name}"
    piece_obj.data.name = piece_obj.name
    _strip_vertex_group_data(piece_obj, source_obj)
    _strip_armature_dependencies(piece_obj)
    _rebase_piece_to_pivot(piece_obj, pivot_local, rebase_to_pivot)
    return piece_obj


def _split_objects_into_chunk_payloads(
    mesh_objects: Sequence[bpy.types.Object],
    armature: Optional[bpy.types.Object],
    include_pattern: re.Pattern[str],
    exclude_pattern: re.Pattern[str],
    rebase_to_pivot: bool,
    verbose: bool,
) -> Dict[str, List[bpy.types.Object]]:
    export_map: Dict[str, List[bpy.types.Object]] = defaultdict(list)

    pieces_collection = bpy.data.collections.new("ChunkPayloadPieces")
    bpy.context.scene.collection.children.link(pieces_collection)

    for mesh_obj in mesh_objects:
        if mesh_obj.type != "MESH":
            continue

        allowed_group_names = _get_allowed_group_names(
            mesh_obj,
            armature,
            include_pattern,
            exclude_pattern,
        )
        if not allowed_group_names:
            continue

        for group_name in allowed_group_names:
            pivot_local = _get_bone_pivot(mesh_obj, armature, group_name)
            piece_obj = _extract_piece_object_by_group(
                source_obj=mesh_obj,
                group_name=group_name,
                pieces_collection=pieces_collection,
                pivot_local=pivot_local,
                rebase_to_pivot=rebase_to_pivot,
            )
            if piece_obj is None:
                continue
            export_map[group_name].append(piece_obj)
            if verbose:
                print(
                    f"Created piece {piece_obj.name} from {mesh_obj.name} "
                    f"pivot={tuple(round(v, 6) for v in pivot_local)}"
                )

    return export_map


def _export_group_meshes(
    ogre_backend,
    OgreExport,
    output_dir: Path,
    export_map: Dict[str, List[bpy.types.Object]],
    xml_converter: Optional[str],
    keep_xml: bool,
    preserve_case: bool,
    export_materials: bool,
    verbose: bool,
) -> List[Path]:
    output_dir.mkdir(parents=True, exist_ok=True)
    operator = ScriptOperator()
    exported_paths: List[Path] = []

    for group_name, piece_objects in sorted(export_map.items()):
        if not piece_objects:
            continue

        _deselect_all()
        for piece_obj in piece_objects:
            piece_obj.select_set(True)
        bpy.context.view_layer.objects.active = piece_objects[0]

        output_name = _sanitize_filename(group_name, preserve_case=preserve_case)
        output_path = output_dir / f"{output_name}.mesh"
        result = ogre_backend.export_mesh(
            operator,
            bpy.context,
            str(output_path),
            legacy_handler=OgreExport.save,
            xml_converter=xml_converter,
            keep_xml=keep_xml,
            export_tangents=True,
            export_binormals=True,
            zero_tangents_binormals=False,
            export_colour=True,
            tangent_parity=True,
            apply_transform=False,
            apply_modifiers=False,
            export_materials=export_materials,
            overwrite_material=False,
            copy_textures=False,
            export_skeleton=False,
            export_poses=False,
            export_animation=False,
            renormalize_weights=False,
            batch_export=False,
        )
        if result != {"FINISHED"}:
            raise RuntimeError(f"Failed exporting {group_name}: {result}")

        exported_paths.append(output_path)
        if verbose:
            print(f"Exported {group_name} -> {output_path}")

    return exported_paths


def _process_single_mesh(
    ogre_backend,
    OgreImport,
    OgreExport,
    mesh_path: Path,
    output_dir: Path,
    include_pattern: re.Pattern[str],
    exclude_pattern: re.Pattern[str],
    xml_converter: Optional[str],
    keep_xml: bool,
    preserve_case: bool,
    export_materials: bool,
    rebase_to_pivot: bool,
    verbose: bool,
) -> List[Path]:
    _clear_scene()
    operator = ScriptOperator()

    before_names = {obj.name for obj in bpy.data.objects}
    import_result = ogre_backend.import_mesh(
        operator,
        bpy.context,
        str(mesh_path),
        legacy_handler=OgreImport.load,
        xml_converter=xml_converter,
        keep_xml=keep_xml,
        import_normals=True,
        normal_mode="custom",
        import_shapekeys=False,
        import_animations=False,
        round_frames=True,
        use_selected_skeleton=False,
        import_materials=True,
    )
    if import_result != {"FINISHED"}:
        raise RuntimeError(f"Import failed: {import_result}")

    mesh_objects, armature = _find_imported_objects(before_names)
    if not mesh_objects:
        raise RuntimeError(f"No mesh objects were imported from {mesh_path}")

    export_map = _split_objects_into_chunk_payloads(
        mesh_objects=mesh_objects,
        armature=armature,
        include_pattern=include_pattern,
        exclude_pattern=exclude_pattern,
        rebase_to_pivot=rebase_to_pivot,
        verbose=verbose,
    )
    if not export_map:
        raise RuntimeError("No chunk payloads were generated from the imported mesh")

    return _export_group_meshes(
        ogre_backend=ogre_backend,
        OgreExport=OgreExport,
        output_dir=output_dir,
        export_map=export_map,
        xml_converter=xml_converter,
        keep_xml=keep_xml,
        preserve_case=preserve_case,
        export_materials=export_materials,
        verbose=verbose,
    )


def main(argv: Sequence[str]) -> int:
    args = _parse_args(argv)

    output_dir = Path(args.output_dir).expanduser().resolve()
    repo_root = Path(args.repo_root).expanduser().resolve()
    mesh_path = Path(args.mesh).expanduser().resolve() if args.mesh else None
    mesh_root = Path(args.mesh_root).expanduser().resolve() if args.mesh_root else None

    include_pattern = re.compile(args.include_regex, re.IGNORECASE)
    exclude_pattern = re.compile(args.exclude_regex, re.IGNORECASE)
    xml_converter = args.xml_converter or None
    input_meshes = _collect_input_meshes(mesh_path, mesh_root)

    ogre_backend, OgreImport, OgreExport = _bootstrap_toolkit(repo_root)

    all_exported_paths: List[Path] = []
    multi_input = len(input_meshes) > 1
    for current_mesh_path in input_meshes:
        current_output_dir = output_dir / current_mesh_path.stem if multi_input else output_dir
        print(f"Processing {current_mesh_path}")
        exported_paths = _process_single_mesh(
            ogre_backend=ogre_backend,
            OgreImport=OgreImport,
            OgreExport=OgreExport,
            mesh_path=current_mesh_path,
            output_dir=current_output_dir,
            include_pattern=include_pattern,
            exclude_pattern=exclude_pattern,
            xml_converter=xml_converter,
            keep_xml=args.keep_xml,
            preserve_case=args.preserve_case,
            export_materials=args.export_materials,
            rebase_to_pivot=not args.skip_pivot_rebase,
            verbose=args.verbose,
        )
        all_exported_paths.extend(exported_paths)

    print(f"Exported {len(all_exported_paths)} chunk payload mesh(es) to {output_dir}")
    for path in all_exported_paths:
        print(f"  {path}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main(sys.argv))
    except SystemExit:
        raise
    except Exception:
        print(traceback.format_exc())
        raise SystemExit(1)
