/*
 * Entry: 004e37e2
 * Name: RKillMessage
 * Namespace: Global
 * Signature: void RKillMessage(int param_1, int param_2, char param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl RKillMessage(int param_1,int param_2,char param_3,int param_4)

{
  int iVar1;
  undefined4 *puVar2;
  char *pcVar3;
  char local_40;
  undefined4 local_3f [6];
  char local_24;
  undefined4 local_23 [6];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 < 1) {
    return;
  }
  local_24 = '\0';
  puVar2 = local_23;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  if (NetPlayer::netPlayerByTeam[param_1] == (NetPlayer *)0x0) {
    sprintf(&local_24,"Team %d",param_1);
  }
  else {
    strncpy(&local_24,NetPlayer::netPlayerByTeam[param_1]->playerName,0x18);
  }
  local_40 = '\0';
  puVar2 = local_3f;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  if (0 < param_2) {
    if (NetPlayer::netPlayerByTeam[param_2] == (NetPlayer *)0x0) {
      sprintf(&local_40,"Team %d",param_2);
    }
    else {
      strncpy(&local_40,NetPlayer::netPlayerByTeam[param_2]->playerName,0x18);
    }
  }
  if (param_3 == 'P') {
joined_r0x004e38f2:
    if (0 < param_2) {
      DisplayMessage("%s%s %s %s");
      return;
    }
  }
  else {
    if (param_3 != 'B') {
      if (param_3 == 'S') goto joined_r0x004e38f2;
      if (param_3 == 'E') {
        pcVar3 = "%s %s";
        goto LAB_004e396f;
      }
    }
    if (param_2 < 1) {
      pcVar3 = "%s%s";
LAB_004e396f:
      DisplayMessage(pcVar3);
      return;
    }
  }
  DisplayMessage("%s%s %s");
  return;
}
