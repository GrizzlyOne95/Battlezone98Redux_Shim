# Battlezone 98 Redux Patch Extraction Results

This document lists the exact memory patches identified by comparing the memory dumps:
- **Unpatched**: `battlezone98redux-nopatch.DMP`
- **Patched**: `battlezone98redux.DMP` (with `_bzcp.dll` shim)

## Environment Data
- **Process**: `Battlezone98Redux.exe` (v2.2.301 GOG)
- **Base Address**: `0x00400000`
- **Shim DLL**: `_bzcp.dll`
- **Shim Load Address (in dump)**: `0x63D10000`

## Key Patches Identified

| Feature | BZR.exe Address | Original Bytes | Patched Bytes | Target (RVA) |
| :--- | :--- | :--- | :--- | :--- |
| **Hop-Fix 1/3** | `0x0079B85F` | `8B 45 FC 8B 88` | `E9 AC 14 58 63` | `_bzcp.dll + 0xCD10` |
| **Hop-Fix 2/3** | `0x00799279` | `6A 00 8B 85 5C` | `E9 C2 3A 58 63` | `_bzcp.dll + 0xCD40` |
| **Hop-Fix 3/3** | `0x00799377` | `FF D2 68 30 09` | `E9 E4 39 58 63` | `_bzcp.dll + 0xCD60` |
| **Vehicle Mod Fix**| `0x007AA5A1` | `75` | `EB` | (Inline) |
| **Map Sorting?** | `0x007680D6` | `89 4D F8 0B B6` | `E9 05 21 5B 63` | `_bzcp.dll + 0xA1E0` |

## Full Patch Table

| Address | Target | Original | Patched |
| :--- | :--- | :--- | :--- |
| `0x00618C2F` | `N/A` | `E4 84 87 00` | `D0 44 D3 63` |
| `0x0062480B` | `0x63D1D770` | `68 3C D5 88 00` | `E9 60 8F 6F 63` |
| `0x00664866` | `N/A` | `EB FE FF FF` | `E6 A0 6B 63` |
| `0x0073E71C` | `0x63D1D850` | `C6 45 FC 07 8D` | `E9 2F F1 5D 63` |
| `0x0073F430` | `0x63D1DD80` | `E8 2B 31 00 00` | `E9 4B E9 5D 63` |
| `0x00743C05` | `0x63D1D7B0` | `8D 85 00 FF FF` | `E9 A6 9B 5D 63` |
| `0x00752A82` | `N/A` | `E8` | `E9` |
| `0x00752A84` | `N/A` | `04 00 00` | `9F 5C 63` |
| `0x00766C4A` | `0x63D1D460` | `E8 A1 AE D1 FF` | `E9 11 68 5B 63` |
| `0x007680D6` | `0x63D1A1E0` | `89 4D F8 0F B6` | `E9 05 21 5B 63` |
| `0x0078DD4E` | `N/A` | `E4 84 87 00` | `D0 44 D3 63` |
| `0x00798BD9` | `0x63D1D440` | `51 E8 A1 BB FC` | `E9 62 48 58 63` |
| `0x00798EAC` | `N/A` | `BC 2A 8A 00` | `D0 A1 D3 63` |
| `0x00799116` | `0x63D1C9F0` | `52 6A 20 6A 00` | `E9 D5 38 58 63` |
| `0x0079920A` | `N/A` | `92 23 03 00` | `C2 38 58 63` |
| `0x00799279` | `0x63D1CD40` | `6A 00 8B 85 5C` | `E9 C2 3A 58 63` |
| `0x00799377` | `0x63D1CD60` | `FF D2 68 30 09` | `E9 E4 39 58 63` |
| `0x00799774` | `0x63D1CE20` | `89 4D FC 8B 45` | `E9 A7 36 58 63` |
| `0x007997A9` | `0x63D1CA80` | `8B 45 F8 8B 88` | `E9 D2 32 58 63` |
| `0x007998AB` | `0x63D1CA60` | `8B 45 BC 8B 88` | `E9 B0 31 58 63` |
| `0x0079A4F4` | `N/A` | `68 99 00 00` | `38 2E 58 63` |
| `0x0079B85F` | `0x63D1CD10` | `8B 45 FC 8B 88` | `E9 AC 14 58 63` |
| `0x0079D691` | `0x63D1A060` | `8B EC 8B 0D 64` | `E9 CA C9 57 63` |
| `0x0079D6B1` | `0x63D1A040` | `8B EC 8B 0D 64` | `E9 8A C9 57 63` |
| `0x007A18F8` | `0x63D1EAF0` | `8D 8D E4 FE FF` | `E9 F3 D1 57 63` |
| `0x007A1FAD` | `0x63D1E5A0` | `E8 2E 08 FB FF` | `E9 EE C5 57 63` |
| `0x007A311E` | `0x63D1D090` | `8B 0D 74 55 94` | `E9 6D 9F 57 63` |
| `0x007A313E` | `0x63D1D090` | `8B 0D 74 55 94` | `E9 4D 9F 57 63` |
| `0x007A31D9` | `0x63D1BF50` | `68 E0 B3 89 00` | `E9 72 8D 57 63` |
| `0x007A39DF` | `0x63D1E9C0` | `8B 48 2C 51 6A` | `E9 DC AF 57 63` |
| `0x007A3D63` | `0x63D1D0B0` | `8B 4D F8 E8 F5` | `E9 48 93 57 63` |
| `0x007A42F5` | `0x63D1E560` | `8A 40 38 0F B6` | `E9 66 A2 57 63` |
| `0x007A4440` | `0x63D1CEF0` | `83 C0 20 8B C8` | `E9 AB 8A 57 63` |
| `0x007A6913` | `0x63D1E360` | `C7 45 FC FF FF` | `E9 48 7A 57 63` |
| `0x007AA5A1` | `N/A` | `75` | `EB` |
| `0x007D0A2F` | `0x63D1E110` | `0F B6 45 20 85` | `E9 DC D6 54 63` |

## Summary
The extraction confirms that the shim applies complex logic by redirecting many core UI and game functions to `_bzcp.dll`. The **Hop-Fix** specifically targets addresses in the `0x00799xxx` and `0x0079Bxxx` range, which correlates with the map list rebuilding logic.
