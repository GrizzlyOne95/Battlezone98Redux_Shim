
void __thiscall FUN_007588f0(int param_1,int param_2,int param_3)

{
  if ((param_2 != 0) && (param_3 != 0)) {
    if ((*(byte *)(param_1 + 4) & 1) != 0) {
      FUN_006ab280();
    }
    *(int *)(param_1 + 0xc) = param_2;
    *(int *)(param_1 + 0x10) = param_3;
    SteamAPI_RegisterCallback(param_1,0x3ed);
  }
  return;
}

