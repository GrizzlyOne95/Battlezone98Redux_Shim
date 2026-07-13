/*
 * Entry: 005836a2
 * Name: swd_accept
 * Namespace: Global
 * Signature: void swd_accept(lzo1x_999_swd_t * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_accept(lzo1x_999_swd_t *param_1,ulong param_2)

{
  int iVar1;
  short *psVar2;
  uint uVar3;
  undefined2 uVar4;
  lzo1x_999_swd_t *unaff_ESI;
  int unaff_EDI;
  ulong unaff_retaddr;
  
  for (; param_1 != (lzo1x_999_swd_t *)0x0;
      param_1 = (lzo1x_999_swd_t *)((int)param_1[-1].head2 + 0x1ffff)) {
    swd_remove_node(unaff_ESI,unaff_retaddr);
    iVar1 = unaff_EDI + *(int *)(unaff_EDI + 0x154);
    uVar3 = (((uint)*(byte *)(unaff_EDI + 0x16c + *(int *)(unaff_EDI + 0x154)) << 5 ^
             (uint)*(byte *)(iVar1 + 0x16d)) << 5 ^ (uint)*(byte *)(iVar1 + 0x16e)) * 0x9f5f >> 5 &
            0x3fff;
    psVar2 = (short *)(unaff_EDI + 0x47168 + uVar3 * 2);
    uVar4 = 0xffff;
    if (*psVar2 != 0) {
      uVar4 = *(undefined2 *)(unaff_EDI + 0xd16c + uVar3 * 2);
    }
    *(undefined2 *)(unaff_EDI + 0x1516c + *(int *)(unaff_EDI + 0x154) * 2) = uVar4;
    *(undefined2 *)(unaff_EDI + 0xd16c + uVar3 * 2) = *(undefined2 *)(unaff_EDI + 0x154);
    *(short *)(unaff_EDI + 0x2e16a + *(int *)(unaff_EDI + 0x154) * 2) =
         *(short *)(unaff_EDI + 4) + 1;
    *psVar2 = *psVar2 + 1;
    *(undefined2 *)
     (unaff_EDI + 0x4f168 + (uint)*(ushort *)(unaff_EDI + 0x16c + *(int *)(unaff_EDI + 0x154)) * 2)
         = *(undefined2 *)(unaff_EDI + 0x154);
    swd_getbyte(unaff_ESI);
  }
  return;
}
