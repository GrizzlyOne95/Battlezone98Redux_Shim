
undefined4 * __thiscall FUN_00676410(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  uVar2 = FUN_00417780(param_2 + 4);
  FUN_0045e0f0(uVar2);
  return param_1;
}

