# Clean PDB Ghidra C Export

This folder packages the best available Ghidra decompilation for `bzone.exe` with `bzint.pdb` applied.

- Function records: 15070
- Decompiled C-like functions: 15045
- Remaining failed decompilations: 25
- Supplemented functions recovered from earlier run: 1

Files:

- `all_decompiled.c`: merged C-like decompiler output.
- `functions/`: one `.c` file per decompiled function, sharded by address prefix.
- `function_index.tsv`: full function index and status.
- `decompile_failures.tsv`: functions still not represented as C.
- `failed_asm/`: assembly fallbacks for the remaining failed decompilations.
- `manifest.json`: machine-readable package summary.

Notes:

- This is reference-grade Ghidra output, not directly buildable original source.
- The remaining failures are Ghidra decompiler timeouts, mostly large software rasterizer/terrain polygon routines.
- `Show_Light_Source` was skipped in the complete run but recovered from the earlier PDB run.
