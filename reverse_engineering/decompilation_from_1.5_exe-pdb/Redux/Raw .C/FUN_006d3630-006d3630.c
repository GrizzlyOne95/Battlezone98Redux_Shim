
undefined4 * __thiscall
FUN_006d3630(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4,
            undefined4 *param_5)

{
  undefined4 uVar1;
  
  uVar1 = FUN_006d6170(param_5,param_1);
  uVar1 = FUN_006d0d10(uVar1);
  FUN_006ae950(*param_3,uVar1);
  uVar1 = param_5[1];
  *param_2 = *param_5;
  param_2[1] = uVar1;
  return param_2;
}

