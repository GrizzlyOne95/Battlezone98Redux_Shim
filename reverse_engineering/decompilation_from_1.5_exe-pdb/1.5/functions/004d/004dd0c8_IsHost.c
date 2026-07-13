/*
 * Entry: 004dd0c8
 * Name: IsHost
 * Namespace: Global
 * Signature: bool IsHost(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsHost(ushort param_1)

{
  int iVar1;
  ushort unaff_SI;
  uint local_8;
  
  local_8 = (uint)unaff_SI;
  done = 0;
  iVar1 = dpEnumPlayers(Net::dp,0,dpEnumPlayersCallbackIsHost,&local_8,0);
  if (iVar1 == 0) {
    return (ushort)local_8 == unaff_SI;
  }
  return false;
}
