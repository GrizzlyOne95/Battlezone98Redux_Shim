/*
 * Entry: 004e36cd
 * Name: Increment_Player_Deaths
 * Namespace: Global
 * Signature: void Increment_Player_Deaths(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Increment_Player_Deaths(void)

{
  ushort uVar1;
  int iVar2;
  undefined4 local_c;
  int local_8;
  
  uVar1 = Net_GetMyPlayerID();
  local_c = 4;
  iVar2 = dpGetPlayerData(Net::dp,uVar1,0x10,&local_8,&local_c,0);
  if ((iVar2 == 0) && (local_8 + 0x1869eU < 0x30d3d)) {
    local_8 = local_8 + 1;
  }
  else {
    local_8 = 1;
  }
  dpSetPlayerData(Net::dp,uVar1,0x10,&local_8,4,0);
  return;
}
