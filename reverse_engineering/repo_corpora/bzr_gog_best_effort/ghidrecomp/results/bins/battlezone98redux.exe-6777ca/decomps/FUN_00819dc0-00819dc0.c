
void __fastcall FUN_00819dc0(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)FUN_00422ea0();
  FUN_00819e40(*puVar1);
  puVar1 = (undefined4 *)FUN_00422ea0();
  *puVar1 = *param_1;
  puVar1 = (undefined4 *)FUN_00422e60();
  *puVar1 = *param_1;
  puVar1 = (undefined4 *)FUN_00422e80();
  *puVar1 = *param_1;
  param_1[1] = 0;
  return;
}

