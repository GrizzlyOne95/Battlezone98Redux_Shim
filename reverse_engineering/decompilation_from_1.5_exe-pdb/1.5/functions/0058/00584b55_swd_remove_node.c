/*
 * Entry: 00584b55
 * Name: swd_remove_node
 * Namespace: Global
 * Signature: void swd_remove_node(lzo1y_999_swd_t * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_remove_node(lzo1y_999_swd_t *param_1,ulong param_2)

{
  int iVar1;
  short *psVar2;
  ushort *puVar3;
  int in_EDX;
  uint unaff_ESI;
  
  if (*(int *)(in_EDX + 0x164) == 0) {
    iVar1 = in_EDX + unaff_ESI;
    psVar2 = (short *)(in_EDX + 0x47168 +
                      ((((uint)*(byte *)(iVar1 + 0x16c) << 5 ^ (uint)*(byte *)(iVar1 + 0x16d)) << 5
                       ^ (uint)*(byte *)(iVar1 + 0x16e)) * 0x9f5f >> 5 & 0x3fff) * 2);
    *psVar2 = *psVar2 + -1;
    puVar3 = (ushort *)(in_EDX + 0x4f168 + (uint)*(ushort *)(iVar1 + 0x16c) * 2);
    if (*puVar3 == unaff_ESI) {
      *puVar3 = 0xffff;
      return;
    }
  }
  else {
    *(int *)(in_EDX + 0x164) = *(int *)(in_EDX + 0x164) + -1;
  }
  return;
}
