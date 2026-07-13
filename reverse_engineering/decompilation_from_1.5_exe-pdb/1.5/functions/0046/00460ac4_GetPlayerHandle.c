/*
 * Entry: 00460ac4
 * Name: GetPlayerHandle
 * Namespace: Global
 * Signature: int GetPlayerHandle(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetPlayerHandle(int param_1)

{
  int iVar1;
  
  iVar1 = GetTeamSlot(TEAM_SLOT_PLAYER,param_1);
  return iVar1;
}
