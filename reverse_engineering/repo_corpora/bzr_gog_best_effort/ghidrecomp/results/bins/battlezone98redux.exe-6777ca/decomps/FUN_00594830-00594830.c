
CSliderCtrl * __fastcall FUN_00594830(CSliderCtrl *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c038;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_005948f0();
  local_8 = 0;
  *(undefined ***)param_1 = PathDisplay::vftable;
  CSliderCtrl::SetRange(param_1,9,-1,uVar1);
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x80) = 0;
  ExceptionList = local_10;
  return param_1;
}

