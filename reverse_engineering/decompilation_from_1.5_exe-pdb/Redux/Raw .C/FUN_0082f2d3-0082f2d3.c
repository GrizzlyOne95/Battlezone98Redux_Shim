
undefined4 FUN_0082f2d3(int param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  
  if (param_2[2] != 6) {
    param_2 = (int *)FUN_0082f8a7(param_1,param_2);
  }
  iVar6 = *param_2;
  iVar1 = *(int *)(param_1 + 0x20);
  *(undefined4 *)(*(int *)(param_1 + 0x14) + 0xc) = *(undefined4 *)(param_1 + 0x18);
  if (*(char *)(iVar6 + 6) == '\0') {
    iVar6 = *(int *)(iVar6 + 0x10);
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) <=
        (int)((uint)*(byte *)(iVar6 + 0x4b) * 0x10)) {
      FUN_0082f194(param_1,(uint)*(byte *)(iVar6 + 0x4b));
    }
    iVar7 = (int)param_2 + (*(int *)(param_1 + 0x20) - iVar1);
    if (*(char *)(iVar6 + 0x4a) == '\0') {
      iVar3 = iVar7 + 0x10;
      uVar2 = (uint)*(byte *)(iVar6 + 0x49) * 0x10 + iVar3;
      if (uVar2 < *(uint *)(param_1 + 8)) {
        *(uint *)(param_1 + 8) = uVar2;
      }
    }
    else {
      iVar3 = FUN_0082ed3d(param_1,iVar6,(*(int *)(param_1 + 8) - iVar7 >> 4) + -1);
      iVar7 = (int)param_2 + (*(int *)(param_1 + 0x20) - iVar1);
    }
    if (*(int *)(param_1 + 0x14) == *(int *)(param_1 + 0x24)) {
      piVar4 = (int *)FUN_0082f01b(param_1);
    }
    else {
      piVar4 = (int *)(*(int *)(param_1 + 0x14) + 0x18);
      *(int **)(param_1 + 0x14) = piVar4;
    }
    piVar4[1] = iVar7;
    *piVar4 = iVar3;
    *(int *)(param_1 + 0xc) = iVar3;
    piVar4[2] = (uint)*(byte *)(iVar6 + 0x4b) * 0x10 + iVar3;
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(iVar6 + 0xc);
    piVar4[5] = 0;
    piVar4[4] = param_3;
    for (uVar2 = *(uint *)(param_1 + 8); uVar2 < (uint)piVar4[2]; uVar2 = uVar2 + 0x10) {
      *(undefined4 *)(uVar2 + 8) = 0;
    }
    *(int *)(param_1 + 8) = piVar4[2];
    if ((*(byte *)(param_1 + 0x38) & 1) != 0) {
      *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 4;
      FUN_0082f0d6(param_1,0,0xffffffff);
      *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -4;
    }
    uVar5 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x141) {
      FUN_0082f194(param_1,0x14);
    }
    if (*(int *)(param_1 + 0x14) == *(int *)(param_1 + 0x24)) {
      piVar4 = (int *)FUN_0082f01b(param_1);
    }
    else {
      piVar4 = (int *)(*(int *)(param_1 + 0x14) + 0x18);
      *(int **)(param_1 + 0x14) = piVar4;
    }
    iVar6 = (int)param_2 + (*(int *)(param_1 + 0x20) - iVar1);
    piVar4[1] = iVar6;
    iVar6 = iVar6 + 0x10;
    *piVar4 = iVar6;
    *(int *)(param_1 + 0xc) = iVar6;
    piVar4[2] = *(int *)(param_1 + 8) + 0x140;
    piVar4[4] = param_3;
    if ((*(byte *)(param_1 + 0x38) & 1) != 0) {
      FUN_0082f0d6(param_1,0,0xffffffff);
    }
    iVar6 = (**(code **)(**(int **)(*(int *)(param_1 + 0x14) + 4) + 0x10))(param_1);
    if (iVar6 < 0) {
      uVar5 = 2;
    }
    else {
      FUN_0082f246(param_1,*(int *)(param_1 + 8) + iVar6 * -0x10);
      uVar5 = 1;
    }
  }
  return uVar5;
}

