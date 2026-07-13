
undefined4 *
FUN_006f27a0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_10 [12];
  
  iVar2 = FUN_006b3f60();
  if (iVar2 == 1) {
    FUN_006f5d50(local_10,param_2,param_3,param_4);
  }
  else {
    FUN_006d8cf0(0x2726);
  }
  uVar1 = param_4[1];
  *param_1 = *param_4;
  param_1[1] = uVar1;
  return param_1;
}

