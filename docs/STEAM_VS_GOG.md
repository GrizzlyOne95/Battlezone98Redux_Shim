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

The original Community Patch (_bzcp.dll) was designed to work with Steam — it polls
address 0x00868300 waiting for the code to be decrypted, then applies patches. The
signature at that address in the decrypted Steam process will match the GOG on-disk bytes.

## Why extraction failed previously

The x64dbg scripts in the old guide used incorrect syntax and never actually ran.
The addresses from the memory dump were from a specific session and are not reliable
as hardcoded values.

The correct extraction method is PatchLogger (see tools/EXTRACTION_GUIDE.md).
Run it against GOG — the captured addresses apply equally to Steam.
