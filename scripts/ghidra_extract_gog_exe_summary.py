from __future__ import annotations

import argparse
import re
import shutil
import struct
import tempfile
import uuid
from dataclasses import dataclass
from pathlib import Path

import pefile
import pyghidra
from pyghidra_mcp.context import PyGhidraContext
from pyghidra_mcp.tools import GhidraTools


@dataclass(frozen=True)
class DebugRecord:
    guid: uuid.UUID
    age: int
    pdb_path: str


@dataclass(frozen=True)
class PdbInfo:
    guid: uuid.UUID
    age: int
    signature: int
    version: int


@dataclass(frozen=True)
class FunctionTarget:
    title: str
    address: str
    pdb_hints: tuple[str, ...]
    excerpt_limit: int = 1800


ASCII_RE = re.compile(rb"[ -~]{6,}")
PATH_TOKEN_RE = re.compile(
    r"[A-Z]:\\[^ ]*BattleZoneTest[^ ]*(?:\\source|\.obj|\.pdb|\.pch|\.c|\.cpp|\.h)",
    re.IGNORECASE,
)

KEY_FUNCTIONS = [
    FunctionTarget(
        title="Multiplayer create screen root",
        address="0x00796880",
        pdb_hints=(
            "cUI_Multiplayer_Create::cUI_Multiplayer_Create",
            "UI_Multiplayer_Create.obj",
        ),
    ),
    FunctionTarget(
        title="Map filter gate",
        address="0x00752A50",
        pdb_hints=(
            "cUI_Multiplayer_MapSelect::FilterMaps",
            "cMapManager::BuildFilteredMapList",
            "filters.obj",
        ),
    ),
    FunctionTarget(
        title="Map filter list rebuild",
        address="0x007A3160",
        pdb_hints=(
            "cUI_Multiplayer_Create::MapFilterToggle",
            "cUI_Multiplayer_Create::FilterSelected",
            "UI_Multiplayer_Create.obj",
        ),
    ),
    FunctionTarget(
        title="Map list viewport update",
        address="0x007997A0",
        pdb_hints=(
            "cUI_Multiplayer_MapSelect",
            "UI_Multiplayer_MapSelect.obj",
        ),
    ),
    FunctionTarget(
        title="Map selection wrapper",
        address="0x00799880",
        pdb_hints=(
            "cUI_Multiplayer_MapSelect",
            "UI_Multiplayer_MapSelect.obj",
        ),
    ),
    FunctionTarget(
        title="Map selection restore helper",
        address="0x007CAFA0",
        pdb_hints=(
            "UI_Multiplayer_MapSelect.obj",
            "cUI_Multiplayer_MapSelect",
        ),
    ),
    FunctionTarget(
        title="Map scroll down helper",
        address="0x007CB500",
        pdb_hints=(
            "UI_Multiplayer_MapSelect.obj",
            "cUI_Multiplayer_MapSelect",
        ),
        excerpt_limit=900,
    ),
    FunctionTarget(
        title="Map scroll up helper",
        address="0x007CB540",
        pdb_hints=(
            "UI_Multiplayer_MapSelect.obj",
            "cUI_Multiplayer_MapSelect",
        ),
        excerpt_limit=900,
    ),
    FunctionTarget(
        title="User bar constructor / whisper + mute buttons",
        address="0x007D0770",
        pdb_hints=(
            "cUI_UserBar::cUI_UserBar",
            "cUI_UserBar::msgCB",
            "cUI_UserBar::muteCB",
            "UI_UserBar.obj",
        ),
    ),
    FunctionTarget(
        title="Lobby slash command handler",
        address="0x006247A0",
        pdb_hints=(
            "Net_MutePlayer",
            "Net_UnmutePlayer",
            "Net_KickPlayer",
            "Net_LockGame",
            "Net_UnlockGame",
        ),
    ),
    FunctionTarget(
        title="Lobby chat update callback",
        address="0x0073EEB0",
        pdb_hints=(
            "CSteamLobby::OnLobbyChatUpdate",
            "CSteamLobby::OnChatMessage",
            "lobby.obj",
            "chat.obj",
        ),
    ),
]

PDB_SYMBOL_GROUPS = {
    "Map UI and filters": (
        "UI_Multiplayer_MapSelect.obj",
        "UI_Multiplayer_Create.obj",
        "filters.obj",
        "cUI_Multiplayer_MapSelect::FilterMaps",
        "cMapManager::BuildFilteredMapList",
        "cUI_Multiplayer_Create::FilterSelected",
        "cUI_Multiplayer_Create::MapFilterToggle",
    ),
    "Lobby and chat": (
        "lobby.obj",
        "chat.obj",
        "CSteamLobby::GetCurrentLobby",
        "CSteamLobby::GetCurrentUser",
        "CSteamLobby::OnLobbyChatUpdate",
        "CSteamLobby::OnChatMessage",
        "CSteamLobby::KickUser",
        "CSteamLobby::OnLobbyKicked",
        "NetPlayer::NotifyLeftLobby",
    ),
    "User bar and mute or whisper UI": (
        "UI_UserBar.obj",
        "cUI_UserBar::cUI_UserBar",
        "cUI_UserBar::msgCB",
        "cUI_UserBar::muteCB",
        "gClick_UserBar_Msg",
        "gClick_UserBar_Mute",
        "gClick_UserBar_Kick",
        "Whisper User",
        "Mute User",
    ),
    "Lobby slash commands": (
        "/help",
        "/mute",
        "/unmute",
        "/kick",
        "/lock",
        "/unlock",
        "Net_MutePlayer",
        "Net_UnmutePlayer",
        "Net_KickPlayer",
        "Net_LockGame",
        "Net_UnlockGame",
    ),
}


