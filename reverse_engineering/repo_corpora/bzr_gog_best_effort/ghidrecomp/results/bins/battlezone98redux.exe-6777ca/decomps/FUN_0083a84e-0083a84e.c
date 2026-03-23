
uint FUN_0083a84e(int *param_1,int param_2,uint *param_3)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  
  uVar5 = 0;
  iVar2 = *param_1;
  uVar7 = (uint)*(byte *)(iVar2 + 0x48);
  iVar6 = *(int *)(iVar2 + 0x24);
  if (uVar7 != 0) {
    pbVar3 = (byte *)(param_1 + 0xd);
    do {
      if (((uint)pbVar3[-1] == *param_3) && ((uint)*pbVar3 == param_3[2])) {
        return uVar5;
      }
      uVar5 = uVar5 + 1;
      pbVar3 = pbVar3 + 2;
    } while ((int)uVar5 < (int)uVar7);
  }
  piVar8 = (int *)(iVar2 + 0x24);
  if (0x3c < uVar7 + 1) {
    FUN_0083a089(param_1,0x3c,"upvalues");
  }
  if (*piVar8 < (int)(*(byte *)(iVar2 + 0x48) + 1)) {
    uVar4 = FUN_008387f7(param_1[4],*(undefined4 *)(iVar2 + 0x1c),piVar8,4,0x7ffffffd,&DAT_008a1ad8)
    ;
    *(undefined4 *)(iVar2 + 0x1c) = uVar4;
  }
  for (; iVar6 < *piVar8; iVar6 = iVar6 + 1) {
    *(undefined4 *)(*(int *)(iVar2 + 0x1c) + iVar6 * 4) = 0;
  }
  *(int *)(*(int *)(iVar2 + 0x1c) + (uint)*(byte *)(iVar2 + 0x48) * 4) = param_2;
  if (((*(byte *)(param_2 + 5) & 3) != 0) && ((*(byte *)(iVar2 + 5) & 4) != 0)) {
    FUN_0083001b(param_1[4],iVar2,param_2);
  }
  *(char *)((int)param_1 + (uint)*(byte *)(iVar2 + 0x48) * 2 + 0x33) = (char)*param_3;
  *(char *)((int)param_1 + (uint)*(byte *)(iVar2 + 0x48) * 2 + 0x34) = (char)param_3[2];
  bVar1 = *(byte *)(iVar2 + 0x48);
  *(byte *)(iVar2 + 0x48) = bVar1 + 1;
  return (uint)bVar1;
}

