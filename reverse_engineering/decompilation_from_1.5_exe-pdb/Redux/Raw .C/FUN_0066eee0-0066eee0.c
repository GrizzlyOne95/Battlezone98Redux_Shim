
undefined4 __thiscall
FUN_0066eee0(_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder> *param_1,
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
  puStack_c = &LAB_0084ebe8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  p_Var2 = std::_Ref_count_obj<struct_Concurrency::details::_ExceptionHolder>::_Getptr(param_1);
  FUN_004b3270(p_Var2);
  local_8 = 0;
  uVar3 = FUN_00672da0(param_2,param_3,param_4,local_14,uVar1);
  local_8 = 0xffffffff;
  FUN_004b30a0();
  ExceptionList = local_10;
  return uVar3;
}

