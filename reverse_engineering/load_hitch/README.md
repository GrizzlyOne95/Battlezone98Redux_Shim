# Load / first-use hitch probe

Used for `Docs/OGRE_LOAD_HITCH_MEASUREMENT_20261003.md`.

- `run_load_hitch_probe.ps1 -Renderer DX11|DX9 -Label <name> [-ColdShaderCache]`:
  deploys the `ncprobe` fixture into `addon\ISDF Chronicles`, launches with the
  native stack sampler, then restores every file it touched. It hashes the
  shim modules before and after and writes `<label>\DONE` when finished. Launch it
  through WMI (`Win32_Process.Create` running `pwsh -File ...`) so the game is
  outside the caller's job object, then wait for `DONE`.
- `pivot_probe.lua`: two of each target type; the first destruction is first
  use, the second is the warm control.
- `attribute_load_hitch.py <run>`: classifies main-thread samples per window
  (start → sim, shell parse, Modable unload → clear, clear → parsed, each
  destruction and the 1.5 s before it) and writes `<run>\attribution.json`.
- `inclusive.py <run> <window key> <regex>...`: inclusive ms of stack patterns
  within one window.
- `callers.py <run> <begin> <end> <leaf regex> <stack regex>`: the most common
  caller chains for matching samples (game frames keep their RVA).
