
void __fastcall FUN_0075a3c0(CDaoErrorInfo *param_1)

{
  uint uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085c98f;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = BZRNetP2P::vftable;
  local_8 = 5;
  iVar2 = get(uVar1);
  if (*(CDaoErrorInfo **)(iVar2 + 0xc3c) == param_1) {
    iVar2 = get(uVar1);
    *(undefined4 *)(iVar2 + 0xc3c) = 0;
  }
  local_8._0_1_ = 4;
  FUN_006676c0();
  local_8._0_1_ = 3;
  FUN_00428210();
  local_8._0_1_ = 2;
  FUN_00428210();
  local_8._0_1_ = 1;
  FUN_0075fb50();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004284d0();
  local_8 = 0xffffffff;
  CDaoErrorInfo::~CDaoErrorInfo(param_1);
  ExceptionList = local_10;
  return;
}

