# Workstation Setup Template — BZR OpenShim

This tracked document describes the **shape** of a useful local workstation note without committing machine-specific paths, usernames, temporary directories, or tool permission state.

For a real development machine, copy this file to `WORKSTATION.local.md` and fill in the local values. `WORKSTATION.local.md` is intentionally ignored by Git.

Repository documentation and checked-in build scripts remain authoritative for project behavior. A local workstation note is only a convenience for paths and commands that vary by machine.

---

## 1. Battlezone installs

Record the game roots you actually use:

```text
GOG game root:   <path-to-Battlezone-98-Redux>
Steam game root: <path-to-Battlezone-98-Redux>
Workshop root:   <path-to-steamapps/workshop/content/301650>
```

Useful local checks:

- confirm the target executable is Battlezone 98 Redux 2.2.301 before native patch testing;
- keep GOG and Steam paths separate when qualifying build-specific behavior;
- record where `openshim.ini`, `net.ini`, logs, and any deployed proxy DLLs live on the machine.

Do not commit a user-specific absolute path back into this template.

---

## 2. Repository locations

Record local checkout paths only in `WORKSTATION.local.md`:

```text
Battlezone98Redux_Shim:              <repo-path>
ExtraUtilities:                      <repo-path>
Battlezone98Redux_CampaignReimagined:<repo-path>
Other related repos:                 <repo-paths-as-needed>
```

Branch names are intentionally omitted from the tracked template because active development branches change frequently. Use `git status`, `git branch --show-current`, and the repository's open pull requests as the source of truth.

---

## 3. Build toolchain

Record the toolchain actually installed on the workstation, for example:

```text
Visual Studio / Build Tools: <edition-and-version>
MSBuild:                     <path-or-PATH-command>
VC toolset:                  <version>
CMake:                       <version/path-if-used>
PowerShell:                  <version>
Python:                      <version/path-if-needed>
```

Prefer repository build scripts and project files over hard-coded local command lines. If a local command needs an absolute executable path, keep it in `WORKSTATION.local.md`.

Typical Windows release build shape:

```powershell
& <MSBuild.exe> <path-to-BZROpenShim.sln> `
  /p:Configuration=Release /p:Platform=Win32 /m /v:m /nologo
```

---

## 4. Reverse-engineering tooling

Record locally installed tools and their versions only when they materially affect reproducibility:

```text
Ghidra:       <version/path>
llvm-pdbutil: <version/path>
llvm-objdump: <version/path>
Python RE packages: <versions>
Debugger:     <tool/version>
```

Before disassembling or creating a new corpus, search the checked-in material under `reverse_engineering/` and the intentionally tracked best-effort corpus under `reverse_engineering/repo_corpora/bzr_gog_best_effort/`.

Do not put temporary Claude/Codex scratch directories, private permission allowlists, or one-session dump paths in tracked repository documentation.

---

## 5. Deploy / smoke-test notes

Keep only machine-specific deployment details in the local copy. The supported end-user installation paths are documented in `README.md` and implemented by the scripts under `scripts/`.

For developer smoke tests, a local note may record:

```text
Primary test install: <GOG-or-Steam>
Secondary test install: <GOG-or-Steam>
Runtime log location: <local-path>
Crash dump location: <local-path>
Known local launch options: <if-any>
```

Always verify the current branch, executable build, and deployed DLL before attributing a runtime result to current source.
