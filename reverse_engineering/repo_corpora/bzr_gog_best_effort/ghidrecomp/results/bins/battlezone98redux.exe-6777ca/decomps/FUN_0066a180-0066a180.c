
undefined4 FUN_0066a180(undefined4 param_1)

{
  undefined1 *puVar1;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e8c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  puVar1 = local_24;
  FUN_004b4350(puVar1,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_20 = FUN_0066ba30(puVar1);
  local_8 = 0;
  local_1c = local_20;
  FUN_0066eb00(local_20);
  local_8._0_1_ = 1;
  FUN_0066b7d0(param_1,local_14);
  local_8._0_1_ = 3;
  FUN_0066a3d0();
  local_8 = CONCAT31(local_8._1_3_,4);
  FUN_0066b400();
  ExceptionList = local_10;
  return local_18;
}

