
void FUN_0083bed9(undefined4 param_1,int param_2,int param_3,undefined4 *param_4,undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 extraout_EDX;
  
  uVar1 = FUN_0083c706(param_1,param_4);
  FUN_0083c706(param_1,param_5);
  FUN_0083c3b1(param_1,param_5);
  FUN_0083c3b1(param_1,param_4);
  uVar2 = extraout_EDX;
  if ((param_3 == 0) && (uVar2 = extraout_EDX, param_2 != 0x17)) {
    param_3 = 1;
    uVar2 = uVar1;
    uVar1 = extraout_EDX;
  }
  uVar2 = FUN_0083bfda(param_1,param_2,param_3,uVar1,uVar2);
  param_4[2] = uVar2;
  *param_4 = 10;
  return;
}

