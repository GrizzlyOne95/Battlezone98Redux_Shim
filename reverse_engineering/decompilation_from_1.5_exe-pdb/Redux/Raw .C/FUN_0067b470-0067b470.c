
void __thiscall
FUN_0067b470(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,uchar *param_2,
            uchar *param_3)

{
  uint uVar1;
  _ExceptionHolder *p_Var2;
  _Wrap_alloc<class_std::allocator<unsigned_char>_> local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f4e8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Var2 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
  FUN_0067bc80(p_Var2);
  local_8 = 0;
  std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>
            (param_2,param_3,local_14);
  local_8 = 0xffffffff;
  FUN_0067b8b0(uVar1);
  ExceptionList = local_10;
  return;
}

