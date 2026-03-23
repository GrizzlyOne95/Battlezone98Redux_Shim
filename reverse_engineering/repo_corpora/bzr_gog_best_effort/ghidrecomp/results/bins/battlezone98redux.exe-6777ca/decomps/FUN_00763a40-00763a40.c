
void __fastcall FUN_00763a40(CDaoErrorInfo *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0085cff3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = CSteamP2P::vftable;
  local_8 = 1;
  FUN_00763a20(uVar1);
  local_8 = local_8 & 0xffffff00;
  FUN_00763a00();
  local_8 = 0xffffffff;
  CDaoErrorInfo::~CDaoErrorInfo(param_1);
  ExceptionList = local_10;
  return;
}

