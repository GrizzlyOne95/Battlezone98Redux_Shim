/*
 * Entry: 005c8ca0
 * Name: FUN_005c8ca0
 * Namespace: Global
 * Signature: undefined FUN_005c8ca0()
 * Symbol source: DEFAULT
 * Export status: ok
 */

undefined4 FUN_005c8ca0(int param_1)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  int *in_EAX;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int *unaff_ESI;
  uint uVar7;
  uint local_8;
  
  iVar5 = in_EAX[9];
  if (in_EAX[8] <= iVar5) {
    return 0;
  }
  puVar6 = (uint *)(in_EAX[4] + iVar5 * 4);
  if ((*(uint *)(in_EAX[4] + iVar5 * 4) & 0x400) != 0) {
    puVar6 = (uint *)(in_EAX + 0x56);
    uVar2 = *puVar6;
    *puVar6 = *puVar6 + 1;
    in_EAX[9] = iVar5 + 1;
    in_EAX[0x57] = in_EAX[0x57] + (uint)(0xfffffffe < uVar2);
    return 0xffffffff;
  }
  if ((unaff_ESI != (int *)0x0) || (param_1 != 0)) {
    uVar2 = *puVar6;
    uVar7 = uVar2 & 0xff;
    local_8 = uVar2 & 0x200;
    uVar4 = uVar7;
    while (uVar4 == 0xff) {
      puVar1 = puVar6 + 1;
      puVar6 = puVar6 + 1;
      iVar5 = iVar5 + 1;
      uVar4 = *puVar1 & 0xff;
      if ((*puVar1 & 0x200) != 0) {
        local_8 = 0x200;
      }
      uVar7 = uVar7 + uVar4;
    }
    if (unaff_ESI != (int *)0x0) {
      unaff_ESI[3] = local_8;
      unaff_ESI[2] = uVar2 & 0x100;
      *unaff_ESI = in_EAX[3] + *in_EAX;
      unaff_ESI[6] = in_EAX[0x56];
      unaff_ESI[7] = in_EAX[0x57];
      iVar3 = in_EAX[5];
      unaff_ESI[4] = *(int *)(iVar3 + iVar5 * 8);
      unaff_ESI[5] = *(int *)(iVar3 + 4 + iVar5 * 8);
      unaff_ESI[1] = uVar7;
    }
    if (param_1 != 0) {
      in_EAX[3] = in_EAX[3] + uVar7;
      puVar6 = (uint *)(in_EAX + 0x56);
      uVar2 = *puVar6;
      *puVar6 = *puVar6 + 1;
      in_EAX[9] = iVar5 + 1;
      in_EAX[0x57] = in_EAX[0x57] + (uint)(0xfffffffe < uVar2);
    }
  }
  return 1;
}
