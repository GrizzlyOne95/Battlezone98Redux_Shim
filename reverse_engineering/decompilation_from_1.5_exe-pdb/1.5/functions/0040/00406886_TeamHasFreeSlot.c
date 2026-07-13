/*
 * Entry: 00406886
 * Name: TeamHasFreeSlot
 * Namespace: Global
 * Signature: bool TeamHasFreeSlot(Team * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl TeamHasFreeSlot(Team *param_1,GameObject *param_2)

{
  int iVar1;
  int iVar2;
  
  if ((GameObject::userTeamList == param_1) &&
     ((param_2->teamList != param_1 || (param_2->teamSlot == -1)))) {
    iVar1 = (**(code **)param_2->_padding_)();
    iVar1 = *(int *)(iVar1 + 0x148);
    iVar2 = (**(code **)param_2->_padding_)();
    iVar1 = Team::FirstEmptySlot(param_1,*(int *)(iVar2 + 0x144),iVar1);
    return iVar1 != -1;
  }
  return true;
}
