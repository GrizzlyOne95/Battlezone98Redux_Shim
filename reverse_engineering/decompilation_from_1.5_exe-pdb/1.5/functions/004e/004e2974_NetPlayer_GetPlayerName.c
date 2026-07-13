/*
 * Entry: 004e2974
 * Name: NetPlayer_GetPlayerName
 * Namespace: Global
 * Signature: char * NetPlayer_GetPlayerName(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl NetPlayer_GetPlayerName(ushort param_1)

{
  NetPlayer *pNVar1;
  
  pNVar1 = NetPlayer::Find(param_1);
  if (pNVar1 != (NetPlayer *)0x0) {
    return pNVar1->playerName;
  }
  return (char *)0x0;
}
