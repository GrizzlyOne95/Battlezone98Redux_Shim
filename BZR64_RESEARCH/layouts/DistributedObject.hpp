// DistributedObject - reconstructed layout, macOS x86_64 Battlezone 98 Redux 2.2.301
//
// Source of truth: depot 301651 / manifest 730966170255625169
//                  Contents/MacOS/Battlezone 98 Redux (Steam)
//                  SHA-256 DAE80722CE6B253F1C7F1FD4807BDB379822EFC3735E7DB799D40E2470BA2C00
// Date: 2026-08-31
//
// THIS IS NOT A COMPILABLE ENGINE HEADER. It is a documentation artifact recording
// evidence-qualified offsets. Unknown regions are represented as explicit padding
// so that the proven offsets land where the binary puts them. Do not treat the
// padding as evidence that those bytes are unused - they are simply unrecovered.
//
// Confidence legend:
//   [PROVEN]      direct load/store at that offset in a named function
//   [HIGH]        multiple independent consistent accesses, no contradicting evidence
//   [PROBABLE]    single consistent access or strong structural inference
//   [SPECULATIVE] inference only; recorded so it can be falsified
//
// ABI: Itanium C++ ABI, Clang, libc++ (std::__1), LP64. Offsets are NOT transferable
// to MSVC/Win64 verbatim - see BZR64_FEASIBILITY_20260831.md section on ABI.

#pragma once
#include <cstdint>

// ---------------------------------------------------------------------------
// Inheritance
// ---------------------------------------------------------------------------
// RTTI at 0x100451AB0 is __class_type_info (vptr + name only): DistributedObject
// has NO base classes.                                                  [PROVEN]
//
// GameObject RTTI at 0x10044FB00 is __vmi_class_type_info with base_count == 2:
//     base[0] = Attachable        offset 0x00  public non-virtual        [PROVEN]
//     base[1] = DistributedObject offset 0x28  public non-virtual        [PROVEN]
// i.e.  class GameObject : public Attachable, public DistributedObject
//
// The 0x28 offset is corroborated three independent ways:
//   1. RTTI base_info offset_flags 0x2802 -> offset 0x28              [PROVEN]
//   2. __ZThn40_ this-adjusting thunks in the secondary vtable (40 == 0x28)
//   3. GameObject ctor 0x10001BCC0: lea rdi,[rbx+0x28]; call DistributedObject::ctor
//      and UpdatePermState 0x10009FD59: lea rcx,[rax+0x28] on GameObject::userObject

class DistributedObject            // sizeof >= 0x180  [PROVEN lower bound]
{                                  // exact size UNRESOLVED - see notes at end
public:
    // +0x00 vptr. Secondary vptr inside GameObject is set to
    //       _ZTV10GameObject+0x148, which is exactly the first virtual slot of
    //       the secondary (DistributedObject) vtable.                  [PROVEN]
    void*     __vptr;                                       // +0x000  8

private:
    uint8_t   m_flag08;            // +0x008 [PROVEN] zeroed by ctor (byte store).
                                   //        Semantic meaning unrecovered.
    uint8_t   _pad_009[0x53];      // +0x009 .. +0x05B  UNRECOVERED

