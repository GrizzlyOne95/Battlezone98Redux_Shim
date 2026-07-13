/*
 * Entry: 00556e23
 * Name: CreateGameSession
 * Namespace: Global
 * Signature: int CreateGameSession(HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl CreateGameSession(HWND__ *param_1)

{
  HWND__ *in_ECX;
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  undefined1 local_168 [13];
  ushort local_15b;
  undefined2 local_157;
  undefined2 local_153;
  char local_151 [73];
  char local_108 [22];
  undefined1 local_f2 [6];
  undefined1 local_ec [228];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_ec;
  Creator = true;
  memset(local_168,0,0x5f);
  local_153 = 0x41;
  local_15b = Net::session_type;
  pcVar2 = local_151;
  pcVar3 = net_defaults.gamename;
  local_168[0] = 0x5f;
  strncpy(pcVar2,net_defaults.gamename,0x20);
  encrypt_password(local_151,pcVar2,pcVar3);
  local_157 = 2;
  if (bGameSetup == 0) {
    Net::Close();
    Net::myPlayerID = 0xfa01;
    dp_result = dpOpen(Net::dp,local_168,dpCreateGameOpenCallback);
    if (dp_result != 0) {
      pcVar2 = "Unable to create game";
      pcVar3 = local_108;
      for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
      memset(local_f2,0,0xea);
      read_text_label("multi_error","fail_create_game",local_108);
      do_error(in_ECX,local_108);
      return 0;
    }
  }
  return 1;
}
