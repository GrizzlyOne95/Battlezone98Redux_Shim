/*
 * Entry: 00460ad2
 * Name: GetTeamSlot
 * Namespace: Global
 * Signature: int GetTeamSlot(TEAM_SLOT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetTeamSlot(TEAM_SLOT param_1)

{
  int iVar1;
  
  iVar1 = GetTeamSlot(param_1,GameObject::userTeamNumber);
  return iVar1;
}
