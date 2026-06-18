Need to investigate https://github.com/mentebinaria/retoolkit and ways it can be implemented.

Recommended Additions by Use Case
Signature Generation & Binary Diffing
iced-x86 (pip install iced-x86) — the single highest-value add for your DLL patching workflow. Far faster than capstone for encoding, has full x86 instruction length decoding, and can re-encode instructions with relocated operands. This is exactly what you need when extracting prologue bytes for your ScanPattern table — you can walk instructions and automatically wildcard the bytes that are absolute addresses vs. the opcode skeleton bytes that are stable.
BinDiff (Ghidra plugin, free from Google) — complements the Version Tracking approach. Gives you a visual confidence-scored diff of every function between 1.5 and Redux in one pass. Install the Ghidra plugin from zynamics.com/bindiff.html. Outputs a SQLite DB you can query programmatically.
Diaphora (pip install diaphora or clone from GitHub) — similar to BinDiff but IDA-native, though it also has a standalone mode. Produces a scored match CSV that's easy to feed into your corpus pipeline. Worth having alongside BinDiff since the two sometimes disagree on fuzzy matches.
PE Analysis
lief (pip install lief) — the best Python PE manipulation library. Unlike pefile it can write modified PEs (inject sections, patch the import table, add debug directory entries). Directly useful for testing patches against the static binary before burning them into the DLL, and for extracting the Redux EXE's debug GUID/age to understand exactly what PDB build it expects.
pdbparse (pip install pdbparse) — reads Microsoft PDB files from Python without needing WinDbg or Ghidra. Can extract the public symbol table, type info, and importantly the GUID/age. Useful for programmatically diffing the 1.5 PDB symbol list against the Redux beta PDB to find functions that appear in one but not the other.
Function Identification (filling in the unknowns)
CAPA (pip install flare-capa) — FLARE's capability matcher. Runs against a PE and classifies functions by what they do (file I/O, network, crypto, etc.) using a YARA-like rule engine. Very useful for identifying functions in the Redux binary that have no PDB name — if you're looking for the map sort routine, CAPA can narrow it to "functions that sort collections" and cross-reference against your 1.5 corpus.
FLOSS (pip install flare-floss) — finds strings that are assembled at runtime (XOR-decoded, stack-built) rather than sitting in the .data section statically. The game has a lot of format strings and debug messages that Ghidra's string scan misses. These are anchor points for finding functions — a format string like "[ERROR] Map sort failed" is much more reliable than a byte pattern.
rizin (the rz CLI, install via winget install rizin.rizin) — lightweight CLI RE framework with scripting. Startup is instant vs Ghidra's JVM warmup, making it practical for scripted batch work. Its rz-ghidra plugin pipes Ghidra decompiler output through rizin, so you get Ghidra-quality decompilation from a fast CLI. Good for the cases where you just need to quickly confirm a function boundary or check a call site without opening the full Ghidra project.
Dynamic / Runtime Analysis
Frida tools (pip install frida-tools) — if the .js trace scripts aren't already using it, this is the obvious gap. Frida lets you hook and trace any function at runtime from Python/JS without recompiling the DLL. For finding the patch sites you don't have signatures for yet, a Frida script that logs every call to a suspected code region is much faster than static analysis iteration. The frida-trace CLI alone (frida-trace -n battlezone98redux.exe -i "MapSort*") is worth the install.
x64dbg (if not already present) with the SigMaker plugin — SigMaker automates the most tedious part of your current gap: select a function in x64dbg, right-click → SigMaker → outputs a \xAB\xCD\x00\x00 pattern with wildcards already placed on the operand bytes. This directly feeds your ScanPattern table. The PatternFinder plugin is also useful for validating that a generated pattern is unique before committing it.
PDB / Symbol Workflow
cvdump (from Microsoft's microsoft-pdb GitHub repo, build from source or grab a prebuilt) — dumps raw PDB contents including type records, global symbols, and the section contribution map. Useful for extracting the full type hierarchy from the Redux beta PDB even if the address mapping is garbage — you get the struct layouts and vtable orderings which are stable regardless of the GUID mismatch.
llvm-pdbutil (ships with LLVM/clang) — similar to cvdump but with better filtering. llvm-pdbutil dump --publics battlezone98redux.pdb gives you the 8078 public symbols cleanly, and --types gives you the type records. If you haven't already exported this as a reference file in your corpus, it's worth doing once so you have it as a lookup table.

Quick Priority Order
For your immediate patches.h address problem, the stack that gets you there fastest:

iced-x86 → auto-wildcard prologue bytes when building signature entries
x64dbg + SigMaker plugin → generate patterns interactively for each patch site
BinDiff Ghidra plugin → bulk 1.5→Redux function correlation in one pass
Frida tools → runtime validation that a scanned address is actually the right function before locking it in

The rest (CAPA, FLOSS, rizin, lief, pdbparse) are solid long-term additions for the broader corpus and analysis work but aren't blockers for the signature table specifically.