
void __thiscall
FUN_0066c7b0(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,
            undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ea80;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
  uVar1 = FUN_0066d550(param_2);
  local_8 = 0;
  FUN_0066f050(*(undefined4 *)param_1,*(undefined4 *)(param_1 + 4),uVar1);
  FUN_0066c83d();
  return;
}

