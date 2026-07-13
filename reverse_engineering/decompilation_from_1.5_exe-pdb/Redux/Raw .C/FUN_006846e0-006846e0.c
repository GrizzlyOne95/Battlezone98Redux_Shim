
undefined4 __thiscall
FUN_006846e0(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,
            undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  _ExceptionHolder *p_Var2;
  undefined4 uVar3;
  undefined1 local_14 [4];
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f8d8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Var2 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
  FUN_00683cc0(p_Var2);
  local_8 = 0;
  uVar3 = FUN_00684900(param_2,param_3,param_4,local_14,uVar1);
  local_8 = 0xffffffff;
  FUN_00683b70();
  ExceptionList = local_10;
  return uVar3;
}

