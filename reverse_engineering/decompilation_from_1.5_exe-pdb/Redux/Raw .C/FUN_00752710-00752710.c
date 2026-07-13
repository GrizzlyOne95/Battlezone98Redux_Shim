
void __fastcall FUN_00752710(int param_1)

{
  if (*(int *)(param_1 + 0x10) != 0 || *(int *)(param_1 + 0x14) != 0) {
    SteamAPI_UnregisterCallResult
              (param_1,*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x10) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
  }
  return;
}

