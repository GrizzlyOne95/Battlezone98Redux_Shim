
void FUN_0046a140(float param_1,float param_2,int param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  FUN_00461fd0(param_1 * DAT_02cc50e4);
  iVar3 = FUN_0083f040();
  FUN_00461fd0(param_2 * DAT_02cc50e4);
  iVar4 = FUN_0083f040();
  iVar4 = iVar4 - DAT_02cd9984;
  if ((((-1 < iVar4) && (iVar4 < DAT_02ce99c4 - DAT_02cd9984)) &&
      (iVar3 = iVar3 - DAT_02ce99c0, -1 < iVar3)) &&
     ((iVar3 < DAT_02ce99a0 - DAT_02ce99c0 &&
      (sVar1 = *(short *)(param_3 + ((DAT_02ce99a0 - DAT_02ce99c0) * iVar4 + iVar3) * 2), sVar1 != 0
      )))) {
    uVar2 = FUN_00469fd0(param_4,sVar1);
    FUN_0046a090(param_5,param_6,uVar2);
  }
  return;
}

