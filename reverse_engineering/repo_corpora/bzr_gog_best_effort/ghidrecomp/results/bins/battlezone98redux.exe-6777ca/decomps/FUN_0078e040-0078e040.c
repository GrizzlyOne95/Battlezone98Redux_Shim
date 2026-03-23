
void __fastcall FUN_0078e040(int param_1)

{
  undefined4 uVar1;
  void *pvVar2;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0078c4a0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  *(undefined4 *)(param_1 + 0x148) = 1;
  uVar1 = FUN_00822e60();
  *(undefined4 *)(param_1 + 0x14c) = uVar1;
  pvVar2 = operator_new(0x144);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_1c = 0;
  }
  else {
    local_1c = FUN_007d1cc0("Splash_Overlay2",0,0,0,0,0x201,0,0);
  }
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x154) = local_1c;
  FUN_007d3f20(1);
  FUN_007d2870(PTR_s_RebellionLogoScreen_v2_png_008f0678);
  FUN_007d2110();
  FUN_0078c4b0(0x408f400000000000,FUN_0078dfa0);
  ExceptionList = local_10;
  return;
}

