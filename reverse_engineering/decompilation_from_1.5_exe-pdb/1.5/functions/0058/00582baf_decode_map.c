/*
 * Entry: 00582baf
 * Name: decode_map
 * Namespace: Global
 * Signature: void decode_map(uchar * param_1, ushort * param_2, ulong param_3, ulong param_4, PVECTOR * param_5, ulong param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
decode_map(uchar *param_1,ushort *param_2,ulong param_3,ulong param_4,PVECTOR *param_5,ulong param_6
          )

{
  uint uVar1;
  undefined4 unaff_EBX;
  PVECTOR *unaff_ESI;
  uchar *unaff_EDI;
  ushort uVar2;
  ushort *local_18;
  uchar *local_14;
  
  if ((ushort *)0x3 < param_2) {
    local_18 = (ushort *)0x3;
    do {
      local_14 = (uchar *)0x3;
      if ((uchar *)0x3 < unaff_EDI) {
        do {
          set_vector(unaff_EDI,4,4,param_3,unaff_ESI,(ushort)unaff_EBX);
          local_14 = local_14 + 4;
        } while (local_14 < unaff_EDI);
      }
      if (((uint)unaff_EDI & 3) != 0) {
        set_vector(unaff_EDI,(uint)unaff_EDI & 3,4,param_3,unaff_ESI,(ushort)unaff_EBX);
      }
      local_18 = local_18 + 2;
    } while (local_18 < param_2);
  }
  uVar2 = (ushort)unaff_EBX;
  uVar1 = (uint)param_2 & 3;
  if (uVar1 != 0) {
    if ((uchar *)0x3 < unaff_EDI) {
      local_18 = (ushort *)0x3;
      do {
        set_vector(unaff_EDI,4,uVar1,param_3,unaff_ESI,(ushort)unaff_EBX);
        uVar2 = (ushort)unaff_EBX;
        local_18 = (ushort *)((int)local_18 + 4);
      } while (local_18 < unaff_EDI);
    }
    if (((uint)unaff_EDI & 3) != 0) {
      set_vector(unaff_EDI,(uint)unaff_EDI & 3,uVar1,param_3,unaff_ESI,uVar2);
    }
  }
  return;
}
