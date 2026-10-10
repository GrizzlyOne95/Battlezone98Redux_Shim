"""
Split a skinned Battlezone Redux `.mesh` into rigid gib payload meshes for the
OpenShim SkinnedGibs path.

Pure Python plus OgreXMLConverter; no Blender. Usage:

    python scripts/export_gib_payloads.py --mesh "<addon>/ispilo.mesh" \
        --output-dir "<chunk root>/ispilo"

How the split works:
  * Every triangle is owned by the bone with the highest summed weight over its
    three vertices (blended skin is split along the dominant bone, which leaves
    a jagged but believable tear line).
  * Bones that own fewer than --min-face-fraction of the mesh (fingers, hands,
    clavicles, feet, nubs) are rolled up into their parent until each gib is a
    meaty limb segment. --keep-regex forces a bone to stay its own gib.
  * Submeshes matching --detach-submesh-regex (guns, lasers) become one extra
    piece driven by their dominant bone, so the weapon drops on its own.
  * Each cut (an edge shared with another gib in the welded source topology)
    is closed with a fan cap in a separate submesh using --cap-material, so a
    gib never shows the inside of its shell.
  * Vertices are rebased to the piece's bounding-box centre so it spins about
    its own middle.

Outputs into --output-dir:
    gib_<bone>.mesh       one rigid mesh per piece (no skeleton, no weights)
    gibs.txt              manifest the shim reads:
                          piece <name> bone <bone> pivot <x> <y> <z> radius <r> tris <n>

At runtime the shim places a piece at
    entityWorld * bone.offsetTransform * translate(pivot)
which is the bone's current skinning transform applied to the bind-space piece,
so the gib leaves exactly where that body part was on the frame of death.
"""

from __future__ import annotations

import argparse
import math
import re
import shutil
import subprocess
import sys
import tempfile
import xml.etree.ElementTree as ET
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Set, Tuple

DEFAULT_CONVERTER = (
    Path(__file__).resolve().parents[2]
    / "BZ98RBlenderToolKit" / "bz98tools" / "ogretools" / "OgreXMLConverter.exe"
)
WELD_EPSILON = 1e-4


# --------------------------------------------------------------------------- io

def _run_converter(converter: Path, src: Path, dst: Path) -> None:
    result = subprocess.run(
        [str(converter), "-q", str(src), str(dst)],
        cwd=str(src.parent),
        capture_output=True,
        text=True,
    )
    # The converter's exit code is unreliable (a missing skeletonlink target is
    # reported as an error even though the XML is written), so judge by output.
    if not dst.exists() or dst.stat().st_size == 0:
        raise RuntimeError(
            f"OgreXMLConverter failed for {src}:\n{result.stdout}\n{result.stderr}"
        )


def _find_skeleton(mesh_path: Path, mesh_root: ET.Element, explicit: Optional[str]) -> Path:
    if explicit:
        return Path(explicit)
    candidates: List[Path] = []
    link = mesh_root.find("skeletonlink")
    if link is not None and link.get("name"):
        candidates.append(mesh_path.with_name(link.get("name")))
    candidates.append(mesh_path.with_suffix(".skeleton"))
    for candidate in candidates:
        if candidate.exists():
            return candidate
    raise FileNotFoundError(
        f"No skeleton found for {mesh_path}; tried {[str(c) for c in candidates]}"
    )


# --------------------------------------------------------------------- math

def _quat_from_axis_angle(angle: float, axis: Tuple[float, float, float]):
    length = math.sqrt(sum(a * a for a in axis)) or 1.0
    ax, ay, az = (a / length for a in axis)
    s = math.sin(angle * 0.5)
    return (math.cos(angle * 0.5), ax * s, ay * s, az * s)


def _quat_mul(a, b):
    aw, ax, ay, az = a
    bw, bx, by, bz = b
    return (
        aw * bw - ax * bx - ay * by - az * bz,
        aw * bx + ax * bw + ay * bz - az * by,
        aw * by - ax * bz + ay * bw + az * bx,
        aw * bz + ax * by - ay * bx + az * bw,
    )


