
void __thiscall FUN_0080c220(allocator<char> *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  __ExceptionPtr *p_Var3;
  undefined1 *puVar4;
  undefined1 local_60 [52];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00864a69;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puVar4 = local_2c;
  local_14 = uVar1;
  std::allocator<char>::allocator<char>(param_1);
  uVar2 = FUN_0080b5d0(puVar4);
  local_8 = 1;
  FUN_007fae60(uVar2);
  local_8._0_1_ = 3;
  ~basic_string<>(uVar1);
  p_Var3 = (__ExceptionPtr *)FUN_0080b640(local_60,param_3);
  std::_Enable_shared_from_this<class___ExceptionPtr,class___ExceptionPtr>
            ((shared_ptr<class___ExceptionPtr> *)param_1,p_Var3);
  FUN_008018b0(local_60);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00800170();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

