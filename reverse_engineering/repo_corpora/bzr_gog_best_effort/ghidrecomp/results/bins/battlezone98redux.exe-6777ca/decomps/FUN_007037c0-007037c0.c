
undefined4 FUN_007037c0(undefined4 param_1,undefined4 param_2)

{
  shared_ptr<class___ExceptionPtr> asStack_28 [4];
  undefined4 uStack_24;
  uint uStack_20;
  undefined4 local_1c;
  undefined1 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00856af8;
  local_10 = ExceptionList;
  uStack_20 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  local_18 = asStack_28;
  local_1c = std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
                       (asStack_28,(shared_ptr<class___ExceptionPtr> *)&stack0x0000000c);
  FUN_00705fc0(param_1,9,param_2);
  local_8 = 0xffffffff;
  uStack_24 = 0x703824;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

