
undefined4 __thiscall FUN_00703250(int *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  shared_ptr<class___ExceptionPtr> local_20 [8];
  uint local_18;
  int *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856a78;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = 0;
  local_14 = param_1;
  cVar1 = (**(code **)(*param_1 + 0x38))(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (cVar1 == '\0') {
    FUN_0068b0a0();
  }
  else {
    std::shared_ptr<class___ExceptionPtr>::shared_ptr<class___ExceptionPtr>
              (local_20,(shared_ptr<class___ExceptionPtr> *)local_14[0x12]);
    local_8 = 0;
    std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
              ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)local_14[0x12]);
    FUN_00421ec0();
    uVar2 = FUN_006cc050();
    cVar1 = FUN_006ba0d0(uVar2);
    if (cVar1 == '\0') {
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_14 + 8));
    }
    else {
      std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
                ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(local_14 + 0xd));
    }
    FUN_007058a0();
    shared_ptr<>(local_20);
    local_18 = local_18 | 1;
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  return param_2;
}

