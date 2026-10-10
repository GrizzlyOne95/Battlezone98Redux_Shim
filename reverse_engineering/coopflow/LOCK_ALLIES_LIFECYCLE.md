# LockAllies lifetime in Redux multiplayer

Reviewed 2026-10-07 while continuing [HANDOFF_TEXT_ENTRY.md](HANDOFF_TEXT_ENTRY.md).

## Finding

The released GOG 2.2.301 executable resets the ally-prompt lock when it
initializes multiplayer text entry. A later multiplayer game therefore has
an engine startup path that clears the prior game's lock. CR does not need
an added mission-result unlock to address that carryover concern on this
examined build.

This is a **static lifecycle finding**, checked against released executable
bytes, not a live test of quitting CR and starting a stock match in the same
process. Steam, Wine and Proton were not tested here.

## Released-build evidence

Executable: `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.exe`.
SHA-256: `8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
PE32 x86, preferred image base `0x00400000`; addresses below are preferred
image VAs. No private PDB was used.

The existing Ghidra corpus was searched for references to `0x0260D5EC` and
calls to `0x0046CC80`. Python `pefile` and Capstone independently decoded the
installed executable at the initializer, setter, getter and both callers.

| VA | Observed operation |
|---|---|
| `0x0046CE16` | The setter at `0x0046CE10` writes its argument to the 32-bit gate at `0x0260D5EC`. |
| `0x0046CD20` | The ally/unally opener tests that gate; a nonzero value prevents opening. See [TEXT_ENTRY_STATE.md](TEXT_ENTRY_STATE.md). |
| `0x0046CCDE` | The initializer at `0x0046CC80` publishes the newly created ally editor node at `0x0260D184`. |
| `0x0046CCED` | The same initializer explicitly writes **zero** to `0x0260D5EC`, immediately after creating the prompt. Instruction bytes: `C7 05 EC D5 60 02 00 00 00 00`. |
| `0x005723A0` | The network allocation entry at `0x00572380` allocates a fresh `0x870`-byte object and calls the constructor at `0x0056FD20`. |
| `0x00570170` | Network startup at `0x0056FD20` calls that initializer, directly after chat initialization at `0x0057016B`. Its surrounding code reports `Net: Clearing user ID information (game starting)` and initializes the network game. |
| `0x00681E2A` | A second UI rebuild path at `0x00681DF0` also calls the initializer. Under its network/mode conditions it tears down chat and ally entry, recreates chat, then recreates ally entry and clears the lock. This is a conditional path, not a claim that every UI transition unlocks. |

Thus the lock is a per-client global that can stay set until multiplayer
entry initialization runs again. It is not an indefinitely retained policy
for subsequent games. The reset also supports the documented observation
that setting `LockAllies` during `Start()` can be overwritten by startup.

## CR behavior and existing validation

`Campaign-Reimagined/Scripts/CRCoop.lua` applies `LockAllies(true)` from
`CRCoop.Update`, every five seconds on each network client with a usable
local player handle. Keep that timing: an early lock can be reset by the
engine. The gate controls the player's ally/unally prompt, not scripted
`Ally`/`UnAlly` calls.

The existing `coop-text-entry` run at
`C:\BZRCoop\runs\cr-misn03-coop-text-entry-20261007-150741` was reviewed:
**7/7 steps passed**, and both clients passed script-error and probe-health
checks. In that run Y/U were blocked under CR's lock, the co-op alliance
remained intact, and an explicit guest `LockAllies(false)` allowed Y to
open the prompt. Chat capture and J/X suppression also passed.

An unlock in a mission-result wrapper would also need to disable CR's
periodic relock. It would not cover an arbitrary mid-mission quit, and
misn03 captures native result functions before PersistentConfig installs
its global wrappers. No such cleanup was added: the verified native
initialization reset addresses next-game startup without new CR hooks.

## Optional live carryover check

For direct runtime evidence beyond the static finding, keep both test-client
PIDs unchanged, quit a CR match while locked, and launch an ordinary stock
multiplayer match. Verify Y and U can open their prompt, then cancel with
Escape. Do not manually unlock or run CRCoop in the stock match; either
would mask carryover. Record the gate and node state before quitting and
after new-game initialization if using a read-only memory probe.

Use only the serialized harness clients under `C:\BZRCoop\instances`,
windowed, with graceful `Stop-BZRGame -Id ... -NoForce` teardown. A fresh
process is not a same-process carryover test. This optional live transition
was not performed in this continuation.
