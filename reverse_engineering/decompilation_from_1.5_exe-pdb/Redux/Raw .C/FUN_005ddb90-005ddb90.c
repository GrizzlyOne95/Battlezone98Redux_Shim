
CSliderCtrl * __fastcall FUN_005ddb90(CSliderCtrl *param_1)

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
  *(undefined ***)param_1 = TargetCam::vftable;
  CSliderCtrl::SetRange(param_1,0,0,uVar1);
  CSliderCtrl::SetRange(param_1,2,0,uVar1);
  CSliderCtrl::SetRange(param_1,1,0,uVar1);
  CSliderCtrl::SetRange(param_1,7,0,uVar1);
  ExceptionList = local_10;
  return param_1;
}

