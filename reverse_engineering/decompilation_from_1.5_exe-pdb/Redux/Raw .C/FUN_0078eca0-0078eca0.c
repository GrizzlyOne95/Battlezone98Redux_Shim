
void __fastcall FUN_0078eca0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085e6c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_MainScreen::vftable;
  local_8 = 0;
  if (*(char *)(param_1 + 0x51) != '\0') {
    FUN_0078c4a0(uVar1);
    FUN_00623ff0();
  }
  FUN_0078cb40();
  DAT_0094551c = 0;
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