def _quat_rotate(q, v):
    w, x, y, z = q
    vq = (0.0, v[0], v[1], v[2])
    conj = (w, -x, -y, -z)
    r = _quat_mul(_quat_mul(q, vq), conj)
    return (r[1], r[2], r[3])


def _sub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def _add(a, b):
    return (a[0] + b[0], a[1] + b[1], a[2] + b[2])


def _scale(a, s):
    return (a[0] * s, a[1] * s, a[2] * s)


def _cross(a, b):
    return (
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0],
    )


def _dot(a, b):
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]


def _normalize(a):
    length = math.sqrt(_dot(a, a))
    if length < 1e-12:
        return (0.0, 1.0, 0.0)
    return _scale(a, 1.0 / length)


# ------------------------------------------------------------------ skeleton

class Skeleton:
    def __init__(self, root: ET.Element):
        self.names: Dict[int, str] = {}
        self.ids: Dict[str, int] = {}
        local: Dict[str, Tuple[tuple, tuple]] = {}
        for bone in root.find("bones"):
            bone_id = int(bone.get("id"))
            name = bone.get("name")
            self.names[bone_id] = name
            self.ids[name] = bone_id
            pos_el = bone.find("position")
            pos = (
                float(pos_el.get("x")), float(pos_el.get("y")), float(pos_el.get("z"))
            ) if pos_el is not None else (0.0, 0.0, 0.0)
            rot_el = bone.find("rotation")
            if rot_el is not None:
                axis_el = rot_el.find("axis")
                quat = _quat_from_axis_angle(
                    float(rot_el.get("angle")),
                    (float(axis_el.get("x")), float(axis_el.get("y")), float(axis_el.get("z"))),
                )
            else:
                quat = (1.0, 0.0, 0.0, 0.0)
            local[name] = (pos, quat)

        self.parent: Dict[str, Optional[str]] = {name: None for name in self.ids}
        hierarchy = root.find("bonehierarchy")
        if hierarchy is not None:
            for link in hierarchy:
                self.parent[link.get("bone")] = link.get("parent")

        self.derived_pos: Dict[str, tuple] = {}
        self.derived_rot: Dict[str, tuple] = {}

        def resolve(name: str):
            if name in self.derived_pos:
                return
            pos, quat = local[name]
            parent = self.parent.get(name)
            if parent is None:
                self.derived_pos[name] = pos
                self.derived_rot[name] = quat
                return
            resolve(parent)
            parent_rot = self.derived_rot[parent]
            self.derived_pos[name] = _add(self.derived_pos[parent], _quat_rotate(parent_rot, pos))
            self.derived_rot[name] = _quat_mul(parent_rot, quat)

        for name in self.ids:
            resolve(name)

    def depth(self, name: str) -> int:
        depth = 0
        while self.parent.get(name):
            name = self.parent[name]
            depth += 1
        return depth


# ---------------------------------------------------------------------- mesh

class SubMesh:
    def __init__(self, index: int, element: ET.Element, shared_geometry: Optional[ET.Element],
                 shared_assignments: Optional[ET.Element]):
        self.index = index
        self.element = element
        self.material = element.get("material", "")
        if element.get("usesharedvertices") == "true":
            geometry = shared_geometry
            assignments = shared_assignments
        else:
            geometry = element.find("geometry")
            assignments = element.find("boneassignments")
        if geometry is None:
            raise RuntimeError(f"submesh {index} has no geometry")
        self.vertex_count = int(geometry.get("vertexcount"))
        # Each vertexbuffer keeps its attribute flags and its <vertex> elements so
        # pieces can be written back with every original element intact.
        self.buffers: List[Tuple[Dict[str, str], List[ET.Element]]] = []
        for buffer in geometry.findall("vertexbuffer"):
            self.buffers.append((dict(buffer.attrib), list(buffer.findall("vertex"))))
        self.positions: List[tuple] = []
        self.normals: List[Optional[tuple]] = []
        for attrs, vertices in self.buffers:
            if attrs.get("positions") == "true":
                for vertex in vertices:
                    p = vertex.find("position")
                    self.positions.append((float(p.get("x")), float(p.get("y")), float(p.get("z"))))
                    n = vertex.find("normal")
                    self.normals.append(
                        (float(n.get("x")), float(n.get("y")), float(n.get("z"))) if n is not None else None
                    )
        if len(self.positions) != self.vertex_count:
            raise RuntimeError(f"submesh {index}: position count mismatch")
        self.faces: List[Tuple[int, int, int]] = [
            (int(f.get("v1")), int(f.get("v2")), int(f.get("v3")))
            for f in element.find("faces").findall("face")
        ]
        self.weights: List[Dict[int, float]] = [defaultdict(float) for _ in range(self.vertex_count)]
        if assignments is not None:
            for vba in assignments.findall("vertexboneassignment"):
                self.weights[int(vba.get("vertexindex"))][int(vba.get("boneindex"))] += float(vba.get("weight"))


