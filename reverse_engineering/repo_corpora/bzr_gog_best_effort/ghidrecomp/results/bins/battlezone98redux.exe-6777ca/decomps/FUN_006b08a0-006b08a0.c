
void __fastcall FUN_006b08a0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085045c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = boost::asio::detail::select_reactor::vftable;
  local_8 = 4;
  FUN_006b0950(uVar1);
  local_8._0_1_ = 3;
  _eh_vector_destructor_iterator_(param_1 + 0x2a,0xc,3,FUN_006ae620);
  local_8._0_1_ = 2;
  _eh_vector_destructor_iterator_(param_1 + 0xe,0x1c,4,FID_conflict__CAtlWinModule);
  local_8._0_1_ = 1;
  FUN_006b0480();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006ac0b0();
  local_8 = 0xffffffff;
  FUN_006ad050();
  ExceptionList = local_10;
  return;
}

