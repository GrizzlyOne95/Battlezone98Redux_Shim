
undefined4 * __thiscall FUN_006f6410(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  uVar2 = FUN_00417780(param_2 + 8);
  FUN_006feb50(uVar2);
  return param_1;
}

