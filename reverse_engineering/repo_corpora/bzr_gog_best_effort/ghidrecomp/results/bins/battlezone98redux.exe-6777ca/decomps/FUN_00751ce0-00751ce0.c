
void __fastcall FUN_00751ce0(undefined4 *param_1)

{
  *param_1 = CCallbackImpl<32>::vftable;
  if ((*(byte *)(param_1 + 1) & 1) != 0) {
    SteamAPI_UnregisterCallback(param_1);
  }
  return;
}

