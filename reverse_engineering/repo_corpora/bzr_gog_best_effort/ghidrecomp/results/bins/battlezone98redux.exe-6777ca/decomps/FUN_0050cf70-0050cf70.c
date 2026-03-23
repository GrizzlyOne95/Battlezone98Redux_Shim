
CSliderCtrl * __fastcall FUN_0050cf70(CSliderCtrl *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084abae;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004b6260();
  local_8 = 0;
  *(undefined ***)param_1 = MapRadar::vftable;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x18));
  local_8._0_1_ = 1;
  Concurrency::details::QuickBitSet::QuickBitSet((QuickBitSet *)(param_1 + 0x20));
  local_8 = CONCAT31(local_8._1_3_,2);
  CSliderCtrl::SetRange(param_1,0,2,uVar1);
  CSliderCtrl::SetRange(param_1,2,2,uVar1);
  CSliderCtrl::SetRange(param_1,1,2,uVar1);
  CSliderCtrl::SetRange(param_1,7,2,uVar1);
  CSliderCtrl::SetRange(param_1,3,2,uVar1);
  ExceptionList = local_10;
  return param_1;
}

