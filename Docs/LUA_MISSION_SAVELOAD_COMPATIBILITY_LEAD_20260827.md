# Historical Lua Mission Save/Load Compatibility Lead

**Date:** 2026-08-27  
**Status:** OPEN - REPRO NEEDED / DO NOT ASSUME ENGINE BUG

## Source

Steam discussion, 2018-12-12:  
https://steamcommunity.com/app/301650/discussions/0/3216031607487056559/

The thread reports several custom Instant Action missions that launched normally but could crash after loading a save. A community reply stated that one of the later Redux patches had broken some older Lua-powered missions.

However, the same thread also demonstrates an important confounder: at least one mission under discussion had questionable/incomplete `Save()` / `Load(...)` implementation. Therefore this cannot be treated as a proven stock Redux regression from forum testimony alone.

This is distinct from the native `Inst4XMission` bug now fixed by OpenShim. That native mission-class crash is closed; this lead concerns **LuaMission save/load compatibility across Redux patch behavior and historical community scripts**.

## Why it is worth preserving

OpenShim/EXU now perform more save/load and mission-continuity work. A historical Lua ABI/serialization regression could be accidentally hidden by mission-specific fixes unless tested with known-good scripts.

The thread names examples including:

- Chinese Mission Pack Episode 1;
- Wreckers;
- a Tharsis Mons map from the Omega Squadron Instant Action pack.

Those names are leads only. Their historical Workshop revisions must be recovered before using them as evidence because current uploads may have changed.

## Required discrimination matrix

Use at least three Lua missions:

1. a minimal synthetic LuaMission with unquestionably correct `Save()` / `Load(...)` symmetry;
2. a known-good historical mission authored for an older Redux patch, recovered at a specific revision if possible;
3. one of the historically reported failing missions at the revision that produced the report.

For each mission test:

- fresh mission -> save -> load from in-mission UI;
- fresh mission -> save -> return to main menu -> load;
- load after player death/failure where UI path differs;
- multiple sequential saves/loads;
- handles to starting objects that no longer exist;
- nil values, booleans, numbers, strings, tables only where the stock Lua bridge supports them;
- PostLoad sequencing and handle refresh;
- Steam and GOG 2.2.301.

Trace/log:

- Lua `Save()` return arity/types;
- serialized mission payload size/type sequence if observable;
- `Load(...)` argument count/types;
- `PostLoad()` ordering;
- native object-pool/handle validity at restore;
- crash signature/module/RVA when a known-good script fails.

## Decision gate

- If the minimal known-good mission is stable and historical failures reduce to bad script state, classify the reports as mission bugs/documentation compatibility issues.
- If a historically valid Lua save contract works in an older Redux build/1.5-equivalent Lua environment but fails in 2.2.301 with the same script/state, locate the first native divergence and promote it to an OpenShim engine regression.
- Do not weaken Lua save validation or add broad exception swallowing merely to make malformed mission scripts appear to work.

## Acceptance if a native regression is proven

A corrected path must preserve stock Lua 5.1 semantics and existing supported mission `Save`/`Load` calling convention, restore known-good historical missions, and not change the already-fixed native `Inst4XMission` behavior.
