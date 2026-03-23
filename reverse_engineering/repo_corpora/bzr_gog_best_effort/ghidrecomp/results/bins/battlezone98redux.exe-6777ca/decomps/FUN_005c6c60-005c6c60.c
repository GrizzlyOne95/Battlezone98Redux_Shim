
void __fastcall FUN_005c6c60(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0068bed0("Scrap");
  *(undefined4 *)(param_1 + 8) = uVar1;
  DAT_00918294 = FUN_0068bed0("scrap_panel");
  DAT_00918288 = FUN_0068bed0("sscrap_panel");
  uVar1 = FUN_0068bed0("Pilot");
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  DAT_00918274 = FUN_0068bed0("pilot_panel");
  DAT_00918298 = FUN_0068bed0("spilot_panel");
  FUN_005c6cf0();
  return;
}

