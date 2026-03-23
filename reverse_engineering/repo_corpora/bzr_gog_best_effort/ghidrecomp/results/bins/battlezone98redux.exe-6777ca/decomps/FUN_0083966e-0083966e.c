
int FUN_0083966e(uint *param_1)

{
  uint uVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = 0;
  uVar1 = *param_1;
  FUN_00839600(param_1,uVar1);
  iVar3 = *(int *)param_1[0xe];
  *(int *)param_1[0xe] = iVar3 + -1;
  if (iVar3 == 0) {
    uVar4 = FUN_0082ec27(param_1[0xe]);
  }
  else {
    pbVar2 = *(byte **)(param_1[0xe] + 4);
    uVar4 = (uint)*pbVar2;
    *(byte **)(param_1[0xe] + 4) = pbVar2 + 1;
  }
  while (*param_1 = uVar4, uVar4 == 0x3d) {
    FUN_00839600(param_1,*param_1);
    iVar3 = *(int *)param_1[0xe];
    *(int *)param_1[0xe] = iVar3 + -1;
    if (iVar3 == 0) {
      uVar4 = FUN_0082ec27(param_1[0xe]);
    }
    else {
      pbVar2 = *(byte **)(param_1[0xe] + 4);
      uVar4 = (uint)*pbVar2;
      *(byte **)(param_1[0xe] + 4) = pbVar2 + 1;
    }
    iVar5 = iVar5 + 1;
  }
  iVar3 = -1 - iVar5;
  if (uVar4 == uVar1) {
    iVar3 = iVar5;
  }
  return iVar3;
}

