"""Compile every eligible terrain permutation and verify DXBC stage linkage."""
import argparse
import os
from pathlib import Path
import re
import struct
import subprocess


def signature(path, tag, control_points=False):
    data = path.read_bytes()
    assert data[:4] == b"DXBC", path
    count = struct.unpack_from("<I", data, 28)[0]
    for offset in struct.unpack_from("<" + "I" * count, data, 32):
        if data[offset:offset + 4] != tag:
            continue
        size = struct.unpack_from("<I", data, offset + 4)[0]
        chunk = data[offset + 8:offset + 8 + size]
        entries = struct.unpack_from("<I", chunk)[0]
        result = []
        for i in range(entries):
            name, index, system, component, register, mask, _ = struct.unpack_from(
                "<IIIIIBB", chunk, 8 + 24 * i)
            semantic = chunk[name:chunk.index(b"\0", name)].decode()
            if control_points and semantic == "SV_POSITION":
                system = 1
            result.append((semantic, index, system, component, register, mask))
        return result
    raise ValueError(f"{path}: missing {tag!r}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--fxc", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    payload = root / "resources/renderer/enhanced"
    if args.fxc:
        fxc = args.fxc
    else:
        sdk = Path(os.environ.get("ProgramFiles(x86)", r"C:\Program Files (x86)")) / "Windows Kits/10/bin"
        candidates = sorted(sdk.glob("10.*/x86/fxc.exe"))
        if not candidates:
            raise FileNotFoundError("Windows SDK fxc.exe unavailable; use --fxc")
        fxc = candidates[-1]
    out = args.output or root / "build/terrain-tessellation"
    out.mkdir(parents=True, exist_ok=True)
    variants = {}
    text = (payload / "openshim_enhanced_terrain.program").read_text(encoding="utf-8")
    # Remove commented declarations/defines before enumerating compile inputs.
    text = re.sub(r"//[^\r\n]*", "", text)
    for match in re.finditer(r"vertex_program\s+(\S+)\s+hlsl\s*\{(.*?)\n\}", text, re.S):
        def value(key):
            found = re.search(r"^\s*" + key + r"\s+([^\r\n]+)", match[2], re.M)
            return found[1].strip() if found else ""
        defines = value("preprocessor_defines")
        if (value("source") != "openshim_enhanced_terrain-sm4.hlsl" or
                value("entry_point") != "terrain_vertex" or
                not value("target").startswith("vs_4") or
                "VERTEX_LIGHTING" in defines):
            continue
        variants[defines] = (value("source"), value("target"))
    assert variants, "no eligible terrain vertex permutations"
    compiled = 0
    for index, (defines, (source, target)) in enumerate(variants.items()):
        flags = []
        for define in defines.split(","):
            if define.strip():
                flags += ["/D", define.strip() if "=" in define else define.strip() + "=1"]

        def compile_shader(file, profile, entry, name, extra=()):
            nonlocal compiled
            result = out / (name + ".cso")
            run = subprocess.run([str(fxc), "/nologo", "/Gec", "/O3", "/T", profile,
                                  "/E", entry, *flags, *extra, "/Fo", str(result),
                                  str(payload / file)], capture_output=True, text=True)
            if run.returncode:
                raise RuntimeError(f"{profile} {defines}:\n{run.stdout}\n{run.stderr}")
            compiled += 1
            return result

        vertex = compile_shader(source, target, "terrain_vertex", f"{index}-vertex")
        expected = signature(vertex, b"OSGN")
        for factor, relief in ((1, False), (2, False), (4, False), (2, True), (4, True)):
            stage_files = {}
            for stage, entry in (("hs", "TerrainHull"), ("ds", "TerrainDomain")):
                stage_files[stage] = compile_shader(
                    "openshim_terrain_tessellation_test.hlsl", stage + "_5_0", entry,
                    f"{index}-{factor}-{'relief' if relief else 'baseline'}-{stage}",
                    ["/D", f"OPENSHIM_TESS_FACTOR={factor}"] +
                    (["/D", "OPENSHIM_RELIEF_TEST=1", "/D", "OPENSHIM_RELIEF_AMPLITUDE=0.25"] if relief else []))
            for stage in ("hs", "ds"):
                for tag in (b"ISGN", b"OSGN"):
                    actual = signature(stage_files[stage], tag,
                                       (stage, tag) in (("hs", b"OSGN"), ("ds", b"ISGN")))
                    assert actual == expected, (defines, factor, stage, tag, expected, actual)
    print(f"PASS: {compiled} shaders; {len(variants)} terrain permutations; "
          "factors 1/2/4 and micro-relief; VS -> HS -> DS signatures and registers match.")


if __name__ == "__main__":
    main()
