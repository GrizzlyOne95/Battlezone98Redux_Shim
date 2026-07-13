/*
 * Entry: 00583899
 * Name: swd_findbest
 * Namespace: Global
 * Signature: void swd_findbest(lzo1x_999_swd_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_findbest(lzo1x_999_swd_t *param_1)

{
  ushort *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  ulong unaff_EBX;
  ushort uVar7;
  lzo1x_999_swd_t *unaff_ESI;
  uint uVar8;
  int unaff_EDI;
  
  iVar4 = *(int *)(unaff_EDI + 0x154);
  uVar3 = (((uint)*(byte *)(iVar4 + 0x16c + unaff_EDI) << 5 ^
           (uint)*(byte *)(iVar4 + 0x16d + unaff_EDI)) << 5 ^
          (uint)*(byte *)(iVar4 + 0x16e + unaff_EDI)) * 0x9f5f >> 5 & 0x3fff;
  puVar1 = (ushort *)(unaff_EDI + 0x47168 + uVar3 * 2);
  uVar7 = 0xffff;
  if (*puVar1 != 0) {
    uVar7 = *(ushort *)(unaff_EDI + 0xd16c + uVar3 * 2);
  }
  *(ushort *)(unaff_EDI + 0x1516c + iVar4 * 2) = uVar7;
  uVar8 = (uint)*puVar1;
  *puVar1 = *puVar1 + 1;
  uVar2 = *(uint *)(unaff_EDI + 0xc);
  if ((uVar2 < uVar8) && (uVar2 != 0)) {
    uVar8 = uVar2;
  }
  *(undefined2 *)(unaff_EDI + 0xd16c + uVar3 * 2) = *(undefined2 *)(unaff_EDI + 0x154);
  uVar3 = *(uint *)(unaff_EDI + 0x1c);
  *(uint *)(unaff_EDI + 0x28) = (uint)*(byte *)(*(int *)(unaff_EDI + 0x154) + 0x16c + unaff_EDI);
  if (uVar3 < *(uint *)(unaff_EDI + 0x24)) {
    iVar4 = swd_search2(unaff_ESI);
    if ((iVar4 != 0) && (2 < *(uint *)(unaff_EDI + 0x24))) {
      swd_search((lzo1x_999_swd_t *)(uint)uVar7,uVar8,(ulong)unaff_ESI);
    }
    if (uVar3 < *(uint *)(unaff_EDI + 0x1c)) {
      uVar3 = *(uint *)(unaff_EDI + 0xb8);
      if (uVar3 < *(uint *)(unaff_EDI + 0x154)) {
        iVar4 = -uVar3;
      }
      else {
        iVar4 = *(int *)(unaff_EDI + 0x15c) - uVar3;
      }
      *(uint *)(unaff_EDI + 0x20) = *(uint *)(unaff_EDI + 0x154) + iVar4;
    }
    *(undefined2 *)(unaff_EDI + 0x2e16a + *(int *)(unaff_EDI + 0x154) * 2) =
         *(undefined2 *)(unaff_EDI + 0x1c);
    if (*(int *)(unaff_EDI + 0x14) != 0) {
      piVar6 = (int *)(unaff_EDI + 0xc4);
      iVar4 = 0x20;
      do {
        iVar5 = *piVar6;
        if (iVar5 == 0) {
          piVar6[-0x24] = 0;
        }
        else {
          uVar3 = *(uint *)(unaff_EDI + 0x154);
          if (iVar5 - 1U < uVar3) {
            iVar5 = (uVar3 - iVar5) + 1;
          }
          else {
            iVar5 = (*(int *)(unaff_EDI + 0x15c) - iVar5) + 1 + uVar3;
          }
          piVar6[-0x24] = iVar5;
        }
        piVar6 = piVar6 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
  }
  else {
    if (*(uint *)(unaff_EDI + 0x24) == 0) {
      *(undefined4 *)(unaff_EDI + 0x28) = 0xffffffff;
    }
    *(undefined4 *)(unaff_EDI + 0x20) = 0;
    *(short *)(unaff_EDI + 0x2e16a + *(int *)(unaff_EDI + 0x154) * 2) =
         *(short *)(unaff_EDI + 4) + 1;
  }
  swd_remove_node(unaff_ESI,unaff_EBX);
  *(undefined2 *)
   (unaff_EDI + 0x4f168 + (uint)*(ushort *)(unaff_EDI + 0x16c + *(int *)(unaff_EDI + 0x154)) * 2) =
       *(undefined2 *)(unaff_EDI + 0x154);
  return;
}
