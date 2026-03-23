
void __thiscall
FUN_0066cab0(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,
            undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  _ExceptionHolder *p_Var2;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084eaa8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Var2 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
  FUN_0066c160(p_Var2);
  local_8 = 0;
  _Destroy_range<>(param_2,param_3,local_14,uVar1);
  local_8 = 0xffffffff;
  FUN_0066b5b0();
  ExceptionList = local_10;
  return;
}

