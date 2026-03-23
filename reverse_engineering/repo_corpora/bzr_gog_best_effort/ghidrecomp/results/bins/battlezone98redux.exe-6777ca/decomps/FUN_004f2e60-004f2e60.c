
CSliderCtrl * __fastcall FUN_004f2e60(CSliderCtrl *param_1)

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
  *(undefined ***)param_1 = InfoDisplay::vftable;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xfc) = 0;
  param_1[0x11c] = (CSliderCtrl)0x0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  CSliderCtrl::SetRange(param_1,0,0,uVar1);
  CSliderCtrl::SetRange(param_1,2,0,uVar1);
  CSliderCtrl::SetRange(param_1,1,0,uVar1);
  CSliderCtrl::SetRange(param_1,7,0,uVar1);
  ExceptionList = local_10;
  return param_1;
}

