# Ogre 1.10.0 reference integration

OpenShim uses a pinned upstream Ogre 1.10.0 source snapshot as a **compile-time reference** for renderer diagnostics and future Ogre hooks.

Run from the repository root:

```powershell
.\setup-dev.ps1
```

The script performs a sparse checkout into:

```text
third_party\ogre-1.10.0-bzr\_work
```

Only the OgreMain and Overlay header trees are fetched.

## Runtime policy

OpenShim does **not** compile, bundle, or load a replacement `OgreMain.dll`.

Battlezone 98 Redux already owns the live Ogre runtime. OpenShim accesses that existing module through:

- `GetModuleHandle("OgreMain.dll")`
- validated exported functions where appropriate
- validated module-relative offsets / signatures for internal functions
- narrowly scoped hooks

This avoids introducing a second Ogre runtime, duplicate singletons, allocator ownership problems, or conflicting resource managers.

## ABI warning

The shipped BZR Ogre DLL is not ABI-identical to pristine upstream Ogre 1.10.0. ExtraUtilities' prior comparison work found allocator/configuration drift and several exported signature differences.

Therefore:

- upstream headers are useful for names, concepts, and many stable declarations;
- do not assume a class layout or decorated signature is safe merely because it exists upstream;
- runtime-facing work must continue to validate the shipped BZR module;
- never replace only one shipped Ogre DLL with a locally rebuilt upstream DLL.

`OgreBuildSettings.h` in this directory mirrors the known-good ExtraUtilities compile-time header configuration. It is not a claim of binary compatibility.
