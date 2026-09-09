# BzE installer recovery and decompilation

## Result

The archived BzE installers were recovered under:

`C:\Users\iestu\Documents\GIT\BZ1\_Source\BzE`

The installer executables are MindVision Installer VISE archives. The VISE
wrapper is not the game-code protector. The installed game executables use:

- BzE 1.11 and BzE 1.3 RC4: NeoLite 1.01
- BzE 1.3.4 and BzE 1.3.9.1: ASProtect 1.23-2.56 / NTkrnl Protector signature

No system-clock change was made. The protected programs restore their game
sections before showing the expired-build dialog. ASProtect also detects an
attached CDB debugger, so the reliable method is a normal windowed launch,
followed by a PE-sieve realigned image dump with import recovery.

## Artifact layout

- `installers\`: one copy of each unique VISE installer
- `extracted\`: complete base payloads and separate base-plus-expansion trees
- `decomp\`: unpacked PE images, per-function Ghidra C output, strings,
  inventories, logs, and Ghidra projects
- `diffs\`: Ghidriff Markdown reports plus complete JSON match/diff data
- `analysis\*-expansion-delta.csv`: SHA-256 file deltas for both expansions

The `corpus\inventory\functions.csv` files are the quickest machine-readable
function index. Each `corpus\ghidrecomp\...\decomps` directory contains one
C-like file per discovered function.

## Ghidriff summary

| Lane | Added | Deleted | Matched with code changes | Overall function match |
|---|---:|---:|---:|---:|
| DX5 1.11 -> 1.3 RC4 | 75 | 70 | 219 | 98.80% |
| DX5 1.3 RC4 -> 1.3.4 | 506 | 1,353 | 507 | 82.64% |
| DX9 1.3 RC4 -> 1.3.4 | 647 | 226 | 377 | 89.19% |
| DX5 1.3.4 -> 1.3.9.1 | 263 | 83 | 205 | 96.36% |
| DX9 1.3.4 -> 1.3.9.1 | 224 | 121 | 312 | 95.99% |

These are automatic correlator statistics rather than claims about source
history. Use the full JSON output to inspect omitted Markdown sections and the
matching evidence for an individual function.

## Recovered executable corpus

| Build | Renderer | Ghidra functions | Unpacked SHA-256 |
|---|---:|---:|---|
| 1.11 | DirectX 5 | 5,651 | `EE4745F9EF7DB27947929D3CDBC43A253A27552E8F658CF68B7AE2BB3CBF4DA9` |
| 1.3 RC4 | DirectX 5 | 5,751 | `92FE0359F10B0134C23A3286860C79E0C72EEFC8D82AB05004E9E034DF98A8BB` |
| 1.3 RC4 | DirectX 9 | 3,528 | `D89751CF803F331769EA8F7C7960F8BC09C74DEC6AEC681FB0D2AC222C40DCD5` |
| 1.3.4 | DirectX 5 | 4,318 | `A91022DBB90ED39B002B5E8B61DCEF1A5A0ED2CCF6A5E6FD006614A0F4F538B5` |
| 1.3.4 | DirectX 9 | 3,922 | `0BC634D5AA3DD59689BDCAF99232C650E68E4FE2B5701D9D241C83A462766B77` |
| 1.3.9.1 | DirectX 5 | 4,557 | `9CF571CF3D79D5DB83569C97D5A0D80A79A40BBAEA0162523E05CEFB88B24E03` |
| 1.3.9.1 | DirectX 9 | 4,067 | `F6E8345A05E12D47C5E5431D2766A1D004317C685B22D39F2221B678DD584A59` |

Function totals vary with compiler, protection, recovered control flow, and
Ghidra analysis. They are not source-level function counts.

## Expansion deltas

- 1.11 expansion: 184 files added, 6 changed, 0 removed
- 1.3.9 expansion: 8 files added, 5 changed, 0 removed

The expansion installers do not replace either main game executable. Their
changed files are primarily ZIX archives, `NETMIS.TXT`, and setup logs.

## Reusable tools

- `unpack_bze_game.ps1` launches a protected BzE executable, snapshots the
  restored PE through PE-sieve, and shuts it down through `BZRHarness.ps1`.
- `compare_bze_payloads.ps1` emits a hash-backed CSV delta between two payload
  trees.
- `rebuild_pe_from_memory.py` realigns a raw module-sized memory image when a
  debugger capture is appropriate. It does not repair imports or infer an OEP.

## Patch-research cautions

Ghidriff matches and decompiler names are leads, not identity proof. Validate a
candidate with independent call-site, xref, string, or behavioral evidence
before creating an OpenShim signature. Complex functions occasionally timed
out during decompiler correlation, and Markdown reports cap displayed
functions; the corresponding JSON reports contain the full result set.

For OpenShim work, record the independent identity evidence in
`scripts/patches.json`, prefer named `resolves` entries over feature-local
byte arrays, and confirm the runtime `[RESOLVE]` agreement log.

## Format references

- Installer VISE user guide:
  https://studylib.net/doc/18262917/installer-vise-user-s-guide
- Observer's incomplete VISE parser:
  https://github.com/lazyhamster/Observer/tree/master-gh/src/modules/vise
- NeoLite unpacking background:
  https://gbppr.ddns.net/cracking/RCEArchive/t-5155.html
