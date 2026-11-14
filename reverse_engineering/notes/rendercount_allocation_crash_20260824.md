# renderCount Invalid Allocation - Code-Level Trace

Date: 2026-08-24
Build: GOG `battlezone98redux.exe` 2.2.301. Static proof below was re-derived
from the shipped image (disassembly of the constructor); the fix itself ships
on this branch's baseline and its install is re-validated at every startup.

## Reproduction shape

The defect needs an ODF with a `[Render]` section selecting
`renderBase = "draw_multi"` and a count that is missing, non-numeric, or
extreme. Campaign Reimagined content uses this renderer constantly
(`bullets.odf`, `shell.odf`, `blasth.odf`, ... all ship
`renderCount = 2`), so malformed custom ordnance/effects hit the same path as
stock objects.

## Native function

`MultiRenderClass` constructor `0x0044D7B0`. Disassembly around the
allocation (comments added):

```
0x0044D847  push 0x8C8E76EC        ; FNV-1a("rendercount"), literal
0x0044D84C  push [ebp-0x60]       ; default value for missing key
0x0044D853  call 0x5896C0         ; ParameterDB::Get -> this+0x108
0x0044D858  xor ecx, ecx          ; <-- clamp site begins (11 bytes)
0x0044D85A  mov edx,[ebp-0x54]    ; this
0x0044D85D  mov eax,[edx+0x108]   ; eax = renderCount
0x0044D863  mov edx, 4            ; <-- resume address
0x0044D868  mul edx               ; edx:eax = count*4
0x0044D86A  seto cl               ; overflow flag -> cl
0x0044D86D  neg ecx               ; 0 or -1
0x0044D86F  or  ecx, eax          ; overflow -> 0xFFFFFFFF else count*4
0x0044D871  push ecx              ; allocation size
0x0044D872  call 0x83D92C         ; operator new[]
0x0044D883  mov [eax+0x104], ecx  ; store saturated size on this
```

Failure modes in stock code:

- key absent / non-numeric text: ParameterDB leaves the zero default ->
  `new[](0)`-sized entry arrays and a zero-trip copy loop are benign, but any
  negative parse result flows straight through;
- negative textual count: `mul` sets OF only for signed overflow, so e.g.
  `0xFFFFFFFF * 4` saturates to `0xFFFFFFFF` via `seto/neg/or` and requests a
  4 GiB allocation - CRT aborts with "invalid allocation size";
- large positive count (`>= 0x40000000`): same saturation path;
- moderately huge counts request enormous but valid sizes and die inside the
  allocator instead.

Either way the process dies while constructing one render object. The
`renderName%d` copy loop immediately afterwards iterates to `[this+0x108]`,
so the same unclamped value also bounds the name fetches.

## Patch (already shipped on this branch)

11-byte mid-function detour at `0x0044D858` (resume `0x0044D863`),
`src/patches/bzr_hooks.cpp`:

- expected bytes validated before install:
  `33 C9 8B 55 AC 8B 82 08 01 00 00`
  (`xor ecx,ecx; mov edx,[ebp-0x54]; mov eax,[edx+0x108]`);
- naked hook clamps `eax` into `[0, kMultiRenderCountMax = 256]`, stores the
  clamped value back to `[edx+0x108]` so the copy loop sees the same bound,
  restores `ecx = 0` for the stock `seto/neg` chain, and jumps to resume;
- `kMultiRenderCountMax = 256` is not an arbitrary gameplay limit: it only
  caps the render-entry array of `draw_multi` renderers, where stock content
  uses 2; legitimate values are unaffected byte-for-byte;
- bounded `[RENDERCOUNT]` log line identifies every clamp that fires;
  opt-out `OPENSHIM_DISABLE_RENDERCOUNT_CLAMP` /
  `BZR_DISABLE_RENDERCOUNT_CLAMP`.

Startup evidence from this workstream:
`[RENDERCOUNT] Installed draw_multi renderCount clamp site=0x0044D858
resume=0x0044D863 max=256`, and no clamp lines during ordinary gameplay
(including CR content whose tracers/shells exercise `draw_multi`
continuously).

## Remaining uncertainty

None material. The one deliberate choice is the 256 cap; if a future asset
legitimately needs more entries the constant is a single #define.