def _load_mesh(root: ET.Element) -> List[SubMesh]:
    shared_geometry = root.find("sharedgeometry")
    shared_assignments = root.find("boneassignments")
    submeshes_el = root.find("submeshes")
    return [
        SubMesh(i, el, shared_geometry, shared_assignments)
        for i, el in enumerate(submeshes_el.findall("submesh"))
    ]


# --------------------------------------------------------------- partitioning

def _face_dominant_bone(sub: SubMesh, face: Tuple[int, int, int]) -> Optional[int]:
    totals: Dict[int, float] = defaultdict(float)
    for vi in face:
        for bone, weight in sub.weights[vi].items():
            totals[bone] += weight
    if not totals:
        return None
    return max(totals.items(), key=lambda kv: (kv[1], -kv[0]))[0]


def _roll_up(owner_counts: Dict[str, int], skeleton: Skeleton, min_faces: int,
             keep: re.Pattern, drop: re.Pattern) -> Dict[str, str]:
    """Map every owning bone to the gib bone it ends up in."""
    target = {name: name for name in skeleton.ids}
    counts = defaultdict(int, owner_counts)

    def must_merge(name: str) -> bool:
        if skeleton.parent.get(name) is None:
            return False
        if keep.search(name):
            return False
        return drop.search(name) is not None or counts[name] < min_faces

    # Deepest bones first, so fingers fold into the hand before the hand is
    # judged, and the hand (now heavier) folds into the forearm only if it is
    # still too small.
    for name in sorted(skeleton.ids, key=lambda n: -skeleton.depth(n)):
        if counts[name] == 0 or not must_merge(name):
            continue
        parent = skeleton.parent[name]
        counts[parent] += counts[name]
        counts[name] = 0
        for bone, mapped in target.items():
            if mapped == name:
                target[bone] = parent
    return target


# ------------------------------------------------------------------ capping

def _weld_key(p: tuple) -> Tuple[int, int, int]:
    return (round(p[0] / WELD_EPSILON), round(p[1] / WELD_EPSILON), round(p[2] / WELD_EPSILON))


def _boundary_loops(edges: List[Tuple[int, int]]) -> List[List[int]]:
    """Chain directed boundary edges (welded ids) into loops; tolerant of junk."""
    outgoing: Dict[int, List[int]] = defaultdict(list)
    for a, b in edges:
        outgoing[a].append(b)
    used: Set[Tuple[int, int]] = set()
    loops: List[List[int]] = []
    for a, b in edges:
        if (a, b) in used:
            continue
        loop = [a]
        used.add((a, b))
        current = b
        guard = 0
        while current != a and guard < len(edges) + 1:
            loop.append(current)
            nxt = None
            for candidate in outgoing.get(current, []):
                if (current, candidate) not in used:
                    nxt = candidate
                    break
            if nxt is None:
                break
            used.add((current, nxt))
            current = nxt
            guard += 1
        if len(loop) >= 3:
            loops.append(loop)
    return loops


# ----------------------------------------------------------------- writing

def _fmt(v: float) -> str:
    return f"{v:.6f}".rstrip("0").rstrip(".") if v != 0 else "0"


