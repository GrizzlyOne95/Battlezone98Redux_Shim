# Steam vs GOG - Analysis

## Result: Same code, Steam just encrypts it on disk

The Steam and GOG executables contain **identical game code** at the same virtual addresses.
The Steam build adds SteamStub DRM which encrypts the .text section on disk and decrypts it
into memory at launch.

| Property | GOG | Steam |
|----------|-----|-------|
| .text VA | 0x00401000 | 0x00401000 (identical) |
| .text size | 0x0046737B | 0x0046737B (identical) |
| .text entropy | 6.266 (normal code) | 8.000 (encrypted) |
| Entry point | 0x0083EE5E (in .text) | 0x02D0F310 (in .bind DRM stub) |
| Extra section | none | .bind (SteamStub DRM) |
| PUSH 0x930 on disk | 112 hits | 0 hits (code is encrypted) |

## Implication for patching

Once the Steam game launches, SteamStub decrypts .text and the game code is live at the
same virtual addresses as GOG. Patch addresses extracted from GOG are valid for Steam.

OpenShim accounts for the timing by waiting on a 256-byte signature block at
`0x00868300` (`DEFAULT_BZR_SIGNATURE_ADDR`) before it writes anything — see
`WaitForSignature` in `src/engine/patcher.cpp`. On Steam those bytes only match once
SteamStub has decrypted `.text`, so the wait doubles as a "game code is live" gate.

Related: `ResolveCallTargetWithFallback` in the same file exists because Steam decrypts
`.text` lazily, so a single read of a call opcode can come back as ciphertext and resolve
to null permanently. It retries, then falls back to the address for the version-gated
build.

## Deriving patch addresses

Work from the GOG executable. It is unencrypted on disk, so static analysis and byte
guards behave normally, and every address recovered there applies unchanged to Steam
once the process is running. Do not read patch addresses out of a Steam memory dump —
they are only valid for the session that produced them.
