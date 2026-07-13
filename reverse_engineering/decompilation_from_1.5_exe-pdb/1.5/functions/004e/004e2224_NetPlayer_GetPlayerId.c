/*
 * Entry: 004e2224
 * Name: NetPlayer_GetPlayerId
 * Namespace: Global
 * Signature: ushort NetPlayer_GetPlayerId(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl NetPlayer_GetPlayerId(char *param_1)

{
  NetPlayer *pNVar1;
  
  pNVar1 = NetPlayer::Find(param_1);
  if (pNVar1 != (NetPlayer *)0x0) {
    return pNVar1->playerId;
  }
  return 0;
}
