
void FUN_008392cf(uint *param_1,undefined4 param_2)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  
  do {
    FUN_00839600(param_1,*param_1);
    iVar2 = *(int *)param_1[0xe];
    *(int *)param_1[0xe] = iVar2 + -1;
    if (iVar2 == 0) {
      uVar3 = FUN_0082ec27(param_1[0xe]);
    }
    else {
      pbVar1 = *(byte **)(param_1[0xe] + 4);
      uVar3 = (uint)*pbVar1;
      *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
    }
    *param_1 = uVar3;
    iVar2 = isdigit(uVar3);
  } while ((iVar2 != 0) || (*param_1 == 0x2e));
  iVar2 = FUN_008388ea(param_1,&DAT_008704bc);
  if (iVar2 != 0) {
    FUN_008388ea(param_1,&DAT_008704c0);
  }
  while( true ) {
    iVar2 = isalnum(*param_1);
    if ((iVar2 == 0) && (*param_1 != 0x5f)) break;
    FUN_00839600(param_1,*param_1);
    iVar2 = *(int *)param_1[0xe];
    *(int *)param_1[0xe] = iVar2 + -1;
    if (iVar2 == 0) {
      uVar3 = FUN_0082ec27(param_1[0xe]);
    }
    else {
      pbVar1 = *(byte **)(param_1[0xe] + 4);
      uVar3 = (uint)*pbVar1;
      *(byte **)(param_1[0xe] + 4) = pbVar1 + 1;
    }
    *param_1 = uVar3;
  }
  FUN_00839600(param_1,0);
  FUN_008388c1(param_1,0x2e,(char)param_1[0x11]);
  iVar2 = FUN_0082eb45(*(undefined4 *)param_1[0xf],param_2);
  if (iVar2 == 0) {
    FUN_008396f7(param_1,param_2);
  }
  return;
}

