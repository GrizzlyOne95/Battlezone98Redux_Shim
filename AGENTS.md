# BZR-OpenShim

This repo is part of the shared Battlezone workspace described in `C:\Users\iestu\Documents\GIT\BZR-Workspace\AGENTS.md`.

## Local Role
- Native shim, patching, and reverse-engineering repo.
- Owns `winmm.dll`, patch trampolines, and native save or loader investigations.

## Cross-Repo Pointers
- Addon-side consumers and Lua integration points live in `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\addon\campaignReimagined`.
- Subtitle integration work may involve `C:\Users\iestu\Documents\GIT\BZR-Subtitles`.
- Rendering-adjacent work may involve `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\addon\shadersEnhanced` or `C:\Users\iestu\Documents\GIT\ogre-1.10.0`.

Open the shared workspace file `C:\Users\iestu\Documents\GIT\BZR-Workspace\Battlezone98.code-workspace` when a task may span repos.