    // ---- ctor-initialised block. Every field below is written by
    //      DistributedObject::DistributedObject() @ 0x10009F47A.
    int32_t   m_field5C;           // +0x05C [PROVEN] dword, zeroed by ctor
    uint8_t   m_field60;           // +0x060 [PROVEN] byte,  zeroed by ctor
    uint8_t   m_recycle;           // +0x061 [PROVEN] byte,  zeroed by ctor;
                                   //        written by SetRecycle() @0x1000A15F0
    uint16_t  m_playerID;          // +0x062 [PROVEN] u16 owner/authority player id
                                   //        SetPlayerID @0x10009FBA6 (word store)
                                   //        GetPlayerID @0x1000A0538 (movzx word)
    uint32_t  m_id;                // +0x064 [PROVEN] u32 network object id
                                   //        GetID @0x1000A0786 (dword load)
                                   //        composed as (playerID<<16)+counter,
                                   //        see SetLocal note below.
                                   //        NOT ctor-initialised - assigned on
                                   //        SetLocal/Create.
    uint8_t   m_locality;          // +0x068 [PROVEN] u8 enum, zeroed by ctor
                                   //        0 = unowned/none
                                   //        1 = Local   (IsLocal  @0x1000A0616)
                                   //        2 = Remote  (IsRemote @0x1000A0606)
    uint8_t   _pad_069[3];         // +0x069 alignment                 [PROBABLE]
    int32_t   m_field6C;           // +0x06C [PROVEN] dword, zeroed by ctor.
                                   //        read by PermStateChanged, Destroy,
                                   //        GetRank -> change/dirty accounting
                                   //        [PROBABLE]
    uint8_t   m_dirty;             // +0x070 [PROVEN] byte. SetDirty @0x1000A04E4
                                   //        stores literal 1. Read by
                                   //        PermStateChanged @0x1000A04EE.
    uint8_t   _pad_071[3];         // +0x071 alignment                 [PROBABLE]
    float     m_permStateInterval; // +0x074 [PROVEN] ctor writes 0x3F800000 (1.0f)
                                   //        [PROBABLE] name/semantics
    int32_t   m_field78;           // +0x078 [PROVEN] dword, zeroed by ctor;
                                   //        read by ExpireRemoteObject @0x1000A051E

    uint8_t   _pad_07C[0x18];      // +0x07C .. +0x093  UNRECOVERED
    int32_t   m_field94;           // +0x094 [PROVEN] accessed by
                                   //        TempStateSendAll @0x1000A08CA
    uint8_t   _pad_098[0x58];      // +0x098 .. +0x0EF  UNRECOVERED
    int32_t   m_fieldF0;           // +0x0F0 [PROVEN] accessed by Explode @0x1000A0626
    uint8_t   _pad_0F4[0x88];      // +0x0F4 .. +0x17B  UNRECOVERED
    int32_t   m_field17C;          // +0x17C [PROVEN] dword. Read by SetLocal,
                                   //        Destroy and UpdatePermState. Used as
                                   //        (0x1200 + m_field17C) for the high half
                                   //        of the keyLocalIDMap key.
                                   //        [SPECULATIVE] a per-object spawn/slot
                                   //        or mission-scoped index.

    // ---- end of PROVEN accesses. sizeof is at least 0x180.

public:
    // -----------------------------------------------------------------------
    // Static registries  (all [PROVEN] - addresses are unslid Mac VAs)
    // -----------------------------------------------------------------------
    // uint32 counters, both initialised to 1 in __DATA, 4 bytes apart:
    static uint32_t dwLocalIDCounter;    // 0x100477AC8
    static uint32_t dwGlobalIDCounter;   // 0x100477ACC

    // Registries. Both maps are keyed by the u32 object id and are keyed from
    // &this->m_id (the code passes rbx+0x64 directly as the key pointer).
    // std::map<uint32_t, DistributedObject*>:
    static void* remoteDistributedObjectMap;  // 0x102E67F40  (24-byte libc++ map)
    static void* localDistributedObjectMap;   // 0x102E67F58  (24-byte libc++ map)
    // std::vector<DistributedObject*> - every live instance, push_back in ctor,
    // remove/erase in dtor:
    static void* allDistributedObjectList;    // 0x102E67F70

    // File-scope, not a class static:
    //   keyLocalIDMap @ 0x100A95E80
    //     std::map<std::pair<uint16_t,uint32_t>, uint32_t>
    //     key = { m_playerID, 0x1200 + m_field17C }                    [PROVEN]
    //   codes @ 0x100A95EC0
    //     102 (0x66) entries x 8 bytes, lives in __bss and is populated at
    //     runtime. Maps an 8-char ODF class name (masked with
    //     0x7F7F7F7F7F7F7F7F) to a 1-byte compact class code.          [PROVEN]

