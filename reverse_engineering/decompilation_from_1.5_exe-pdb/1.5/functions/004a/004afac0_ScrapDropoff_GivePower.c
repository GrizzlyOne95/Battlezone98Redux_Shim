/*
 * Entry: 004afac0
 * Name: ScrapDropoff::GivePower
 * Namespace: ScrapDropoff
 * Signature: bool GivePower(ScrapDropoff * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScrapDropoff::GivePower(ScrapDropoff *this,GameObject *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  if (((param_1 != (GameObject *)0x0) &&
      (iVar2 = (**(code **)param_1->_padding_)(), *(int *)(iVar2 + 0x20) == 0x53434156)) &&
     (bVar1 = GameObject::FriendP((GameObject *)this,param_1), bVar1)) {
    iVar2 = *(int *)&param_1[1].isCargo;
    Scavenger::UnloadScrap((Scavenger *)param_1,iVar2);
    iVar3 = Net_IsNetGame();
    if (iVar3 != 0) {
      iVar2 = iVar2 * 2;
    }
    Team::AddScrap(*(Team **)&this->field_0x170,iVar2);
    return true;
  }
  return false;
}
