
void FUN_0083ae74(int param_1,int *param_2,undefined4 *param_3)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  
  piVar1 = *(int **)(param_1 + 0x30);
  iVar2 = *piVar1;
  iVar5 = *(int *)(iVar2 + 0x34);
  if (iVar5 < piVar1[0xb] + 1) {
    uVar3 = FUN_008387f7(*(undefined4 *)(param_1 + 0x34),*(undefined4 *)(iVar2 + 0x10),
                         (int *)(iVar2 + 0x34),4,0x3ffff,"constant table overflow");
    *(undefined4 *)(iVar2 + 0x10) = uVar3;
  }
  for (; iVar5 < *(int *)(iVar2 + 0x34); iVar5 = iVar5 + 1) {
    *(undefined4 *)(*(int *)(iVar2 + 0x10) + iVar5 * 4) = 0;
  }
  *(int *)(*(int *)(iVar2 + 0x10) + piVar1[0xb] * 4) = *param_2;
  piVar1[0xb] = piVar1[0xb] + 1;
  if (((*(byte *)(*param_2 + 5) & 3) != 0) && ((*(byte *)(iVar2 + 5) & 4) != 0)) {
    FUN_0083001b(*(undefined4 *)(param_1 + 0x34),iVar2,*param_2);
  }
  uVar3 = FUN_0083c5ff(piVar1,0x24,0,piVar1[0xb] + -1);
  param_1 = 0;
  param_3[4] = 0xffffffff;
  param_3[5] = 0xffffffff;
  *param_3 = 0xb;
  param_3[2] = uVar3;
  if (*(char *)(*param_2 + 0x48) != '\0') {
    pcVar4 = (char *)((int)param_2 + 0x33);
    do {
      uVar3 = 4;
      if (*pcVar4 == '\x06') {
        uVar3 = 0;
      }
      FUN_0083c5d2(piVar1,uVar3,0,pcVar4[1],0);
      pcVar4 = pcVar4 + 2;
      param_1 = param_1 + 1;
    } while (param_1 < (int)(uint)*(byte *)(*param_2 + 0x48));
  }
  return;
}

