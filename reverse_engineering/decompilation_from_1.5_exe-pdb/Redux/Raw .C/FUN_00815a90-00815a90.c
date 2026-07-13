
undefined4 FUN_00815a90(undefined4 param_1,undefined1 *param_2,undefined4 param_3)

{
  undefined1 **ppuVar1;
  undefined4 uVar2;
  undefined1 *puStack_30;
  uint uStack_2c;
  undefined1 *local_20;
  undefined1 local_1c [4];
  undefined4 local_18;
  allocator<char> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855c08;
  local_10 = ExceptionList;
  uStack_2c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_30 = param_2;
  puStack_30 = (undefined1 *)FUN_00417780();
  local_18 = FUN_00736d50();
  puStack_30 = (undefined1 *)0x815ad8;
  puStack_30 = (undefined1 *)std::allocator<char>::allocator<char>(local_14);
  FUN_00416430(local_18);
  local_8 = 0;
  local_20 = (undefined1 *)&puStack_30;
  ppuVar1 = &puStack_30;
  uVar2 = local_18;
  std::allocator<char>::allocator<char>(local_14);
  FUN_007007c0(ppuVar1,uVar2,param_3);
  FUN_006d0c50();
  puStack_30 = (undefined1 *)0x815b1a;
  FUN_00703d50();
  puStack_30 = local_1c;
  FUN_006cc240();
  local_8 = 0xffffffff;
  puStack_30 = (undefined1 *)0x815b35;
  FUN_00703d00();
  ExceptionList = local_10;
  return param_1;
}