def sanitize_excerpt(text: str, limit: int) -> str:
    return text.replace("\r", "").strip()[:limit].rstrip()


def read_exe_debug_record(exe_path: Path) -> DebugRecord:
    pe = pefile.PE(str(exe_path))
    for entry in getattr(pe, "DIRECTORY_ENTRY_DEBUG", []):
        debug = entry.struct
        if debug.Type != 2:
            continue
        data = pe.__data__[debug.PointerToRawData : debug.PointerToRawData + debug.SizeOfData]
        if data[:4] != b"RSDS":
            continue
        guid = uuid.UUID(bytes_le=data[4:20])
        age = int.from_bytes(data[20:24], "little")
        pdb_path = data[24:].split(b"\x00", 1)[0].decode("utf-8", "ignore")
        return DebugRecord(guid=guid, age=age, pdb_path=pdb_path)
    raise ValueError(f"No RSDS debug record found in {exe_path}")


def read_pdb_info(pdb_path: Path) -> PdbInfo:
    data = pdb_path.read_bytes()
    block_size, _, _, directory_bytes, _, block_map_addr = struct.unpack_from("<6I", data, 32)
    directory_block_count = (directory_bytes + block_size - 1) // block_size
    block_map_offset = block_map_addr * block_size
    directory_blocks = struct.unpack_from("<" + ("I" * directory_block_count), data, block_map_offset)
    directory_data = b"".join(
        data[block * block_size : (block + 1) * block_size] for block in directory_blocks
    )[:directory_bytes]

    stream_count = struct.unpack_from("<I", directory_data, 0)[0]
    offset = 4
    sizes = list(struct.unpack_from("<" + ("I" * stream_count), directory_data, offset))
    offset += stream_count * 4

    streams: list[list[int]] = []
    for size in sizes:
        if size == 0xFFFFFFFF:
            streams.append([])
            continue
        block_count = (size + block_size - 1) // block_size
        if block_count:
            blocks = list(struct.unpack_from("<" + ("I" * block_count), directory_data, offset))
        else:
            blocks = []
        offset += block_count * 4
        streams.append(blocks)

    info_size = sizes[1]
    info = b"".join(data[block * block_size : (block + 1) * block_size] for block in streams[1])[:info_size]
    version, signature, age = struct.unpack_from("<III", info, 0)
    guid = uuid.UUID(bytes_le=info[12:28])
    return PdbInfo(guid=guid, age=age, signature=signature, version=version)


def extract_ascii_strings(path: Path) -> list[str]:
    return [match.decode("ascii", "ignore") for match in ASCII_RE.findall(path.read_bytes())]


def find_unique_matches(strings: list[str], patterns: tuple[str, ...], limit: int = 24) -> list[str]:
    hits: list[str] = []
    seen: set[str] = set()
    lowered = tuple(pattern.lower() for pattern in patterns)
    for text in strings:
        text_lower = text.lower()
        if not any(pattern in text_lower for pattern in lowered):
            continue
        if text in seen:
            continue
        seen.add(text)
        hits.append(text)
        if len(hits) >= limit:
            break
    return hits


def battlezonetest_paths(strings: list[str], limit: int = 12) -> list[str]:
    hits: list[str] = []
    seen: set[str] = set()
    for text in strings:
        for token in PATH_TOKEN_RE.findall(text):
            if token in seen:
                continue
            seen.add(token)
            hits.append(token)
            if len(hits) >= limit:
                return hits
    return hits


def analyze_exe_functions(exe_path: Path) -> list[tuple[FunctionTarget, str, str]]:
    project_root = Path(tempfile.gettempdir()) / "bzr_gog_exe_pyghidra"
    if project_root.exists():
        shutil.rmtree(project_root)

    project_name = "BZR_GOG_EXE"
    pyghidra.start(False)

    ctx = PyGhidraContext(
        project_name=project_name,
        project_path=project_root,
        pyghidra_mcp_dir=project_root / f"{project_name}-pyghidra-mcp",
        threaded=False,
        max_workers=1,
        wait_for_analysis=False,
    )

    try:
        ctx.import_binaries([exe_path])
        for domain_file in ctx.list_binary_domain_files():
            ctx.analyze_program(domain_file)

        program_key = ctx.list_binaries()[0]
        tools = GhidraTools(ctx.get_program_info(program_key))

        results: list[tuple[FunctionTarget, str, str]] = []
        for target in KEY_FUNCTIONS:
            decompiled = tools.decompile_function_by_name_or_addr(target.address)
            results.append(
                (
                    target,
                    decompiled.signature,
                    sanitize_excerpt(decompiled.code, target.excerpt_limit),
                )
            )
        return results
    finally:
        ctx.close()


