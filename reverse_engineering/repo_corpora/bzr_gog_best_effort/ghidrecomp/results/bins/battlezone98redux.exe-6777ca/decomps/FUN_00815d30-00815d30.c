
void __thiscall
FUN_00815d30(shared_ptr<class___ExceptionPtr> *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  __ExceptionPtr *p_Var2;
  undefined1 local_60 [52];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864cf9;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("alternative");
  local_8 = 1;
  FUN_007fae60(local_2c);
  local_8._0_1_ = 3;
  ~basic_string<>(uVar1);
  p_Var2 = (__ExceptionPtr *)FUN_0080b640(local_60,param_3);
  std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>(param_1,p_Var2);
  FUN_008018b0(local_60);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00800170();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

