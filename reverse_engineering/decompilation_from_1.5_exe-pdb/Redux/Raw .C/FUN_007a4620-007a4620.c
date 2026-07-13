
undefined4 * __fastcall FUN_007a4620(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860384;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_Multiplayer_Refresh::vftable;
  pvVar1 = operator_new(0x144);
  local_8._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_007d1cc0("Middle_Overlay",0,0,0x44b40000,0x44870000,0x60,0,0);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_007d3f20(2);
  FUN_007d2870("esc_center.png");
  FUN_007d2110(local_20,0);
  FUN_007c79a0();
  ExceptionList = local_10;
  return param_1;
}