def _write_piece_xml(path: Path, piece_subs: List[Tuple[SubMesh, List[Tuple[int, int, int]]]],
                     pivot: tuple, cap_tris: List[Tuple[tuple, tuple, tuple, tuple]],
                     cap_material: str, uv_scale: float) -> int:
    mesh = ET.Element("mesh")
    submeshes = ET.SubElement(mesh, "submeshes")
    tri_total = 0

    for sub, faces in piece_subs:
        used = sorted({vi for face in faces for vi in face})
        remap = {old: new for new, old in enumerate(used)}
        sm = ET.SubElement(submeshes, "submesh", {
            "material": sub.material,
            "usesharedvertices": "false",
            "use32bitindexes": "true" if len(used) > 65535 else "false",
            "operationtype": "triangle_list",
        })
        faces_el = ET.SubElement(sm, "faces", {"count": str(len(faces))})
        for a, b, c in faces:
            ET.SubElement(faces_el, "face", {"v1": str(remap[a]), "v2": str(remap[b]), "v3": str(remap[c])})
        geometry = ET.SubElement(sm, "geometry", {"vertexcount": str(len(used))})
        for attrs, vertices in sub.buffers:
            buffer = ET.SubElement(geometry, "vertexbuffer", attrs)
            for old in used:
                vertex = _clone(vertices[old])
                if attrs.get("positions") == "true":
                    p = vertex.find("position")
                    for axis, offset in zip("xyz", pivot):
                        p.set(axis, _fmt(float(p.get(axis)) - offset))
                buffer.append(vertex)
        tri_total += len(faces)

    if cap_tris:
        sm = ET.SubElement(submeshes, "submesh", {
            "material": cap_material,
            "usesharedvertices": "false",
            "use32bitindexes": "false",
            "operationtype": "triangle_list",
        })
        faces_el = ET.SubElement(sm, "faces", {"count": str(len(cap_tris))})
        geometry = ET.SubElement(sm, "geometry", {"vertexcount": str(len(cap_tris) * 3)})
        buffer = ET.SubElement(geometry, "vertexbuffer", {
            "positions": "true", "normals": "true",
            "texture_coord_dimensions_0": "float2", "texture_coords": "1",
        })
        for tri_index, (p0, p1, p2, normal) in enumerate(cap_tris):
            base = tri_index * 3
            ET.SubElement(faces_el, "face", {"v1": str(base), "v2": str(base + 1), "v3": str(base + 2)})
            # Planar UVs in the cap's own plane, so the flesh texture tiles evenly.
            tangent = _normalize(_cross(normal, (0.0, 1.0, 0.0) if abs(normal[1]) < 0.9 else (1.0, 0.0, 0.0)))
            bitangent = _cross(normal, tangent)
            for p in (p0, p1, p2):
                vertex = ET.SubElement(buffer, "vertex")
                local = _sub(p, pivot)
                ET.SubElement(vertex, "position", {"x": _fmt(local[0]), "y": _fmt(local[1]), "z": _fmt(local[2])})
                ET.SubElement(vertex, "normal", {"x": _fmt(normal[0]), "y": _fmt(normal[1]), "z": _fmt(normal[2])})
                ET.SubElement(vertex, "texcoord", {
                    "u": _fmt(_dot(p, tangent) * uv_scale), "v": _fmt(_dot(p, bitangent) * uv_scale),
                })
        tri_total += len(cap_tris)

    ET.ElementTree(mesh).write(path, encoding="utf-8", xml_declaration=False)
    return tri_total


def _clone(element: ET.Element) -> ET.Element:
    return ET.fromstring(ET.tostring(element))


# --------------------------------------------------------------------- main

def _parse_args(argv: Sequence[str]) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--mesh", required=True, help="Skinned input .mesh")
    parser.add_argument("--skeleton", default="", help="Override the .skeleton (default: skeletonlink, then <mesh>.skeleton)")
    parser.add_argument("--output-dir", required=True)
    parser.add_argument("--converter", default=str(DEFAULT_CONVERTER), help="OgreXMLConverter.exe")
    parser.add_argument("--min-face-fraction", type=float, default=0.025,
                        help="Bones owning fewer than this share of all faces roll up into their parent")
    parser.add_argument("--keep-regex", default="(?i)head$",
                        help="Bones that always stay their own gib")
    parser.add_argument("--drop-regex", default="(?i)(nub|footsteps|finger|toe|clavicle)",
                        help="Bones that always roll up into their parent")
    parser.add_argument("--detach-submesh-regex", default="(?i)(gun|laser|weapon|rifle)",
                        help="Submesh materials that become one separate weapon piece")
    parser.add_argument("--cap-material", default="openshim_gib_flesh")
    parser.add_argument("--cap-uv-scale", type=float, default=4.0)
    parser.add_argument("--no-caps", action="store_true")
    parser.add_argument("--keep-xml", action="store_true")
    return parser.parse_args(argv)


