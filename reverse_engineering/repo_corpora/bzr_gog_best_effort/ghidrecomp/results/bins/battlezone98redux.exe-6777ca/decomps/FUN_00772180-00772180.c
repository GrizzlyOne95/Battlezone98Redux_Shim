
undefined4 * __thiscall FUN_00772180(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  FUN_00730810();
  *param_2 = uVar1;
  param_2[1] = uVar2;
  return param_2;
}