    // Packet staging (class statics, [PROVEN]):
    static uint8_t  packet_buffer[0x480];     // 0x102DF3650, 1152 bytes
                                              // (size from the gap to the next
                                              //  symbol - [HIGH], not [PROVEN])
    static uint64_t packet_buffer_length;     // 0x102DF3AD0  (qword store in
                                              //  UpdatePermState)
    static uint16_t local_user_id;            // 0x102DF3AD8  u16 - SetGlobalPlayerID
                                              //  @0x10009F46C stores a word
    static uint32_t next_remove_oldobjects;   // 0x102DF3ADC

    // -----------------------------------------------------------------------
    // Virtual layout - secondary vtable slot order          [PROVEN]
    // Standalone vtable 0x1004519F8; slots 0,1,3 read as 0 on disk, consistent
    // with pure virtuals bound to __cxa_pure_virtual by dyld  [HIGH]
    // -----------------------------------------------------------------------
    //  [ 0] GetClass()                     = 0   (pure)
    //  [ 1] GetTeam()                      = 0   (pure)
    //  [ 2] SetTeam(int)
    //  [ 3] GetPosition()                  = 0   (pure)
    //  [ 4] Remove()
    //  [ 5] Explode()
    //  [ 6] GetRank(float, float)
    //  [ 7] GetHealth()
    //  [ 8] GetRecycle()
    //  [ 9] SetRecycle()
    //  [10] AddHealth(float)
    //  [11] GetEntity()
    //  [12] GetOBJ76()
    //  [13] Getroot()
    //  [14] DamageAlloc(DAMAGE*, VECTOR_3D*)
    //  [15] PackTempState(void*, size_t*)
    //  [16] UnPackTempState(void*, size_t*)
    //  [17] PackPermState(void*, size_t*)
    //  [18] UnPackPermState(void*, size_t)
    //  [19] PermStateChanged(float)
    //  [20] ExpireRemoteObject(float)
    //
    // NOTE: there is no virtual destructor. Slot 0 of the secondary vtable is
    // GetClass, not a destructor pair. Deleting through a DistributedObject*
    // would not run the derived destructor.                            [PROVEN]
};

// ---------------------------------------------------------------------------
// Network ID composition  [PROVEN] - DistributedObject::SetLocal @ 0x1000A007A
// ---------------------------------------------------------------------------
//   eax  = Net::myPlayerIDInt            (u16 @ 0x102ED0290)
//   eax <<= 16
//   eax += DistributedObject::dwLocalIDCounter
//   this->m_id = eax
//   ++dwLocalIDCounter
//
//   m_id = (playerID << 16) | perPlayerCounter
//
// The remote->local takeover path tests `m_id < 0x10000`, i.e. "was this object
// authored by player 0 / pre-placed", and only rewrites m_playerID and the
// keyLocalIDMap entry for ids at or above 0x10000.                      [PROVEN]
//
// This is an intentional fixed-width distributed identifier, not a truncated
// pointer: it is 32 bits wide in a 64-bit build, it is composed arithmetically
// from a 16-bit player id, and it is the map key on both sides.

// ---------------------------------------------------------------------------
// Unresolved
// ---------------------------------------------------------------------------
// 1. Exact sizeof(DistributedObject). Lower bound 0x180 is proven by the dword
//    access at +0x17C. The upper bound is not established: GameObject's own
//    constructor writes into +0xD0 and +0xF8 of the complete object, which are
//    inside the DistributedObject subobject, so derived-class initialisation of
//    base fields prevents using the constructor as a boundary probe.
// 2. Fields +0x009..+0x05B, +0x07C..+0x093, +0x098..+0x0EF, +0x0F4..+0x17B.
// 3. Whether m_field6C is a change counter, a timestamp, or a bitfield.
