"""Inspect legacy SDF/VDF ANIM data and Ogre meshes when an animated part misbehaves in Redux.

  python sdf_anim_tools.py anim  <file.sdf|file.vdf>          ANIM elements, per-part keys, GEO parents
  python sdf_anim_tools.py bones <file.mesh> <file.skeleton>  per-bone vertex bounding boxes
  python sdf_anim_tools.py faces <file.mesh> <file.skeleton> [bone]
                                                             per-bone face directions; flags faces whose
                                                             normal points into the part (back-face culled
                                                             once the part turns past 90 degrees)

Compare a custom model with 3+ working stock models (StockODFFiles\\*.sdf, BZ_ASSETS\\common\\models)
before reversing the engine.  See SDF_ANIM_BONE_POSING.md.

ANIM parsing reuses the bz98tools Blender add-on (found under %APPDATA%\\Blender Foundation\\Blender\\*,
or set BZ98TOOLS).  Binary .mesh/.skeleton files go through its OgreXMLConverter.exe; .xml inputs are
read directly.
"""
import glob
import os
import re
import subprocess
import sys
import tempfile
import types
from collections import defaultdict


def bz98tools():
    d = os.environ.get("BZ98TOOLS")
    if not d:
        hits = sorted(glob.glob(os.path.join(os.environ.get("APPDATA", ""), "Blender Foundation", "Blender",
                                             "*", "scripts", "addons", "bz98tools")))
        if not hits:
            sys.exit("bz98tools add-on not found; set BZ98TOOLS")
        d = hits[-1]
    if "bzt" not in sys.modules:  # load the add-on's modules as a package without importing bpy
        pkg = types.ModuleType("bzt")
        pkg.__path__ = [d]
        sys.modules["bzt"] = pkg
    return d


def rounded(v, n=3):
    return [round(x, n) for x in v]


def print_keys(name, parent, m2, rots, poss):
    print(f"OR {name} parent={parent} m2={rounded(m2)} rotkeys={len(rots)} poskeys={len(poss)}")
    for tag, keys, n in (("R", rots, 4), ("P", poss, 3)):
        show = keys if len(keys) <= 6 else keys[:3] + [None] + keys[-2:]
        for k in show:
            print("   ...") if k is None else print(f"   {tag} {k.frame} {rounded(k.translate, n)}")


def cmd_anim(path):
    bz98tools()
    data = open(path, "rb").read()
    if path.lower().endswith(".vdf"):
        from bzt import vdf_classes, vdf_file
        p = vdf_file.parse_vdf(data)
        parent = {}
        for raw in p.band_records(0):
            g = vdf_classes.GEOData()
            g.Read(raw, 0)
            parent[g.name] = g.parent
        els, ors, rots, poss = p.anim_elements, p.anim_orientations, p.anim_rotations, p.anim_positions
    else:
        from bzt import sdf_classes as S
        o = 0
        for hdr in (S.SDFHeader(), S.SDFCHeader()):
            o = hdr.Read(data, o)
        g = S.SGEOHeader()
        o = g.Read(data, o)
        geos = []
        for _ in range(6 * g.geocount):  # six LOD bands
            r = S.GEOData()
            o = r.Read(data, o)
            geos.append(r)
        parent = {r.name: r.parent for r in geos[:g.geocount]}
        a = S.ANIMHeader()
        o = a.Read(data, o)

        def read(cls, n):
            nonlocal o
            out = []
            for _ in range(n):
                r = cls()
                o = r.Read(data, o)
                out.append(r)
            return out
        els = read(S.ANIMElement, a.elementscount)
        ors = read(S.ANIMOrientation, a.orientationscount)
        rots = read(S.ANIMRotation, a.rotationcount)
        read(S.ANIMTranslation2, a.translation2count)
        poss = read(S.ANIMPosition, a.positioncount)
    for e in els:
        print("EL", {k: v for k, v in vars(e).items() if not k.startswith("_")})
    for r in ors:
        print_keys(r.name, parent.get(r.name), r.matrix2,
                   rots[r.rotationindex:r.rotationindex + r.rotationcount],
                   poss[r.positionindex:r.positionindex + r.positioncount])


