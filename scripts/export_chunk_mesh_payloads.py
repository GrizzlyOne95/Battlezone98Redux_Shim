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
import bmesh
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
        "--skip-tangents",
        action="store_true",
        help="Do not export tangents/binormals for payload meshes",
    )
    parser.add_argument(
        "--skip-pivot-rebase",
        action="store_true",
        help="Leave extracted vertices in model space instead of shifting them to the bone pivot",
    )
    parser.add_argument(
        "--skip-import-normals",
        action="store_true",
        help="Disable custom-normal import for meshes that crash Blender on import",
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
    for obj in bpy.data.objects:
        if obj is not None:
            obj.select_set(False)


def _get_vertex_indices_for_group(
    source_obj: bpy.types.Object,
    group_name: str,
) -> set[int]:
    if group_name not in source_obj.vertex_groups:
        return set()

    group_index = source_obj.vertex_groups[group_name].index
    return {
        vertex.index
        for vertex in source_obj.data.vertices
        if any(group.group == group_index for group in vertex.groups)
    }


def _filter_piece_object_to_vertex_indices(
    piece_obj: bpy.types.Object,
    keep_vertex_indices: set[int],
) -> bool:
    if not keep_vertex_indices:
        return False

    bm = bmesh.new()
    try:
        bm.from_mesh(piece_obj.data)
        bm.verts.ensure_lookup_table()
        delete_verts = [vert for vert in bm.verts if vert.index not in keep_vertex_indices]
        if delete_verts:
            bmesh.ops.delete(bm, geom=delete_verts, context="VERTS")
        bm.to_mesh(piece_obj.data)
    finally:
        bm.free()

    piece_obj.data.validate(verbose=False)
    piece_obj.data.update(calc_edges=True, calc_edges_loose=True)
    return len(piece_obj.data.vertices) > 0 and len(piece_obj.data.polygons) > 0


def _extract_piece_object(
    source_obj: bpy.types.Object,
    piece_name: str,
    keep_vertex_indices: set[int],
    pieces_collection: bpy.types.Collection,
    pivot_local: Vector,
    rebase_to_pivot: bool,
) -> Optional[bpy.types.Object]:
    if not keep_vertex_indices:
        return None

    temp_obj = _duplicate_mesh_object(source_obj, pieces_collection)
    if not _filter_piece_object_to_vertex_indices(temp_obj, keep_vertex_indices):
        bpy.data.objects.remove(temp_obj, do_unlink=True)
        return None

    temp_obj.name = f"{source_obj.name}__{piece_name}"
    temp_obj.data.name = temp_obj.name
    _strip_vertex_group_data(temp_obj, source_obj)
    _strip_armature_dependencies(temp_obj)
    _rebase_piece_to_pivot(temp_obj, pivot_local, rebase_to_pivot)
    _reset_piece_custom_normals(temp_obj)
    return temp_obj


def _reset_piece_custom_normals(piece_obj: bpy.types.Object) -> None:
    if len(piece_obj.data.vertices) == 0:
        return

    # Zero vectors tell Blender to rebuild normals from the current topology.
    piece_obj.data.normals_split_custom_set_from_vertices(
        [(0.0, 0.0, 0.0)] * len(piece_obj.data.vertices)
    )
    piece_obj.data.update()


def _extract_piece_object_by_group(
    source_obj: bpy.types.Object,
    group_name: str,
    pieces_collection: bpy.types.Collection,
    pivot_local: Vector,
    rebase_to_pivot: bool,
) -> Optional[bpy.types.Object]:
    return _extract_piece_object(
        source_obj=source_obj,
        piece_name=group_name,
        keep_vertex_indices=_get_vertex_indices_for_group(source_obj, group_name),
        pieces_collection=pieces_collection,
        pivot_local=pivot_local,
        rebase_to_pivot=rebase_to_pivot,
    )


def _find_connected_face_islands(mesh_obj: bpy.types.Object) -> List[set[int]]:
    bm = bmesh.new()
    try:
        bm.from_mesh(mesh_obj.data)
        bm.faces.ensure_lookup_table()
        remaining_faces = set(bm.faces)
        islands: List[set[int]] = []
        while remaining_faces:
            seed_face = remaining_faces.pop()
            stack = [seed_face]
            island_faces = {seed_face}
            while stack:
                current_face = stack.pop()
                for edge in current_face.edges:
                    for linked_face in edge.link_faces:
                        if linked_face in remaining_faces:
                            remaining_faces.remove(linked_face)
                            island_faces.add(linked_face)
                            stack.append(linked_face)

            islands.append({vert.index for face in island_faces for vert in face.verts})
        return islands
    finally:
        bm.free()


def _split_objects_into_connected_face_islands(
    mesh_objects: Sequence[bpy.types.Object],
    pieces_collection: bpy.types.Collection,
    mesh_basename: str,
    rebase_to_pivot: bool,
    verbose: bool,
) -> Dict[str, List[bpy.types.Object]]:
    export_map: Dict[str, List[bpy.types.Object]] = defaultdict(list)

    for mesh_obj in mesh_objects:
        if mesh_obj.type != "MESH" or len(mesh_obj.data.polygons) == 0:
            continue

        islands = _find_connected_face_islands(mesh_obj)
        island_count = len(islands)
        for index, keep_vertex_indices in enumerate(islands, start=1):
            if island_count == 1:
                piece_name = mesh_basename
            else:
                piece_name = f"{mesh_basename}_part{index:02d}"

            piece_obj = _extract_piece_object(
                source_obj=mesh_obj,
                piece_name=piece_name,
                keep_vertex_indices=keep_vertex_indices,
                pieces_collection=pieces_collection,
                pivot_local=Vector((0.0, 0.0, 0.0)),
                rebase_to_pivot=rebase_to_pivot,
            )
            if piece_obj is None:
                continue
            export_map[piece_name].append(piece_obj)
            if verbose:
                print(
                    f"Created fallback piece {piece_obj.name} from {mesh_obj.name} "
                    f"island={index}/{island_count}"
                )

    return export_map


def _split_objects_into_chunk_payloads(
    mesh_objects: Sequence[bpy.types.Object],
    armature: Optional[bpy.types.Object],
    mesh_basename: str,
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

    if export_map:
        return export_map

    return _split_objects_into_connected_face_islands(
        mesh_objects=mesh_objects,
        pieces_collection=pieces_collection,
        mesh_basename=mesh_basename,
        rebase_to_pivot=rebase_to_pivot,
        verbose=verbose,
    )


def _export_group_meshes(
    ogre_backend,
    OgreExport,
    output_dir: Path,
    export_map: Dict[str, List[bpy.types.Object]],
    xml_converter: Optional[str],
    keep_xml: bool,
    preserve_case: bool,
    export_materials: bool,
    export_tangents: bool,
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
            export_tangents=export_tangents,
            export_binormals=export_tangents,
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
            print(f"[WARNING] Failed exporting {group_name}: {result}")
            continue

        if not output_path.exists() or output_path.stat().st_size == 0:
            if output_path.exists():
                output_path.unlink()
            print(f"[WARNING] Export produced no usable mesh for {group_name}")
            continue

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
    export_tangents: bool,
    import_normals: bool,
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
        import_normals=import_normals,
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
        mesh_basename=mesh_path.stem,
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
        export_tangents=export_tangents,
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
            export_tangents=not args.skip_tangents,
            import_normals=not args.skip_import_normals,
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
