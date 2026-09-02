// GameObject - reconstructed layout, extending the prior 2026-08-31 findings.
//
// Source of truth: depot 301651 / manifest 730966170255625169
//                  Contents/MacOS/Battlezone 98 Redux (Steam)
//                  SHA-256 DAE80722CE6B253F1C7F1FD4807BDB379822EFC3735E7DB799D40E2470BA2C00
// Date: 2026-08-31
//
// This EXTENDS BZR_MACOS_X64_RECON_20260831.md section 7. All four previously
// proven serialization offsets are preserved unchanged. What is new in this pass
// is the inheritance structure, which reinterprets where those offsets live.
//
// THIS IS NOT A COMPILABLE ENGINE HEADER - see DistributedObject.hpp preamble.

#pragma once
#include <cstdint>

// ---------------------------------------------------------------------------
// Inheritance  [PROVEN]
// ---------------------------------------------------------------------------
//   class GameObject : public Attachable, public DistributedObject
//
// RTTI 0x10044FB00 is __vmi_class_type_info, base_count == 2:
//     base[0] Attachable         typeinfo 0x100452E18  offset 0x00  public
//     base[1] DistributedObject  typeinfo 0x100451AB0  offset 0x28  public
//
// Attachable RTTI 0x100452E18 is __class_type_info - it has no bases itself.
//
// Vtable group _ZTV10GameObject @ 0x10044F910:
//     primary   (offset-to-top  0x00) : 37 slots, GameObject's own virtuals
//     secondary (offset-to-top -0x28) : 21 slots, the DistributedObject subobject
//     the secondary block begins at _ZTV10GameObject+0x148, which is exactly the
//     value the constructor stores into this+0x28.                     [PROVEN]

class GameObject                      // sizeof >= 0x1E4                [PROVEN]
{                                     // (from the +0x1E0 dword serialized by Save)
    // -----------------------------------------------------------------------
    // Attachable subobject, offset 0x00, size 0x28                     [PROVEN]
    // GameObject::GameObject(_OBJ76*, GameObjectClass*) @ 0x10001BC80:
    //   [this+0x00] = _ZTV10Attachable+0x10   (then overwritten with
    //                 _ZTV10GameObject+0x10 after the base ctors run)
    //   [this+0x08] = 0
    //   [this+0x10] = 0
    //   [this+0x18] = 0      (three 8-byte stores)
    // 0x20 is not written by the ctor; the DistributedObject ctor is called on
    // this+0x28, which fixes Attachable's size at 0x28.
    // -----------------------------------------------------------------------
    void*    __vptr_Attachable;       // +0x000  primary vptr
    void*    m_attach08;              // +0x008 [PROVEN] nulled by ctor
    void*    m_attach10;              // +0x010 [PROVEN] nulled by ctor
    void*    m_attach18;              // +0x018 [PROVEN] nulled by ctor
    uint8_t  _pad_020[0x08];          // +0x020 8-byte tail. Not written by the
                                      //        ctor, but its EXISTENCE is
                                      //        corroborated by the ILP32/LP64
                                      //        cross-check below.        [HIGH]

    // ---- Independent cross-check against prior Windows RE ----------------
    // Earlier Windows x86 Redux work (recorded independently of this pass)
    // placed the DistributedObject subobject at GameObject+0x18.
    // Attachable here is: vptr + 3 pointer-width fields + an 8-byte tail.
    //     ILP32 (Win x86) : 4 * 4 + 8 = 0x18   <- matches the prior RE exactly
    //     LP64  (Mac x64) : 4 * 8 + 8 = 0x28   <- matches this pass exactly
    //     delta 0x10 == 4 pointer slots x 4 bytes of growth
    // Two separately derived results agree under pointer-width expansion, which
    // (a) corroborates the 0x28 base offset from a completely independent
    //     direction, and (b) is the reason the 8-byte tail is rated HIGH rather
    //     than left unrecovered - without it neither figure works.
    // ----------------------------------------------------------------------

