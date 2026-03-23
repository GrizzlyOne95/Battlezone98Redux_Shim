
void FUN_00442ca0(undefined4 *param_1)

{
  int iVar1;
  
  FUN_004438f0(param_1);
  if (param_1[9] != 0) {
    iVar1 = FUN_0062e000(*param_1);
    if (iVar1 == 0) {
      DAT_0260d0f0 = FUN_00824540(DAT_0260d0f0,0,param_1);
      FUN_004429d0(param_1);
    }
    else {
      DAT_0260cac4 = FUN_00824540(DAT_0260cac4,0,param_1);
    }
  }
  iVar1 = FUN_00445220(*param_1);
  if (iVar1 != 0) {
    FUN_00444ef0(param_1);
  }
  return;
}

