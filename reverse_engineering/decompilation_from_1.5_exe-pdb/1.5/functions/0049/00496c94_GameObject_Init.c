/*
 * Entry: 00496c94
 * Name: GameObject::Init
 * Namespace: GameObject
 * Signature: void Init(GameObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::Init(GameObject *this,int param_1)

{
  int iVar1;
  Team *this_00;
  int iVar2;
  
  this->obj->flags = this->obj->flags & 0xfff0ffff | param_1 << 0x10;
  this->teamNumber = param_1;
  this_00 = Team::GetTeam(param_1);
  this->teamList = this_00;
  if ((this == userObject) || ((char)this->_padding_ != '\0')) {
    this->teamSlot = 0;
  }
  else {
    iVar2 = this->objClass->categoryMin;
    if ((iVar2 < 0) || (iVar1 = this->objClass->categoryMax, iVar1 < 0)) {
      this->teamSlot = -1;
    }
    else {
      iVar2 = Team::FirstEmptySlot(this_00,iVar2,iVar1);
      this->teamSlot = iVar2;
    }
  }
  if ((this->teamList != (Team *)0x0) && (this->teamSlot != -1)) {
    Team::SetSlot(this->teamList,this->teamSlot,this);
  }
  AssignColor(this);
  (**(code **)(this->_padding_ + 0x58))();
  (this->modeList).activeSlot = 0;
  return;
}
