
undefined4 * __thiscall FUN_00611800(undefined4 param_1,undefined4 *param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(**(code **)(*(int *)(param_3 + 0x18) + 0xc))(param_1);
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  return param_2;
}

