/*
 * Entry: 004e0eca
 * Name: NetPlayer::IWon
 * Namespace: NetPlayer
 * Signature: bool IWon(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl NetPlayer::IWon(void)

{
  int iVar1;
  byte local_5;
  
  local_5 = 1;
  iVar1 = dpEnumPlayers(Net::dp,0,dpEnumPlayerLivesCallback,&local_5,0);
  return (bool)(~-(iVar1 != 0) & local_5);
}
