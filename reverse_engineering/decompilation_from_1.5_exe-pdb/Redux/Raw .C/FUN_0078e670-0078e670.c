
undefined4 * __fastcall FUN_0078e670(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ec54;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007d0fa0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = cUI_MainScreen::vftable;
  param_1[0x52] = 0;
  param_1[0x54] = 0;
  param_1[0x55] = 0;
  param_1[0x56] = 0;
  param_1[0x57] = 0;
  param_1[0x58] = 0;
  param_1[0x59] = 0;
  param_1[0x5a] = 0;
  param_1[0x5b] = 0;
  param_1[0x5c] = 0;
  param_1[0x5d] = 0;
  param_1[0x5e] = 0;
  *(undefined1 *)(param_1 + 0x51) = 0;
  DAT_0094551c = param_1;
  if ((DAT_008e8c7e == '\0') || (DAT_008eaab8 == 0)) {
    FUN_006240f0();
    FUN_0078d000(1);
  }
  else {
    FUN_00623eb0();
    FUN_007d2870(PTR_s_RebellionLogoScreen_png_008f0674);
    FUN_007d22b0();
    pvVar1 = operator_new(0x144);
    local_8._0_1_ = 1;
    if (pvVar1 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_007d1cc0("Splash_Overlay1",0,0,0,0,0x201,0,0);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    param_1[0x54] = local_1c;
    FUN_007d3f20(2);
    FUN_007d2870(PTR_s_RebellionLogoScreen_png_008f0674);
    FUN_007d2110();
    *(undefined1 *)(param_1 + 0x51) = 1;
    FUN_0078c4b0(0x4097700000000000,FUN_0078df80);
  }
  ExceptionList = local_10;
  return param_1;
}

