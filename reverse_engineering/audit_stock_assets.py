"""
Stock Battlezone 98 Redux asset LOD / bounds / renderability audit.

Parses every stock `.mesh` under `<GameRoot>\\BZ_ASSETS\\common\\models`,
every `.material` script under `BZ_ASSETS` and `BZ_ASSETS_CORE`, and the ODF
inventory inside `bzone.zfs`, then emits a machine-verifiable inventory
(JSON) plus a work-order manifest (CSV).

Mesh binary parsing reuses the BZ98R Blender ToolKit's validated Ogre 1.100
serializer (`bzrmodelporter`). The toolkit skips M_MESH_LOD, so this script
adds its own raw walker for mesh-LOD usage chunks (layout per pinned
ogre-1.10.0 MeshSerializerImpl.cpp: strategy string, ushort numLods, then one
M_MESH_LOD_MANUAL / M_MESH_LOD_GENERATED chunk per level with a float
userValue/distance ahead of each payload).

Typical usage:

    python reverse_engineering/audit_stock_assets.py ^
        --game-root "C:\\Program Files (x86)\\GOG Galaxy\\Games\\Battlezone 98 Redux" ^
        --out reverse_engineering/asset_audit

Static-only by design; runtime LOD selection evidence is merged later from
profiler captures (see the accompanying report).
"""

from __future__ import annotations

import argparse
import csv
import io
import json
import math
import os
import re
import struct
import sys
import tempfile
import types
from collections import Counter, defaultdict
from dataclasses import dataclass, field
from pathlib import Path

DEFAULT_GAME_ROOT = (
    r"C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux"
)
DEFAULT_TOOLKIT = str(Path.home() / "Documents" / "GIT" / "BZ98RBlenderToolKit")

CHUNK_HEADER_SIZE = 6  # ushort id + uint length (Ogre chunked serialization)

# Top-level chunk ids we need in the pre-pass (subset of MeshChunkID).
M_MESH = 0x3000
M_MESH_SKELETON_LINK = 0x6000
M_MESH_BONE_ASSIGNMENT = 0x7000
M_MESH_LOD = 0x8000
M_MESH_LOD_MANUAL = 0x8110
M_MESH_LOD_GENERATED = 0x8120
M_MESH_BOUNDS = 0x9000

# Bounds sanity thresholds (world units; BZ scale is metres).
IMPLAUSIBLE_EXTENT = 10_000.0
ZERO_EXTENT_EPS = 1e-6
BOUNDS_TOL_ABS = 0.01
BOUNDS_TOL_REL = 0.02  # 2% of max extent
RADIUS_TOL_REL = 0.05  # 5% mismatch against best radius model

# ---------------------------------------------------------------------------
# Toolkit bootstrap (bypass bz98tools/__init__.py, which imports bpy)
# ---------------------------------------------------------------------------


def load_toolkit(toolkit_root: str):
    sys.path.insert(0, toolkit_root)
    stub = types.ModuleType("bz98tools")
    stub.__path__ = [str(Path(toolkit_root) / "bz98tools")]
    sys.modules["bz98tools"] = stub
    from bz98tools.bzrmodelporter.ogremesh_serializer import MeshSerializer
    from bz98tools.bzrmodelporter.ogremesh import VES, VET, OT

    return MeshSerializer, VES, VET, OT


def read_cstring(data: bytes, pos: int) -> tuple[str, int]:
    end = data.index(b"\x00", pos)
    return data[pos:end].decode("ascii", errors="replace"), end + 1


def read_nlt_string(data: bytes, pos: int) -> tuple[str, int]:
    """BZ98R Ogre serialization writes newline-terminated strings."""
    end = data.index(b"\n", pos)
    return data[pos:end].decode("latin-1"), end + 1


class ChunkCursor:
    """Sequential reader over Ogre chunked binary data."""

    def __init__(self, data: bytes, pos: int = 0):
        self.data = data
        self.pos = pos

    def u16(self):
        (v,) = struct.unpack_from("<H", self.data, self.pos)
        self.pos += 2
        return v

    def u32(self):
        (v,) = struct.unpack_from("<I", self.data, self.pos)
        self.pos += 4
        return v

    def f32(self):
        (v,) = struct.unpack_from("<f", self.data, self.pos)
        self.pos += 4
        return v

    def string(self):
        s, nxt = read_nlt_string(self.data, self.pos)
        self.pos = nxt
        return s

    def header(self):
        """Returns (id, total_size, end_offset). BZ98R Ogre chunk lengths
        INCLUDE the 6-byte header itself."""
        start = self.pos
        cid = self.u16()
        size = self.u32()
        return cid, size, start + size


