/*
 * Entry: 004de944
 * Name: dpCreatePlayerCallback
 * Namespace: Global
 * Signature: void dpCreatePlayerCallback(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpCreatePlayerCallback(ushort param_1,char *param_2,long param_3,void *param_4)

{
  Net::SetMyPlayerId(param_4,param_1);
  *(undefined4 *)param_4 = 4;
  if (Net::hosting != false) {
    Net::Team = NetPlayer::FindUnusedTeam();
    NetPlayer::AddPlayer(param_1,param_2,Net::Team);
    dpidCurHost = param_1;
  }
  return;
}
