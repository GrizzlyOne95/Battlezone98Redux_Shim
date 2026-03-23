
void __thiscall
FUN_00752250(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  if (*(int *)(param_1 + 0x10) != 0 || *(int *)(param_1 + 0x14) != 0) {
    SteamAPI_UnregisterCallResult
              (param_1,*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
  }
  *(int *)(param_1 + 0x10) = param_2;
  *(int *)(param_1 + 0x14) = param_3;
  *(undefined4 *)(param_1 + 0x18) = param_4;
  *(undefined4 *)(param_1 + 0x1c) = param_5;
  if (param_2 != 0 || param_3 != 0) {
    SteamAPI_RegisterCallResult(param_1,param_2,param_3);
  }
  return;
}

