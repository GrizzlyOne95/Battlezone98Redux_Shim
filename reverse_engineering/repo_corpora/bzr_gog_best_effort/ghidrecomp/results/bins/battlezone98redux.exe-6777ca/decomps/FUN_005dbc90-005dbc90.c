
CSliderCtrl * __fastcall FUN_005dbc90(CSliderCtrl *param_1)

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
  *(undefined ***)param_1 = StatusDisplay::vftable;
  CSliderCtrl::SetRange(param_1,0,1,uVar1);
  CSliderCtrl::SetRange(param_1,2,1,uVar1);
  CSliderCtrl::SetRange(param_1,1,1,uVar1);
  CSliderCtrl::SetRange(param_1,7,1,uVar1);
  ExceptionList = local_10;
  return param_1;
}