def xml(path):
    if path.lower().endswith(".xml"):
        return open(path).read()
    conv = os.path.join(bz98tools(), "ogretools", "OgreXMLConverter.exe")
    out = os.path.join(tempfile.mkdtemp(), os.path.basename(path) + ".xml")
    # it may crash after writing when the mesh's skeleton is not beside it; the XML is still complete
    subprocess.run([conv, path, out], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if not os.path.exists(out):
        sys.exit(f"OgreXMLConverter failed on {path}")
    return open(out).read()


def submeshes(mesh, skel):
    """Yield (material, positions, {vertex: bone name}, faces) for each submesh."""
    names = {int(i): n for i, n in re.findall(r'<bone id="(\d+)" name="([^"]+)"', xml(skel))}
    for s in re.findall(r"<submesh .*?</submesh>", xml(mesh), re.S):
        mat = re.search(r'material="([^"]+)"', s)[1]
        pos = [tuple(map(float, m)) for m in re.findall(r'<position x="([^"]+)" y="([^"]+)" z="([^"]+)"', s)]
        vb = {int(v): names[int(b)] for v, b in
              re.findall(r'<vertexboneassignment vertexindex="(\d+)" boneindex="(\d+)"', s)}
        faces = [tuple(map(int, f)) for f in re.findall(r'<face v1="(\d+)" v2="(\d+)" v3="(\d+)"', s)]
        yield mat, pos, vb, faces


def cmd_bones(mesh, skel):
    box = {}
    for _, pos, vb, _ in submeshes(mesh, skel):
        for v, b in vb.items():
            lo, hi = box.setdefault(b, ([1e9] * 3, [-1e9] * 3))
            for k in range(3):
                lo[k], hi[k] = min(lo[k], pos[v][k]), max(hi[k], pos[v][k])
    for b, (lo, hi) in sorted(box.items()):
        print(f"{b:12s} min {rounded(lo, 2)} max {rounded(hi, 2)}")


def cmd_faces(mesh, skel, only=None):
    """Inward test: normal . (face centre - part centroid) < 0.  Exact for convex parts (doors, ramps,
    plates); concave parts such as a hull with an open bay legitimately report their inner walls."""
    for mat, pos, vb, faces in submeshes(mesh, skel):
        per = defaultdict(list)
        for f in faces:
            b = {vb.get(i) for i in f}
            if len(b) == 1 and (only is None or only in b):
                per[b.pop()].append(f)
        for bone, fs in sorted(per.items(), key=lambda kv: str(kv[0])):
            vs = {i for f in fs for i in f}
            c = [sum(pos[i][k] for i in vs) / len(vs) for k in range(3)]
            dirs, inward = defaultdict(int), []
            for f in fs:
                a, b, d = (pos[i] for i in f)
                u = [b[k] - a[k] for k in range(3)]
                v = [d[k] - a[k] for k in range(3)]
                n = (u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0])
                area = sum(x * x for x in n) ** 0.5 / 2
                k = max(range(3), key=lambda k: abs(n[k]))
                dirs["xyz"[k] + ("+" if n[k] > 0 else "-")] += 1
                m = [(a[j] + b[j] + d[j]) / 3 for j in range(3)]
                if sum(n[j] * (m[j] - c[j]) for j in range(3)) < 0:
                    inward.append((area, rounded(m, 2), "xyz"[k] + ("+" if n[k] > 0 else "-")))
            print(f"{mat} {bone}: {len(fs)} faces {dict(dirs)} inward {len(inward)}"
                  f" ({sum(x[0] for x in inward):.1f} m2)")
            for area, centre, axis in sorted(inward, reverse=True)[:8]:
                print(f"   inward {axis} area {area:.1f} at {centre}")


if __name__ == "__main__":
    cmds = {"anim": cmd_anim, "bones": cmd_bones, "faces": cmd_faces}
    if len(sys.argv) < 3 or sys.argv[1] not in cmds:
        sys.exit(__doc__)
    cmds[sys.argv[1]](*sys.argv[2:])
