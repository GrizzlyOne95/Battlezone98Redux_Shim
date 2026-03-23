
undefined4 FUN_008388ea(uint *param_1,char *param_2)

{
  int iVar1;
  byte *pbVar2;
  char *pcVar3;
  undefined4 uVar4;
  uint uVar5;
  
  pcVar3 = strchr(param_2,*param_1);
  uVar4 = 0;
  if (pcVar3 != (char *)0x0) {
    FUN_00839600(param_1,*param_1);
    iVar1 = *(int *)param_1[0xe];
    *(int *)param_1[0xe] = iVar1 + -1;
    if (iVar1 == 0) {
      uVar5 = FUN_0082ec27(param_1[0xe]);
    }
    else {
      pbVar2 = *(byte **)(param_1[0xe] + 4);
      uVar5 = (uint)*pbVar2;
      *(byte **)(param_1[0xe] + 4) = pbVar2 + 1;
    }
    *param_1 = uVar5;
    uVar4 = 1;
  }
  return uVar4;
}