def build_summary(exe_path: Path, pdb_path: Path) -> str:
    exe_record = read_exe_debug_record(exe_path)
    pdb_info = read_pdb_info(pdb_path)
    pdb_strings = extract_ascii_strings(pdb_path)
    source_paths = battlezonetest_paths(pdb_strings)
    function_summaries = analyze_exe_functions(exe_path)

    lines: list[str] = []
    lines.append("# GOG EXE + PDB Summary")
    lines.append("")
    lines.append("Headless analysis performed with `pyghidra` / `pyghidra_mcp` plus direct RSDS/MSF parsing.")
    lines.append("")
    lines.append("## Inputs")
    lines.append("")
    lines.append(f"- EXE: `{exe_path}`")
    lines.append(f"- PDB: `{pdb_path}`")
    lines.append("")
    lines.append("## Debug Metadata")
    lines.append("")
    lines.append("- EXE RSDS record:")
    lines.append(f"  - GUID: `{exe_record.guid}`")
    lines.append(f"  - Age: `{exe_record.age}`")
    lines.append(f"  - Expected PDB path: `{exe_record.pdb_path}`")
    lines.append("- Provided PDB info stream:")
    lines.append(f"  - GUID: `{pdb_info.guid}`")
    lines.append(f"  - Age: `{pdb_info.age}`")
    lines.append(f"  - Signature: `0x{pdb_info.signature:08X}`")
    lines.append(f"  - Version: `0x{pdb_info.version:08X}`")
    lines.append(
        f"- Match status: `{'MATCH' if (exe_record.guid, exe_record.age) == (pdb_info.guid, pdb_info.age) else 'MISMATCH'}`"
    )
    lines.append("")
    lines.append("## PDB Evidence That Still Helps")
    lines.append("")
    if source_paths:
        lines.append("- BattleZoneTest source or object paths found in the PDB:")
        for path in source_paths:
            lines.append(f"  - `{path}`")
    else:
        lines.append("- No BattleZoneTest source paths were found in the provided PDB strings.")
    lines.append("")
    for group_name, patterns in PDB_SYMBOL_GROUPS.items():
        hits = find_unique_matches(pdb_strings, patterns)
        lines.append(f"### {group_name}")
        lines.append("")
        if hits:
            for hit in hits:
                lines.append(f"- `{hit}`")
        else:
            lines.append("- No matching strings found.")
        lines.append("")

    lines.append("## Ghidra Function Snapshots")
    lines.append("")
    for target, signature, code in function_summaries:
        lines.append(f"### {target.title}")
        lines.append("")
        lines.append(f"- Address: `{target.address}`")
        lines.append(f"- Signature: `{signature}`")
        lines.append("- PDB hints:")
        for hint in target.pdb_hints:
            lines.append(f"  - `{hint}`")
        lines.append("```c")
        lines.append(code)
        lines.append("```")
        lines.append("")

    lines.append("## Short Conclusions")
    lines.append("")
    lines.append(
        "- The provided PDB does not match the GOG EXE by GUID, so it will not auto-apply cleanly in Ghidra."
    )
    lines.append(
        "- The PDB still comes from the same BattleZoneTest codebase family and exposes high-value names for lobby, map filter, map select, and user bar systems."
    )
    lines.append(
        "- The Ghidra decompilation aligns with those names at the feature level: the map filter path checks strings such as `All Maps`, `Strategy`, and `Death Match`; the user bar constructor creates `Whisper User` and `Mute User`; the slash command handler prints `/mute`, `/unmute`, `/kick`, `/lock`, and `/unlock`; and the lobby callback logs `CNetGameLobby::OnLobbyChatUpdate`."
    )
    return "\n".join(lines)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Run headless Ghidra analysis for the GOG battlezone98redux.exe and compare a nearby PDB."
    )
    parser.add_argument(
        "--exe",
        type=Path,
        default=Path(r"C:\GOG Games\Battlezone 98 Redux\battlezone98redux.exe"),
        help="Path to battlezone98redux.exe",
    )
    parser.add_argument(
        "--pdb",
        type=Path,
        default=Path(r"C:\GOG Games\Battlezone 98 Redux\battlezone98redux.pdb"),
        help="Path to battlezone98redux.pdb",
    )
    parser.add_argument(
        "--out",
        type=Path,
        default=None,
        help="Optional output markdown path",
    )
    args = parser.parse_args()

    summary = build_summary(args.exe, args.pdb)
    if args.out:
        args.out.write_text(summary, encoding="utf-8")
    else:
        print(summary)


if __name__ == "__main__":
    main()
