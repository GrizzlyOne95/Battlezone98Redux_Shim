
undefined4 * __thiscall
FUN_006b13c0(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4,
            undefined4 *param_5)

{
  undefined4 uVar1;
  
  FUN_006aebe0(*param_3,param_4,param_5,param_1);
  uVar1 = param_5[1];
  *param_2 = *param_5;
  param_2[1] = uVar1;
  return param_2;
}

