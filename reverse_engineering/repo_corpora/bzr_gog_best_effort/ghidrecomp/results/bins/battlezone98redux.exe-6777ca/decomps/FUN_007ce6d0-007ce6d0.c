
void __fastcall FUN_007ce6d0(int param_1)

{
  _Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *this;
  int iVar1;
  
  this = (_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *)FUN_00764760();
  std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(this);
  iVar1 = FUN_004170c0();
  if (*(uint *)(param_1 + 0x294c) <= (uint)(iVar1 - *(int *)(param_1 + 0x2958))) {
    *(int *)(param_1 + 0x2958) = *(int *)(param_1 + 0x2958) + 1;
    FUN_007ce580();
  }
  return;
}

