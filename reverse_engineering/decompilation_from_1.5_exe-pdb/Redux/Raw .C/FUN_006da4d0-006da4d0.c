
undefined4 FUN_006da4d0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  _ExceptionHolder *p_Var3;
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *p_Var4;
  undefined1 local_2c [8];
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *local_24;
  uint local_20;
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *local_1c;
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *local_18;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008537f4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_20 = 0;
  local_14 = operator_new(0x50);
  local_8 = 0;
  if (local_14 == (void *)0x0) {
    local_18 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)0x0;
  }
  else {
    uVar2 = FUN_00417780(param_2,uVar1);
    local_18 = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_006e8920(uVar2);
  }
  local_24 = local_18;
  local_8 = 0xffffffff;
  local_1c = local_18;
  FUN_0068b0a0();
  local_8 = 1;
  p_Var4 = local_1c;
  p_Var3 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(local_1c);
  _Resetp0<>(p_Var3,p_Var4);
  shared_ptr<>(local_2c);
  local_20 = local_20 | 1;
  local_8 = 0xffffffff;
  FUN_006ca8c0();
  ExceptionList = local_10;
  return param_1;
}

