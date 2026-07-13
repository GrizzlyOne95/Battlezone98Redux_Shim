
void __fastcall FUN_00763500(CDaoErrorInfo *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085cf88;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *(undefined ***)param_1 = CGalaxyP2P::vftable;
  *(undefined ***)(param_1 + 0x38) = CGalaxyP2P::vftable;
  local_8 = 0;
  FUN_00763800(uVar1);
  local_8 = 0xffffffff;
  CDaoErrorInfo::~CDaoErrorInfo(param_1);
  ExceptionList = local_10;
  return;
}

