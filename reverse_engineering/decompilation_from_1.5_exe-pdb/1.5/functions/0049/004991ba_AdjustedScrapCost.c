/*
 * Entry: 004991ba
 * Name: AdjustedScrapCost
 * Namespace: Global
 * Signature: long AdjustedScrapCost(int param_1, GameObjectClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AdjustedScrapCost(int param_1,GameObjectClass *param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  
  lVar1 = GameObject::userTeamNumber;
  iVar3 = param_2->scrapCost;
  iVar2 = Net_IsNetGame();
  if ((iVar2 == 0) && (param_1 == lVar1)) {
    iVar2 = UserPref_noSalvageManagement();
    if (iVar2 == 0) {
      if (difficultySetting == 0) {
        iVar3 = iVar3 + -2;
      }
      else {
        if (difficultySetting != 1) {
          return iVar3;
        }
        iVar3 = iVar3 + -1;
      }
      if (-1 < iVar3) {
        return iVar3;
      }
    }
    iVar3 = 0;
  }
  return iVar3;
}
