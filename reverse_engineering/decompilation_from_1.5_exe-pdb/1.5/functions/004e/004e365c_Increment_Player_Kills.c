/*
 * Entry: 004e365c
 * Name: Increment_Player_Kills
 * Namespace: Global
 * Signature: void Increment_Player_Kills(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Increment_Player_Kills(void)

{
  ushort uVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  uVar1 = Net_GetMyPlayerID();
  local_c = 4;
  iVar2 = dpGetPlayerData(Net::dp,uVar1,0xf,&local_8,&local_c,0);
  if (((iVar2 == 0) && (local_c == 4)) && (local_8 + 0x1869eU < 0x30d3d)) {
    local_8 = local_8 + 1;
  }
  else {
    local_8 = 1;
  }
  dpSetPlayerData(Net::dp,uVar1,0xf,&local_8,4,0);
  return;
}
