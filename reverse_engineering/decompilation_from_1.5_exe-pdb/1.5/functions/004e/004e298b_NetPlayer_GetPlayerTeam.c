/*
 * Entry: 004e298b
 * Name: NetPlayer_GetPlayerTeam
 * Namespace: Global
 * Signature: int NetPlayer_GetPlayerTeam(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl NetPlayer_GetPlayerTeam(ushort param_1)

{
  NetPlayer *pNVar1;
  
  pNVar1 = NetPlayer::Find(param_1);
  if (pNVar1 != (NetPlayer *)0x0) {
    return (uint)pNVar1->bTeamNumber;
  }
  return 0;
}