def parse_mesh_header_and_special_chunks(
    data: bytes,
) -> dict:
    """Walk the top-level M_MESH chunk far enough to capture the pieces the
    toolkit does not surface: mesh LOD usage list, bounds-chunk presence,
    skeleton link, and mesh-level bone assignment count."""
    cur = ChunkCursor(data, 0)
    if data[0:2] == b"\x00\x10":
        pass  # little endian marker, already assumed below
    else:
        raise ValueError("unexpected file endian marker")
    version, pos = read_nlt_string(data, 2)

    cur = ChunkCursor(data, pos)
    cid, size, body_end = cur.header()
    if cid != M_MESH:
        raise ValueError(f"expected M_MESH chunk, got 0x{cid:04X}")
    skeletally_animated = bool(cur.data[cur.pos])  # Ogre bool = 1 byte
    cur.pos += 1

    result = {
        "version": version,
        "skeletally_animated": skeletally_animated,
        "skeleton_name": None,
        "has_bounds_chunk": False,
        "mesh_bone_assignments": None,
        "mesh_lod": {
            "present": False,
            "strategy": None,
            "num_lods": 1,
            "levels": [],
        },
        "unknown_top_level_chunks": [],
    }

    while cur.pos < body_end:
        cid, csize, cend = cur.header()
        if cid == M_MESH_SKELETON_LINK:
            result["skeleton_name"] = cur.string()
        elif cid == M_MESH_BOUNDS:
            result["has_bounds_chunk"] = True
            cur.pos = cend
        elif cid == M_MESH_BONE_ASSIGNMENT:
            # count occurrences by walking siblings is awkward; the toolkit
            # reports these, so just note presence here.
            result["mesh_bone_assignments"] = True
            cur.pos = cend
        elif cid == M_MESH_LOD:
            # header() returns csize that includes the 6-byte header; cur.pos
            # is already past the header, so pass the absolute end offset to
            # avoid parsing 6 bytes into the following sibling chunk.
            lod = parse_mesh_lod_chunk(ChunkCursor(cur.data, cur.pos), cend - cur.pos)
            result["mesh_lod"] = lod
            cur.pos = cend
        else:
            result["unknown_top_level_chunks"].append(hex(cid))
            cur.pos = cend
    return result


def parse_mesh_lod_chunk(cur: ChunkCursor, size: int) -> dict:
    end = cur.pos + size
    out = {"present": True, "strategy": None, "num_lods": 1, "levels": []}
    try:
        out["strategy"] = cur.string()
        num_lods = cur.u16()
        out["num_lods"] = num_lods
        # level 0 is the base mesh; serialized entries start at level 1
        while cur.pos < end:
            cid, csize, cend = cur.header()
            distance = cur.f32()
            entry = {
                "index": len(out["levels"]) + 1,
                "kind": {M_MESH_LOD_MANUAL: "manual", M_MESH_LOD_GENERATED: "generated"}.get(
                    cid, f"unknown_0x{cid:04X}"
                ),
                "distance": distance,
                "manual_mesh": None,
                "total_indices": None,
            }
            if cid == M_MESH_LOD_MANUAL:
                entry["manual_mesh"] = cur.string()
            cur.pos = cend
            out["levels"].append(entry)
    except Exception as exc:  # malformed LOD chunk: record and keep auditing
        out["parse_error"] = repr(exc)
        cur.pos = end
    return out


# ---------------------------------------------------------------------------
# Geometry diagnostics
# ---------------------------------------------------------------------------


def numpy_dtype_for(vet, VET):
    mapping = {
        VET.FLOAT1: ("f4", 1),
        VET.FLOAT2: ("f4", 2),
        VET.FLOAT3: ("f4", 3),
        VET.FLOAT4: ("f4", 4),
        VET.DOUBLE1: ("f8", 1),
        VET.DOUBLE2: ("f8", 2),
        VET.DOUBLE3: ("f8", 3),
        VET.DOUBLE4: ("f8", 4),
    }
    if vet not in mapping:
        return None
    dt, cnt = mapping[vet]
    return np.dtype(dt), cnt


