/*
 * Entry: 004e3738
 * Name: Increment_Player_TimeInZone
 * Namespace: Global
 * Signature: void Increment_Player_TimeInZone(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Increment_Player_TimeInZone(float param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 local_c;
  float local_8;
  
  uVar1 = Net_GetMyPlayerID();
  local_c = 4;
  iVar2 = dpGetPlayerData(Net::dp,uVar1,0x12,&local_8,&local_c,0);
  if (((iVar2 == 0) && (0.0 < local_8)) && (local_8 < 99999.9)) {
    param_1 = local_8 + param_1;
  }
  local_8 = param_1;
  dpSetPlayerData(Net::dp,uVar1,0x12,&local_8,4,0);
  return;
}
