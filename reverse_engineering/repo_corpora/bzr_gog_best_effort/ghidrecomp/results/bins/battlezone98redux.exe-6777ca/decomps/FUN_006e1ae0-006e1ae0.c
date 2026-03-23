
undefined4 FUN_006e1ae0(undefined4 param_1)

{
  uint uVar1;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853fe8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = 0;
  local_20 = begin(local_34);
  local_8 = 0;
  local_1c = local_20;
  local_24 = FUN_006f0c50(local_2c,local_20,uVar1);
  shared_ptr<>(local_24);
  local_14 = local_14 | 1;
  FUN_006ca8c0();
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

