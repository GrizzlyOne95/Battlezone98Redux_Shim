/*
 * Entry: 00499205
 * Name: AdjustedPilotCost
 * Namespace: Global
 * Signature: long AdjustedPilotCost(int param_1, GameObjectClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AdjustedPilotCost(int param_1,GameObjectClass *param_2)

{
  long lVar1;
  int iVar2;
  uint uVar3;
  
  lVar1 = GameObject::userTeamNumber;
  uVar3 = param_2->pilotCost;
  iVar2 = Net_IsNetGame();
  if ((iVar2 == 0) && (param_1 == lVar1)) {
    iVar2 = UserPref_noSalvageManagement();
    uVar3 = ~-(uint)(iVar2 != 0) & uVar3;
  }
  return uVar3;
}
