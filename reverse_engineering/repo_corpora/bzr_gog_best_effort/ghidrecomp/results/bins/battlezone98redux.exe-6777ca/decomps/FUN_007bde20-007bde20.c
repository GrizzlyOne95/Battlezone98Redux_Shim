
void __thiscall FUN_007bde20(undefined4 *param_1,__ExceptionPtr *param_2)

{
  _Ref_count<class___ExceptionPtr> *this;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00861acc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *param_1 = 0;
  local_8 = 0;
  this = operator_new(0x10);
  local_8._0_1_ = 1;
  if (this == (_Ref_count<class___ExceptionPtr> *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = std::tr1::_Ref_count<class___ExceptionPtr>::_Ref_count<class___ExceptionPtr>
                         (this,param_2);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  *param_1 = local_20;
  FUN_007bdeca();
  return;
}