    // -----------------------------------------------------------------------
    // DistributedObject subobject, offset 0x28                         [PROVEN]
    // See layouts/DistributedObject.hpp. Complete-object offsets of its proven
    // fields (subobject offset + 0x28):
    //     +0x030  m_flag08          (DO +0x008)
    //     +0x084  m_field5C         (DO +0x05C)
    //     +0x088  m_field60         (DO +0x060)
    //     +0x089  m_recycle         (DO +0x061)
    //     +0x08A  m_playerID  u16   (DO +0x062)
    //     +0x08C  m_id        u32   (DO +0x064)   <-- network object id
    //     +0x090  m_locality  u8    (DO +0x068)
    //     +0x094  m_field6C         (DO +0x06C)
    //     +0x098  m_dirty     u8    (DO +0x070)
    //     +0x09C  m_permStateInterval f32 (DO +0x074)
    //     +0x0A0  m_field78         (DO +0x078)
    //     +0x0BC  m_field94         (DO +0x094)
    //     +0x118  m_fieldF0         (DO +0x0F0)
    //     +0x1A4  m_field17C        (DO +0x17C)
    // -----------------------------------------------------------------------
    void*    __vptr_DistributedObject; // +0x028  secondary vptr [PROVEN]
    // ... DistributedObject body, extent >= 0x180 bytes ...

    // -----------------------------------------------------------------------
    // Fields written by GameObject's own constructor into the complete object
    // -----------------------------------------------------------------------
    // +0x0D0 = 0 (8-byte store)                                        [PROVEN]
    // +0x0F8 = 0 (8-byte store)                                        [PROVEN]
    // Both land inside the DistributedObject subobject range (DO +0xA8 and
    // DO +0xD0). A derived constructor initialising protected base members is
    // ordinary C++, so these do NOT bound the base class - they are recorded
    // here because they are the reason sizeof(DistributedObject) could not be
    // closed by constructor probing.

    // -----------------------------------------------------------------------
    // Serialization-proven offsets - PRESERVED from the prior pass
    // GameObject::Save(__sFILE*) @ 0x10001EE4A, matched to Windows by the
    // ordered field-name literals. Windows offsets from the earlier work.
    // -----------------------------------------------------------------------
    //   field            Win x86    Mac x86_64   wire width
    //   illumination     +0x0DC     +0x110       4
    //   perceivedTeam    +0x174     +0x1C8       4
    //   isVisible        +0x180     +0x1DC       4
    //   seen             +0x184     +0x1E0       4
    //
    // REINTERPRETATION [PROBABLE], new in this pass:
    // Mac +0x110 and +0x1C8 fall inside the DistributedObject subobject
    // (DO +0xE8 and DO +0x1A0). Since DistributedObject's own vtable carries
    // GetTeam/SetTeam/GetHealth/AddHealth/GetRank/GetRecycle/Explode/DamageAlloc,
    // DistributedObject in this engine is a full replicated-entity base rather
    // than a thin networking mixin, so replicated gameplay state living in it is
    // consistent. This does NOT change any proven offset - only which class the
    // field is attributed to. It is explicitly not proven and is the single most
    // valuable thing to settle next.
    //
    // The alternative reading, that sizeof(DistributedObject) is smaller and the
    // +0x17C access is something this pass mis-attributed, is not supported:
    // rbx is loaded from rdi at entry to SetLocal and is never reassigned before
    // the +0x17C read.
};

// ---------------------------------------------------------------------------
// Handle system - PRESERVED from the prior pass, unchanged
// ---------------------------------------------------------------------------
// GameObject::InitHandles() @ 0x10001BB70 - 4096 slots, 0x600-byte arena stride
//   (an allocation-slot stride, NOT asserted to be sizeof(GameObject)).
// GameObject::GetObj(int) @ 0x10001BC48 - upper 12 bits = slot index, lower 20
//   bits = generation, compared against the slot's +0x1A0 field before a 64-bit
//   pointer is returned.
//
// The Lua-visible handle therefore remains a 32-bit opaque identifier in the
// 64-bit build. It is not an object address. Any Win64 reconstruction should
// preserve this contract verbatim.
//
// Statics:
//   GameObject::userObject @ 0x102DF16F0   GameObject* - the local player's
//     object. UpdatePermState upcasts it with an explicit null-checked
//     `lea rcx,[rax+0x28]` to compare against a DistributedObject*.     [PROVEN]