def main(argv: Sequence[str]) -> int:
    args = _parse_args(argv)
    mesh_path = Path(args.mesh).resolve()
    out_dir = Path(args.output_dir).resolve()
    converter = Path(args.converter)
    if not converter.exists():
        raise FileNotFoundError(f"OgreXMLConverter not found: {converter}")
    out_dir.mkdir(parents=True, exist_ok=True)

    with tempfile.TemporaryDirectory(prefix="openshim_gib_") as tmp_text:
        tmp = Path(tmp_text)
        staged_mesh = tmp / mesh_path.name
        shutil.copy2(mesh_path, staged_mesh)
        mesh_xml = tmp / (mesh_path.name + ".xml")
        _run_converter(converter, staged_mesh, mesh_xml)
        mesh_root = ET.parse(mesh_xml).getroot()

        skeleton_path = _find_skeleton(mesh_path, mesh_root, args.skeleton or None)
        staged_skeleton = tmp / skeleton_path.name
        shutil.copy2(skeleton_path, staged_skeleton)
        skeleton_xml = tmp / (skeleton_path.name + ".xml")
        _run_converter(converter, staged_skeleton, skeleton_xml)
        skeleton = Skeleton(ET.parse(skeleton_xml).getroot())

        submeshes = _load_mesh(mesh_root)
        detach = re.compile(args.detach_submesh_regex)
        keep = re.compile(args.keep_regex)
        drop = re.compile(args.drop_regex)

        # 1. Dominant bone per face.
        face_owner: Dict[Tuple[int, int], str] = {}
        owner_counts: Dict[str, int] = defaultdict(int)
        weapon_counts: Dict[str, int] = defaultdict(int)
        total_faces = 0
        for sub in submeshes:
            for fi, face in enumerate(sub.faces):
                bone = _face_dominant_bone(sub, face)
                name = skeleton.names.get(bone) if bone is not None else None
                if name is None:
                    continue
                face_owner[(sub.index, fi)] = name
                total_faces += 1
                if detach.search(sub.material):
                    weapon_counts[name] += 1
                else:
                    owner_counts[name] += 1

        # 2. Roll small bones up into limb-sized gibs.
        min_faces = max(1, int(total_faces * args.min_face_fraction))
        target = _roll_up(owner_counts, skeleton, min_faces, keep, drop)
        weapon_bone = max(weapon_counts.items(), key=lambda kv: kv[1])[0] if weapon_counts else None

        pieces: Dict[str, Dict[int, List[Tuple[int, int, int]]]] = defaultdict(lambda: defaultdict(list))
        piece_bone: Dict[str, str] = {}
        face_piece: Dict[Tuple[int, int], str] = {}
        for sub in submeshes:
            is_weapon = detach.search(sub.material) is not None
            for fi, face in enumerate(sub.faces):
                owner = face_owner.get((sub.index, fi))
                if owner is None:
                    continue
                if is_weapon:
                    piece, bone = "weapon", weapon_bone
                else:
                    bone = target[owner]
                    piece = bone
                pieces[piece][sub.index].append(face)
                piece_bone[piece] = bone
                face_piece[(sub.index, fi)] = piece

        # 3. Welded topology to find cut edges between body gibs.
        weld_ids: Dict[Tuple[int, int], int] = {}
        weld_pos: Dict[int, tuple] = {}
        weld_lookup: Dict[Tuple[int, int, int], int] = {}
        for sub in submeshes:
            for vi, p in enumerate(sub.positions):
                key = _weld_key(p)
                wid = weld_lookup.setdefault(key, len(weld_lookup))
                weld_ids[(sub.index, vi)] = wid
                weld_pos.setdefault(wid, p)

        edge_pieces: Dict[Tuple[int, int], Set[str]] = defaultdict(set)
        for (si, fi), piece in face_piece.items():
            if piece == "weapon":
                continue
            a, b, c = (weld_ids[(si, v)] for v in submeshes[si].faces[fi])
            for u, v in ((a, b), (b, c), (c, a)):
                edge_pieces[(min(u, v), max(u, v))].add(piece)

        manifest_lines: List[str] = [
            "# OpenShim gib manifest: generated by scripts/export_gib_payloads.py",
            f"# source {mesh_path.name} skeleton {skeleton_path.name}",
        ]
        summary: List[str] = []
        for piece in sorted(pieces):
            by_sub = pieces[piece]
            positions = [submeshes[si].positions[v] for si, faces in by_sub.items() for f in faces for v in f]
            lo = tuple(min(p[i] for p in positions) for i in range(3))
            hi = tuple(max(p[i] for p in positions) for i in range(3))
            pivot = _scale(_add(lo, hi), 0.5)
            radius = max(math.sqrt(_dot(_sub(p, pivot), _sub(p, pivot))) for p in positions)
            centroid = _scale(
                tuple(sum(p[i] for p in positions) for i in range(3)), 1.0 / len(positions)
            )

            cap_tris: List[Tuple[tuple, tuple, tuple, tuple]] = []
            if not args.no_caps and piece != "weapon":
                cut_edges: List[Tuple[int, int]] = []
                for si, faces in by_sub.items():
                    for face in faces:
                        a, b, c = (weld_ids[(si, v)] for v in face)
                        for u, v in ((a, b), (b, c), (c, a)):
                            owners = edge_pieces[(min(u, v), max(u, v))]
                            if len(owners) > 1:
                                # Reverse the face edge so the cap winds opposite
                                # to the skin it closes.
                                cut_edges.append((v, u))
                for loop in _boundary_loops(list(dict.fromkeys(cut_edges))):
                    points = [weld_pos[w] for w in loop]
                    center = _scale(tuple(sum(p[i] for p in points) for i in range(3)), 1.0 / len(points))
                    newell = (0.0, 0.0, 0.0)
                    for i, p in enumerate(points):
                        q = points[(i + 1) % len(points)]
                        newell = _add(newell, (
                            (p[1] - q[1]) * (p[2] + q[2]),
                            (p[2] - q[2]) * (p[0] + q[0]),
                            (p[0] - q[0]) * (p[1] + q[1]),
                        ))
                    normal = _normalize(newell)
                    # The cap faces away from the body of the piece.
                    if _dot(normal, _sub(center, centroid)) < 0:
                        normal = _scale(normal, -1.0)
                        points = list(reversed(points))
                    for i in range(len(points)):
                        p0, p1 = points[i], points[(i + 1) % len(points)]
                        tri_normal = _cross(_sub(p0, center), _sub(p1, center))
                        if _dot(tri_normal, normal) < 0:
                            p0, p1 = p1, p0
                        cap_tris.append((center, p0, p1, normal))

            piece_name = re.sub(r"[^A-Za-z0-9_]+", "_", piece).lower()
            xml_path = tmp / f"gib_{piece_name}.mesh.xml"
            tris = _write_piece_xml(
                xml_path,
                [(submeshes[si], faces) for si, faces in sorted(by_sub.items())],
                pivot, cap_tris, args.cap_material, args.cap_uv_scale,
            )
            mesh_out = out_dir / f"gib_{piece_name}.mesh"
            _run_converter(converter, xml_path, mesh_out)
            if args.keep_xml:
                shutil.copy2(xml_path, out_dir / xml_path.name)
            manifest_lines.append(
                f"piece gib_{piece_name} bone {piece_bone[piece]} "
                f"pivot {pivot[0]:.6f} {pivot[1]:.6f} {pivot[2]:.6f} "
                f"radius {radius:.6f} tris {tris}"
            )
            summary.append(f"  gib_{piece_name:<24} bone {piece_bone[piece]:<22} tris {tris:>5} caps {len(cap_tris):>4} r {radius:.3f}")

        (out_dir / "gibs.txt").write_text("\n".join(manifest_lines) + "\n", encoding="utf-8")

    print(f"{mesh_path.name}: {len(pieces)} gibs from {total_faces} faces (min {min_faces} faces/bone)")
    print("\n".join(summary))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
