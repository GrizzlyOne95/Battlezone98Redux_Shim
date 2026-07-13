
undefined4 * __thiscall FUN_00662210(undefined4 *param_1,undefined4 param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084db08;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00661990(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = SubEntityTransparencyMaterial::vftable;
  param_1[7] = param_2;
  FUN_006623e0();
  ExceptionList = local_10;
  return param_1;
}

