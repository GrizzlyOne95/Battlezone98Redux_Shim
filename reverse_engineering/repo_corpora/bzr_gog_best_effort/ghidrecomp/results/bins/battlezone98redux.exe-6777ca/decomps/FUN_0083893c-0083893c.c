
void FUN_0083893c(uint *param_1)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = *param_1;
  iVar1 = *(int *)param_1[0xe];
  *(int *)param_1[0xe] = iVar1 + -1;
  if (iVar1 == 0) {
    uVar3 = FUN_0082ec27(param_1[0xe]);
  }
  else {
    pbVar2 = *(byte **)(param_1[0xe] + 4);
    uVar3 = (uint)*pbVar2;
    *(byte **)(param_1[0xe] + 4) = pbVar2 + 1;
  }
  *param_1 = uVar3;
  if (((uVar3 == 10) || (uVar3 == 0xd)) && (uVar3 != uVar4)) {
    iVar1 = *(int *)param_1[0xe];
    *(int *)param_1[0xe] = iVar1 + -1;
    if (iVar1 == 0) {
      uVar4 = FUN_0082ec27(param_1[0xe]);
    }
    else {
      pbVar2 = *(byte **)(param_1[0xe] + 4);
      uVar4 = (uint)*pbVar2;
      *(byte **)(param_1[0xe] + 4) = pbVar2 + 1;
    }
    *param_1 = uVar4;
  }
  param_1[1] = param_1[1] + 1;
  if (0x7ffffffc < (int)param_1[1]) {
    FUN_008390b7(param_1,"chunk has too many lines");
  }
  return;
}

