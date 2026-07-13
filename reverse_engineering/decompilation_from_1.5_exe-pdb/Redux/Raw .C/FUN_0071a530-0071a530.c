
undefined4 * __thiscall FUN_0071a530(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  uVar2 = puVar1[1];
  *param_1 = *puVar1;
  param_1[1] = uVar2;
  uVar2 = FUN_00417780(param_2 + 8);
  basic_string<>(uVar2);
  return param_1;
}