try:
    import numpy as np
except ImportError:  # pragma: no cover
    np = None


def extract_positions(vd, VES, VET):
    el = vd.vertex_declaration.get_position_vertex_element()
    if el is None:
        return None, "no_position_element"
    info = numpy_dtype_for(el.type, VET)
    if info is None:
        return None, f"unsupported_position_type_{VET.label(el.type)}"
    dtype, comps = info
    if comps < 3:
        return None, f"position_components_{comps}"
    buf = vd.vertex_buffer_map.get(el.source)
    if buf is None:
        return None, "missing_source_buffer"
    stride = buf.vertex_size
    expected = vd.vertex_count * stride
    if buf.buffer.nbytes < expected:
        return None, "short_source_buffer"
    raw = np.frombuffer(buf.buffer.obj, dtype=np.uint8, count=expected)
    cols = np.frombuffer(
        raw.tobytes(), dtype=np.float32, count=vd.vertex_count * (stride // 4)
    )
    cols = cols.reshape(vd.vertex_count, stride // 4)
    off = el.offset // 4
    pts = cols[:, off : off + 3].astype(np.float64)
    return pts, None


def stream_summary(vd, VES, VET):
    decl = []
    for el in sorted(
        vd.vertex_declaration.vertex_element_list, key=lambda e: (e.source, e.offset)
    ):
        decl.append(
            {
                "source": el.source,
                "semantic": VES.label(el.semantic),
                "type": VET.label(el.type),
                "offset": el.offset,
                "index": el.index,
            }
        )
    buffers = {}
    for src, buf in vd.vertex_buffers():
        expected = vd.vertex_count * buf.vertex_size
        buffers[str(src)] = {
            "vertex_size": buf.vertex_size,
            "bytes": int(buf.buffer.nbytes),
            "expected_bytes": int(expected),
            "size_ok": int(buf.buffer.nbytes) == int(expected),
        }
    return decl, buffers


# ---------------------------------------------------------------------------
# Material script parsing
# ---------------------------------------------------------------------------


@dataclass
class TechniqueInfo:
    scheme: str | None = None
    lod_index: int | None = None
    passes: int = 0
    texture_units: int = 0


@dataclass
class MaterialDef:
    name: str
    parent: str | None
    file: str
    techniques: list[TechniqueInfo] = field(default_factory=list)
    lod_values: list[float] = field(default_factory=list)
    lod_distances: list[float] = field(default_factory=list)
    texture_aliases: dict[str, str] = field(default_factory=dict)
    vars: dict[str, str] = field(default_factory=dict)
    shadow_refs: list[str] = field(default_factory=list)


def strip_comment(line: str) -> str:
    idx = line.find("//")
    return line[:idx] if idx >= 0 else line


TOKEN_RE = re.compile(r'"[^"]*"|\S+')


def parse_material_scripts(paths: list[Path]) -> dict[str, MaterialDef]:
    materials: dict[str, MaterialDef] = {}

    def ensure(name: str, file: str) -> MaterialDef:
        if name not in materials:
            materials[name] = MaterialDef(name=name, parent=None, file=file)
        return materials[name]

    for path in paths:
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError as exc:
            print(f"WARN material unreadable {path}: {exc}")
            continue
        lines = [strip_comment(l).rstrip() for l in text.splitlines()]

        current_mat: MaterialDef | None = None
        tech: TechniqueInfo | None = None
        in_pass = False

        # First handle imports so inheritance resolution can find bases.
        for line in lines:
            m = re.match(r'\s*import\s+\*\s+from\s+"([^"]+)"', line)
            if m and current_mat is None:
                continue  # recorded implicitly via file scan

        depth_stack: list[str] = []
        for raw in lines:
            line = raw.strip()
            if not line:
                continue
            toks = TOKEN_RE.findall(line)
            head = toks[0] if toks else ""
            brace_open = line.endswith("{") or "{" in line
            brace_close = "}" in line

            if head == "material":
                m = re.match(r'material\s+([\w.\-]+)\s*(?::\s*([\w.\-]+))?\s*\{?', line)
                if m:
                    current_mat = ensure(m.group(1), str(path))
                    current_mat.parent = m.group(2)
                    tech = None
                    in_pass = False
                continue
            if current_mat is None:
                continue
            if head == "technique":
                tech = TechniqueInfo()
                current_mat.techniques.append(tech)
                in_pass = False
                continue
            if head == "pass":
                in_pass = True
                if tech is not None:
                    tech.passes += 1
                continue
            if head == "texture_unit":
                if tech is not None:
                    tech.texture_units += 1
                continue
            if head == "lod_values":
                vals = re.findall(r"-?\d+(?:\.\d+)?(?:e-?\d+)?", line[len("lod_values"):])
                current_mat.lod_values.extend(float(v) for v in vals)
                continue
            if head == "lod_distances":
                vals = re.findall(r"-?\d+(?:\.\d+)?(?:e-?\d+)?", line[len("lod_distances"):])
                current_mat.lod_distances.extend(float(v) for v in vals)
                continue
            if head == "scheme" and tech is not None:
                tech.scheme = toks[1].strip('"') if len(toks) > 1 else None
                continue
            if head == "lod_index" and tech is not None:
                try:
                    tech.lod_index = int(toks[1])
                except (IndexError, ValueError):
                    pass
                continue
            if head == "set_texture_alias":
                if len(toks) >= 3:
                    current_mat.texture_aliases[toks[1]] = toks[2].strip('"')
                continue
            if head.startswith("set $"):
                parts = line.split(None, 2)
                if len(parts) >= 3:
                    current_mat.vars[parts[1]] = parts[2]
                continue
            if "shadow" in line.lower():
                current_mat.shadow_refs.append(line.strip())
    return materials


def resolve_material_techniques(
    name: str, materials: dict[str, MaterialDef], _seen=None
) -> list[TechniqueInfo]:
    """Ogre semantics: a material that declares ANY technique uses ONLY its own
    techniques; otherwise it inherits its parent's full set."""
    seen = _seen or set()
    if name in seen or name not in materials:
        return []
    seen.add(name)
    mat = materials[name]
    if mat.techniques:
        return mat.techniques
    if mat.parent:
        return resolve_material_techniques(mat.parent, materials, seen)
    return []


def resolve_inherited_scalar_list(
    name: str, attr: str, materials: dict[str, MaterialDef], _seen=None
) -> list[float]:
    """Nearest declaration of a material-level list wins down the parent chain."""
    seen = _seen or set()
    if name in seen or name not in materials:
        return []
    seen.add(name)
    mat = materials[name]
    vals = getattr(mat, attr)
    if vals:
        return list(vals)
    if mat.parent:
        return resolve_inherited_scalar_list(mat.parent, attr, materials, seen)
    return []


# ---------------------------------------------------------------------------
# ODF extraction / classification
# ---------------------------------------------------------------------------


def load_odf_classes(game_root: Path) -> dict[str, dict]:
    zfs_path = game_root / "bzone.zfs"
    if not zfs_path.exists():
        return {}
    try:
        from bz98tools.zfs_reader import ZFSReader
    except Exception as exc:
        print(f"WARN zfs_reader unavailable: {exc}")
        return {}
    classes: dict[str, dict] = {}
    try:
        reader = ZFSReader(str(zfs_path))
        reader.open()
        files = [
            str(f) for f in reader.list_files() if str(f).lower().endswith(".odf")
        ]
        tmp = Path(tempfile.mkdtemp(prefix="bzr_odf_", dir=os.environ.get("OPENCODE_TMP"))
                   if os.environ.get("OPENCODE_TMP") else tempfile.gettempdir())
        odf_dir = tmp / "odf"
        odf_dir.mkdir(parents=True, exist_ok=True)
        label_re = re.compile(r"^\s*classLabel\s*=\s*(\S+)", re.MULTILINE | re.IGNORECASE)
        for fname in files:
            base = Path(fname).stem.lower()
            try:
                reader.extract(fname, str(odf_dir))
            except Exception:
                continue
        reader.close()
        for p in odf_dir.glob("*.odf"):
            try:
                txt = p.read_text(encoding="ascii", errors="replace")
            except OSError:
                continue
            m = label_re.search(txt)
            classes[p.stem.lower()] = {"classLabel": m.group(1) if m else None}
    except Exception as exc:
        print(f"WARN odf extraction failed: {exc}")
    return classes


CLASS_PREFIX_TABLE = {
    "tank": "tank",
    "figh": "scout",
    "rckt": "rocket_tank",
    "artl": "artillery",
    "apc": "apc_service",
    "walk": "walker",
    "mine": "minelayer",
    "turr": "turret_tank",
    "pilo": "pilot",
    "haul": "tug",
    "scav": "scavenger",
    "recy": "recycler",
    "fact": "factory",
    "armo": "armory",
}


def classify_asset(stem: str, odf_classes: dict[str, dict]) -> dict:
    s = stem.lower()
    cls = {"odf_class": None, "faction_prefix": None, "heuristic_class": None}
    for prefix, faction in (
        ("av", "isdf"),
        ("bv", "bdog"),
        ("cv", "chinese"),
        ("sv", "ccon"),
        ("ab", "building"),
        ("bb", "building"),
        ("gb", "building"),
        ("sb", "building"),
    ):
        if s.startswith(prefix) and len(s) > 2:
            cls["faction_prefix"] = faction
            break
    if s in odf_classes:
        cls["odf_class"] = odf_classes[s]["classLabel"]
    for suffix, label in CLASS_PREFIX_TABLE.items():
        if suffix in s:
            cls["heuristic_class"] = label
            break
    return cls


# ---------------------------------------------------------------------------
# Per-mesh audit
# ---------------------------------------------------------------------------


def audit_mesh(path: Path, MeshSerializer, VES, VET, OT) -> dict:
    rec: dict = {"file": str(path), "name": path.stem}
    data = path.read_bytes()
    rec["bytes"] = len(data)
    rec["sha256_prefix"] = None
    import hashlib

    rec["sha256"] = hashlib.sha256(data).hexdigest()

    parse_error = None
    try:
        special = parse_mesh_header_and_special_chunks(data)
    except Exception as exc:
        special = {}
        parse_error = f"header_walk: {exc!r}"
        serializer = MeshSerializer(io.BytesIO(data))
        try:
            serializer.read_file_header()
        except Exception:
            rec["fatal"] = "unreadable"
            return rec
        special = {
            "version": getattr(serializer, "version", "?"),
            "skeletally_animated": None,
            "skeleton_name": None,
            "has_bounds_chunk": False,
            "mesh_lod": {"present": False, "num_lods": 1, "levels": []},
        }

    rec.update(
        {
            "version": special.get("version"),
            "skeletally_animated": special.get("skeletally_animated"),
            "skeleton_name": special.get("skeleton_name"),
            "has_bounds_chunk": special.get("has_bounds_chunk", False),
            "mesh_lod": special.get("mesh_lod"),
            "header_parse_error": parse_error,
        }
    )

    # Full parse through the toolkit serializer.
    mesh = None
    tool_err = None
    try:
        serializer = MeshSerializer(io.BytesIO(data))
        mesh = serializer.read()
    except Exception as exc:
        tool_err = repr(exc)

    rec["toolkit_parse_error"] = tool_err
    if mesh is None:
        rec["bounds_status"] = "unparseable"
        return rec

    # ---- geometry ----
    submeshes = []
    issues = []

    def audit_vertex_data(vd, label):
        decl, bufs = stream_summary(vd, VES, VET)
        bad_bufs = [s for s, b in bufs.items() if not b["size_ok"]]
        if bad_bufs:
            issues.append(f"{label}: buffer size mismatch sources={bad_bufs}")
        pts, err = extract_positions(vd, VES, VET)
        stats = {"decl": decl, "buffers": bufs, "vertex_count": vd.vertex_count}
        if err:
            stats["positions_error"] = err
            issues.append(f"{label}: positions undecodable ({err})")
            return stats, None
        finite = np.isfinite(pts).all()
        if not finite:
            issues.append(f"{label}: non-finite position values")
        aabb_min = pts.min(axis=0)
        aabb_max = pts.max(axis=0)
        stats["geometry_aabb"] = [round(float(v), 6) for v in np.r_[aabb_min, aabb_max]]
        stats["max_abs_vertex"] = float(np.abs(pts).max())
        stats["max_origin_dist"] = (
            round(float(np.linalg.norm(pts, axis=1).max()), 6) if len(pts) else 0.0
        )
        return stats, (aabb_min, aabb_max, bool(finite))

    shared_stats = None
    shared_geom = None
    if mesh.shared_vertex_data is not None:
        shared_stats, shared_geom = audit_vertex_data(mesh.shared_vertex_data, "shared")

    total_verts = 0
    total_tris = 0
    total_indices = 0
    materials_used = []
    index_oob = 0
    for sm in mesh.submesh_list:
        sm_rec = {
            "name": sm.get_name(),
            "material": sm.material_name,
            "use_shared_vertices": sm.use_shared_vertices,
            "operation_type": OT.name_map.get(sm.operation_type, f"OT_{sm.operation_type}"),
            "index_count": int(sm.index_count),
            "indices_32_bit": bool(sm.indices_32_bit),
            "bone_assignments": sm.get_bone_assignment_count(),
        }
        materials_used.append(sm.material_name)
        total_indices += int(sm.index_count)
        op = sm.operation_type
        if op == OT.TRIANGLE_LIST:
            tris = sm.index_count // 3
        elif op in (OT.TRIANGLE_STRIP, OT.TRIANGLE_FAN):
            tris = max(0, sm.index_count - 2)
        else:
            tris = 0
            issues.append(f"submesh{sm.submesh_index}: unusual operation type {op}")
        sm_rec["triangles"] = tris
        total_tris += tris

        arr = sm.get_index_array()
        if arr is not None and arr.size:
            vc = (
                mesh.shared_vertex_data.vertex_count
                if sm.use_shared_vertices and mesh.shared_vertex_data is not None
                else (sm.vertex_data.vertex_count if sm.vertex_data is not None else None)
            )
            if vc is not None:
                oob = int((arr >= vc).sum()) + int((arr < 0).sum())
                if oob:
                    index_oob += oob
                    issues.append(
                        f"submesh{sm.submesh_index}: {oob} indices out of range (verts={vc})"
                    )

        geom = None
        if not sm.use_shared_vertices and sm.vertex_data is not None:
            sm_stats, geom = audit_vertex_data(sm.vertex_data, f"submesh{sm.submesh_index}")
            sm_rec["vertex_data"] = sm_stats
            total_verts += sm_stats["vertex_count"]
        else:
            sm_rec["vertex_data"] = None
            total_verts += (
                mesh.shared_vertex_data.vertex_count
                if mesh.shared_vertex_data is not None and sm.submesh_index == 0
                else 0
            )
        sm_rec["bone_assignment_vertices"] = len(sm.bone_assignment_map)
        submeshes.append(sm_rec)

    if mesh.shared_vertex_data is not None:
        total_verts += 0  # counted above only when referenced; keep simple
    rec["submeshes"] = submeshes
    rec["shared_vertex_data"] = shared_stats
    rec["totals"] = {
        "vertices": total_verts,
        "triangles": total_tris,
        "indices": total_indices,
    }
    rec["materials_used"] = materials_used
    rec["name_table"] = {str(k): v for k, v in mesh.name_table.items()}
    rec["issues_geometry"] = issues

    # ---- bounds ----
    bounds_status = []
    stored = None
    if mesh.aabb is not None:
        vals = np.array(
            [
                mesh.aabb.min_x,
                mesh.aabb.min_y,
                mesh.aabb.min_z,
                mesh.aabb.max_x,
                mesh.aabb.max_y,
                mesh.aabb.max_z,
            ],
            dtype=np.float64,
        )
        if not np.isfinite(vals).all():
            bounds_status.append("nonfinite_serialized_bounds")
        extent = vals[3:] - vals[:3]
        if (extent <= ZERO_EXTENT_EPS).all():
            bounds_status.append("zero_extent_bounds")
        elif (extent > IMPLAUSIBLE_EXTENT).any():
            bounds_status.append("implausibly_large_bounds")
        stored = vals

    geoms = []
    if shared_geom:
        geoms.append(shared_geom)
    for sm_rec, sm in zip(submeshes, mesh.submesh_list):
        vd = sm.vertex_data
        if vd is not None:
            pts, err = extract_positions(vd, VES, VET)
            if pts is not None and np.isfinite(pts).all():
                geoms.append((pts.min(axis=0), pts.max(axis=0), True))

    geom_aabb = None
    if geoms:
        mins = np.min([g[0] for g in geoms], axis=0)
        maxs = np.max([g[1] for g in geoms], axis=0)
        geom_aabb = np.r_[mins, maxs]

    rec["stored_aabb"] = [round(float(v), 6) for v in stored] if stored is not None else None
    rec["geometry_aabb"] = (
        [round(float(v), 6) for v in geom_aabb] if geom_aabb is not None else None
    )
    rec["stored_radius"] = float(mesh.bound_radius) if mesh.bound_radius is not None else None

    if not special.get("has_bounds_chunk", False):
        bounds_status.append("missing_bounds_chunk")
    if stored is not None and geom_aabb is not None and np.isfinite(stored).all():
        tol = BOUNDS_TOL_ABS + BOUNDS_TOL_REL * float(
            np.abs(geom_aabb[3:] - geom_aabb[:3]).max(initial=1.0)
        )
        delta = float(np.abs(stored - geom_aabb).max())
        rec["bounds_vs_geometry_delta"] = round(delta, 6)
        if delta > tol:
            bounds_status.append("stale_vs_geometry")
        # Stored radius model (empirically exact on stock assets):
        # bounding sphere radius = max vertex distance from the origin.
        r_stored = float(mesh.bound_radius) if mesh.bound_radius is not None else None
        tight_radii = []
        for vd_stats in [shared_stats] + [
            s.get("vertex_data") for s in submeshes if s.get("vertex_data")
        ]:
            if vd_stats and "max_origin_dist" in vd_stats:
                tight_radii.append(vd_stats["max_origin_dist"])
        if r_stored is not None and math.isfinite(r_stored) and tight_radii:
            tight = max(tight_radii)
            rec["radius_tight_from_vertices"] = round(tight, 6)
            rel_err = abs(r_stored - tight) / max(tight, 1e-9)
            rec["radius_rel_error"] = round(rel_err, 6)
            if rel_err > RADIUS_TOL_REL:
                bounds_status.append("radius_inconsistent_with_geometry")
    elif stored is None and special.get("has_bounds_chunk", False):
        bounds_status.append("nonfinite_serialized_bounds")

    if not bounds_status and stored is not None:
        bounds_status.append("ok_finite")
    rec["bounds_status"] = ";".join(bounds_status) if bounds_status else "missing"

    # ---- skinning / GPU-source proxy ----
    rec["skinning"] = {
        "has_skeleton_link": bool(rec["skeleton_name"]),
        "mesh_bone_assignments_present": special.get("mesh_bone_assignments", False),
        "submeshes_with_assignments": sum(1 for s in submeshes if s["bone_assignments"]),
        "streams_note": (
            "runtime DX11 verification required for GPU-only source determination"
        ),
    }
    return rec


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--game-root", default=DEFAULT_GAME_ROOT)
    ap.add_argument("--toolkit", default=DEFAULT_TOOLKIT)
    ap.add_argument("--out", default=str(Path(__file__).parent / "asset_audit"))
    ap.add_argument("--skip-odf", action="store_true")
    args = ap.parse_args(argv)

    game_root = Path(args.game_root)
    out_dir = Path(args.out)
    out_dir.mkdir(parents=True, exist_ok=True)

    MeshSerializer, VES, VET, OT = load_toolkit(args.toolkit)

    models_root = game_root / "BZ_ASSETS" / "common" / "models"
    mesh_paths = sorted(models_root.rglob("*.mesh"))
    print(f"found {len(mesh_paths)} stock meshes")

    odf_classes = {} if args.skip_odf else load_odf_classes(game_root)
    print(f"odf classes: {len(odf_classes)}")

    records = []
    for i, p in enumerate(mesh_paths):
        rec = audit_mesh(p, MeshSerializer, VES, VET, OT)
        rec["relative"] = str(p.relative_to(game_root))
        rec["tro_variant"] = "TRO" in p.parts
        rec["classification"] = classify_asset(p.stem, odf_classes)
        records.append(rec)
        if (i + 1) % 40 == 0:
            print(f"  audited {i + 1}/{len(mesh_paths)}")

    # material scripts
    material_files = sorted((game_root / "BZ_ASSETS").rglob("*.material")) + sorted(
        (game_root / "BZ_ASSETS_CORE").rglob("*.material")
    )
    materials = parse_material_scripts(material_files)
    print(f"materials parsed: {len(materials)} from {len(material_files)} files")

    material_records = {}
    for name, mat in materials.items():
        eff = resolve_material_techniques(name, materials)
        schemes: dict[str, set[int]] = defaultdict(set)
        for t in eff:
            sch = t.scheme or "(default)"
            schemes[sch].add(t.lod_index if t.lod_index is not None else 0)
        material_records[name] = {
            "file": mat.file,
            "parent": mat.parent,
            "own_technique_count": len(mat.techniques),
            "effective_technique_count": len(eff),
            "schemes": {k: sorted(x for x in v if x is not None) for k, v in schemes.items()},
            "lod_values": resolve_inherited_scalar_list(name, "lod_values", materials),
            "lod_distances": resolve_inherited_scalar_list(
                name, "lod_distances", materials
            ),
            "shadow_ref_lines": mat.shadow_refs[:5],
            "texture_aliases": mat.texture_aliases,
        }

    # cross-reference meshes -> materials
    undefined_materials = defaultdict(list)
    for rec in records:
        resolved = {}
        for mname in rec.get("materials_used", []):
            mdef = material_records.get(mname)
            if mdef is None:
                undefined_materials[mname].append(rec["name"])
                resolved[mname] = None
            else:
                resolved[mname] = {
                    "techniques": mdef["effective_technique_count"],
                    "schemes": mdef["schemes"],
                    "lod_values": mdef["lod_values"],
                }
        rec["resolved_materials"] = resolved
    rec_issues = sorted(undefined_materials.items())

    inventory = {
        "game_root": str(game_root),
        "mesh_count": len(records),
        "material_files": [str(p) for p in material_files],
        "materials": material_records,
        "undefined_material_references": dict(rec_issues),
        "meshes": records,
    }
    inv_path = out_dir / "stock_asset_inventory.json"
    inv_path.write_text(json.dumps(inventory, indent=1), encoding="utf-8")
    print(f"wrote {inv_path}")

    # summary counts
    status_counter = Counter(r["bounds_status"] for r in records)
    print("bounds status:", dict(status_counter))
    lod_counter = Counter(r["mesh_lod"]["num_lods"] for r in records if r.get("mesh_lod"))
    print("mesh lod counts:", dict(lod_counter))

    # ---- work-order manifest (CSV) ----
    csv_path = out_dir / "stock_asset_manifest.csv"
    cols = [
        "asset",
        "class_type",
        "bounds_status",
        "mesh_lod_count",
        "material_lod_count",
        "runtime_lod_result",
        "shadow_behavior",
        "issue",
        "repair",
        "validation",
    ]
    with open(csv_path, "w", newline="", encoding="utf-8") as fh:
        w = csv.writer(fh)
        w.writerow(cols)
        for r in records:
            cls = r.get("classification", {})
            class_type = (
                cls.get("heuristic_class")
                or cls.get("odf_class")
                or cls.get("faction_prefix")
                or "unclassified"
            )
            issues = list(r.get("issues_geometry") or [])
            if r["bounds_status"] != "ok_finite":
                issues.append(f"bounds:{r['bounds_status']}")
            mat_issues = []
            for mname, resolved in (r.get("resolved_materials") or {}).items():
                if resolved is None:
                    mat_issues.append(f"dangling_material_ref:{mname}")
            mesh_lod = r.get("mesh_lod") or {}
            mlod_n = int(mesh_lod.get("num_lods", 1))
            lod_vals = None
            for resolved in (r.get("resolved_materials") or {}).values():
                if resolved and resolved.get("lod_values"):
                    lod_vals = resolved["lod_values"]
                    break
            mlod_schemes = {}
            if lod_vals is not None:
                for mname, resolved in (r.get("resolved_materials") or {}).items():
                    if resolved:
                        mlod_schemes.update(resolved["schemes"])
            mat_lod_desc = (
                f"{len(mlod_schemes)}schemes@{lod_vals}" if mlod_schemes else "none"
            )
            skin = r.get("skinning") or {}
            w.writerow(
                [
                    r["name"],
                    class_type,
                    r["bounds_status"],
                    mlod_n,
                    mat_lod_desc,
                    "pending_runtime",
                    (
                        "skeletal_animated_flag"
                        if r.get("skeletally_animated")
                        else "static"
                    ),
                    "; ".join(issues + mat_issues) if (issues or mat_issues) else "none_static",
                    "",
                    "",
                ]
            )
    print(f"wrote {csv_path}")


if __name__ == "__main__":
    main()
