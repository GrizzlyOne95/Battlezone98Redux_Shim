
void FUN_006f78d0(__ExceptionPtr *param_1)

{
  _Ref_count<class___ExceptionPtr> *this;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085573c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  this = operator_new(0x14);
  local_8._0_1_ = 1;
  if (this == (_Ref_count<class___ExceptionPtr> *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = std::_Ref_count<class___ExceptionPtr>::_Ref_count<class___ExceptionPtr>(this,param_1)
    ;
  }
  local_8 = (uint)local_8._1_3_ << 8;
  _Resetp0<>(param_1,local_1c);
  FUN_006f797e();
  return;
}

