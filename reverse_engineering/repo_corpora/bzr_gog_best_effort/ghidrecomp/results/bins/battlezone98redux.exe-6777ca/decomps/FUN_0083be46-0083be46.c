
void FUN_0083be46(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  int local_8;
  
  iVar1 = FUN_0083bffe(param_2,param_3,param_4);
  if (iVar1 == 0) {
    if ((param_2 == 0x12) || (param_2 == 0x14)) {
      local_8 = 0;
    }
    else {
      local_8 = FUN_0083c706(param_1,param_4);
    }
    iVar1 = FUN_0083c706(param_1,param_3);
    if (local_8 < iVar1) {
      FUN_0083c3b1(param_1,param_3);
    }
    else {
      FUN_0083c3b1(param_1,param_4);
      param_4 = param_3;
    }
    FUN_0083c3b1(param_1,param_4);
    uVar2 = FUN_0083c5d2(param_1,param_2,0,iVar1,extraout_EDX);
    param_3[2] = uVar2;
    *param_3 = 0xb;
  }
  return;
}

