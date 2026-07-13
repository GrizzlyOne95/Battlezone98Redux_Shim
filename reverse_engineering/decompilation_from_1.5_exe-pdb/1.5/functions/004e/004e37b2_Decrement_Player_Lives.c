/*
 * Entry: 004e37b2
 * Name: Decrement_Player_Lives
 * Namespace: Global
 * Signature: void Decrement_Player_Lives(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Decrement_Player_Lives(void)

{
  ushort uVar1;
  int local_8;
  
  uVar1 = Net_GetMyPlayerID();
  local_8 = Net::iLivesLeft;
  dpSetPlayerData(Net::dp,uVar1,0x13,&local_8,4,0);
  return;
}
