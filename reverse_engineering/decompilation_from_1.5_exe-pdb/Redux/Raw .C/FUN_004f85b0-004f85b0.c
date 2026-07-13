
CSliderCtrl * __fastcall FUN_004f85b0(CSliderCtrl *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008493d8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004b6260();
  local_8 = 0;
  *(undefined ***)param_1 = LauncherInterface::vftable;
  CSliderCtrl::SetRange(param_1,0,5,uVar1);
  CSliderCtrl::SetRange(param_1,2,5,uVar1);
  CSliderCtrl::SetRange(param_1,1,5,uVar1);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  ExceptionList = local_10;
  return param_1;
}

