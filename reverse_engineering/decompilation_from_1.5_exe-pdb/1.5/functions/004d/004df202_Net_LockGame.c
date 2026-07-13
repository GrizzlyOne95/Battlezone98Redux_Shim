/*
 * Entry: 004df202
 * Name: Net_LockGame
 * Namespace: Global
 * Signature: void Net_LockGame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net_LockGame(void)

{
  undefined2 local_14 [6];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14[0] = 0x534c;
  Net::Send(Net::dp,Net::myPlayerID,0,1,local_14,2);
  dpEnableNewPlayers(Net::dp,0);
  return;
}
