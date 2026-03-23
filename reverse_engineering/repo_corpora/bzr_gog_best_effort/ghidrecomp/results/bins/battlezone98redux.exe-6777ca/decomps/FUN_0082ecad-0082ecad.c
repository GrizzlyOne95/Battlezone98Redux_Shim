
undefined4 FUN_0082ecad(undefined4 param_1,undefined4 *param_2,uint param_3)

{
  undefined4 uVar1;
  
  if ((uint)param_2[2] < param_3) {
    if (param_3 < 0x20) {
      param_3 = 0x20;
    }
    if (param_3 + 1 < 0xfffffffe) {
      uVar1 = FUN_00838869(param_1,*param_2,param_2[2],param_3);
    }
    else {
      uVar1 = FUN_008388ab(param_1);
    }
    *param_2 = uVar1;
    param_2[2] = param_3;
  }
  return *param_2;
}

