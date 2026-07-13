/*
 * Entry: 004dc4b6
 * Name: allie_cb
 * Namespace: Global
 * Signature: int allie_cb(void * * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl allie_cb(void **param_1,char *param_2)

{
  int iVar1;
  char *pcVar2;
  
  if (param_2 == (char *)0x0) {
    iVar1 = -1;
  }
  else {
    iVar1 = atoi(param_2);
  }
  if (iVar1 - 1U < 0xf) {
    if (A == 0) {
      send_ally(iVar1,0);
      GameObject_UnSetUserTeamAlly(iVar1);
      pcVar2 = "UnAlly with %d";
    }
    else {
      send_ally(iVar1,1);
      GameObject_SetUserTeamAlly(iVar1);
      pcVar2 = "Ally with %d";
    }
    Net_BroadCastMessage(pcVar2);
  }
  TextInput_ShowRegion(allie_entry,0);
  TextInput_AllowInput(allie_entry,0);
  return 1;
}
