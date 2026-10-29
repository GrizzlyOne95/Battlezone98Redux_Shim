# Released-image identity qualification for Direct LAN

Evidence class: static image/assembly plus existing Ghidra output. No native
hook or gameplay validation. Baseline: Battlezone 98 Redux **2.2.301 GOG**,
`battlezone98redux.exe`, SHA256
`8d71f56c1314e69a8ad38f4eeaf20a8ff825965a84cf196e5f77ea4cc3377413`.
Private evidence path:
`Battlezone_Source/BZ1/Redux/openshim_re_corpus/bzr_gog_best_effort/ghidrecomp/results/bins/battlezone98redux.exe-6777ca/decomps/`.
Function files there use `FUN_<lowercase-address>-<lowercase-address>.c`.
Ghidra project `/battlezone98redux.exe-007c64` corroborates the decompilation.
The public repository contains this hand-authored analysis and a reproduction
script, never decompiler bodies or private/PDB-derived artifacts.

## Proven observations

| Function / VA | Released-image observation |
|---|---|
| `FUN_0073A6E0` / `0x0073A6E0` | Stores discriminator 1 at offset 0 and two words at offsets 8/12. |
| `FUN_0073A710` / `0x0073A710` | Stores discriminator 2 at offset 0 and two words at offsets 8/12. |
| `FUN_0073A740` / `0x0073A740` | Copies offsets 0, 8 and 12. This does not qualify offset 4 or establish a complete public C++ layout. |
| `FUN_0073A900` / `0x0073A900` | Reads the object through ECX. Zero combined words at 8/12 yield AL=0. Nonzero values with discriminator 2 or 3 yield AL=1. Discriminator 1 constructs a temporary through `0x0073A590` and calls `0x0073A5D0`. Other discriminators yield AL=0. |
| `FUN_0073AAB0` / `0x0073AAB0` | Formats different prefixes for discriminators 0..3; nonzero cases insert the words at 8/12 into the stream. |
| `FUN_0073ABD0` / `0x0073ABD0` | Parses prefixes I/S/G/B into discriminators 0/1/2/3 respectively, then a 64-bit value. On an accepted parse, writes the destination from saved ECX at offsets 0/8/12. The stream is the stack argument; `ret 4` returns the stream pointer. |
| `FUN_0073A970` / `0x0073A970` | For discriminator 1, initializes the stack-supplied destination through `0x0073A590`; otherwise uses `0x0073A530`. Returns that destination in EAX, `ret 4`. |
| `FUN_0073A9B0` / `0x0073A9B0` | For discriminator 2, initializes the stack-supplied destination through `0x006C9A90`; otherwise uses `0x006A9140`. Returns that destination in EAX, `ret 4`. |
| `FUN_0074B670` / `0x0074B670`, lobby vtable `+0x38` | Copies the global at `0x0260B1C8` into the stack-supplied destination by passing it in ECX to `0x0073A740`; returns the destination, `ret 4`. |

All rows are **PROVEN for this image** at the byte/register/data-operation
level. The inventory's inferred signatures remain unqualified. In particular,
`0x0073A900` does not define a whole EAX boolean: its leaf paths set only AL.
Treating Ghidra's inferred `int` return as a meaningful 32-bit value is unsafe.

**STRONG INFERENCE:** the offset-0 discriminator and 8/12 value form a tagged
native network identity. The destination-return routines at `0x0074B670`,
`0x0073A970` and `0x0073A9B0` use hidden struct-return destinations or equivalent
explicit-output conventions. Stack cleanup and register facts are proven;
source-level C++ declarations need caller qualification before an adapter
implements them.

**UNKNOWN:** whether discriminator 3 is suitable for a session-local identity
through every engine consumer, how it is serialized in each gameplay path,
which callbacks retain copies, and whether any consumer converts it through a
platform-specific accessor. Its validity predicate alone proves none of those
contracts. Prefix letters must not be promoted into invented object roles.

## Consequence for implementation

The OpenShim control protocol keeps its own opaque 128-bit IDs. Do not cast
them to this native structure, truncate them into Steam/Galaxy identities, or
write a provider global to make readiness return true. A native mapping must
be explicit, lifetime-bound to the session and qualified at every consumer.

The earliest useful adapter qualification is the local-ID return plus its
copy/equality/serialization callers, then host identity, membership callbacks
and peer endpoint publication. Record ECX/EDX, each stack argument, hidden
returns, destructor flags and allocator ownership for every replaced method.
The existing 32-pointer lobby and four-pointer P2P inventories are bounds for
investigation, not complete replacement declarations. Provider construction
and teardown also register backend pointers away from the main accessor;
see [DIRECT_LAN_BACKEND.md](DIRECT_LAN_BACKEND.md).

Reproduce with `reverse_engineering/inspect_direct_lan_backend.py --exe
<exact-baseline-exe> --corpus <private-corpus>`. It verifies the executable
hash and now records 36 vtable entries, 20 boundary functions, assembly and
unqualified corpus hints in ignored `reverse_engineering/workshop/` output.
No runtime native hook should be added from this static inventory alone.
