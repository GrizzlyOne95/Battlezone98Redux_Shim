
undefined4 FUN_006da6b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  shared_ptr<class___ExceptionPtr> *psVar1;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  shared_ptr<class___ExceptionPtr> local_24 [8];
  undefined4 local_1c;
  undefined1 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853848;
  local_10 = ExceptionList;
  uStack_28 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_2c = 0x6da6e0;
  uStack_2c = FUN_004170c0();
  uStack_30 = param_3;
  psVar1 = local_24;
  FUN_00421ec0(psVar1);
  FUN_006e1b80(psVar1);
  local_8 = 0;
  uStack_2c = param_2;
  uStack_30 = 0x6da711;
  FUN_00421ec0();
  uStack_30 = 0x6da718;
  FUN_006e1ac0();
  uStack_2c = 1;
  uStack_30 = 0x6da722;
  FUN_00421ec0();
  uStack_30 = 0x6da729;
  FUN_006e1aa0();
  local_18 = (undefined1 *)&uStack_30;
  local_1c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       ((shared_ptr<class___ExceptionPtr> *)&uStack_30,local_24);
  FUN_006e8a10(param_1);
  local_8 = 0xffffffff;
  uStack_2c = 0x6da758;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

