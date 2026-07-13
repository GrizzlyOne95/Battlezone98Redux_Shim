/*
 * Entry: 00495371
 * Name: GameObject::Cleanup
 * Namespace: GameObject
 * Signature: void Cleanup(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::Cleanup(GameObject *this)

{
  int iVar1;
  
  if ((this->teamList != (Team *)0x0) && (this->teamSlot != -1)) {
    Team::SetSlot(this->teamList,this->teamSlot,(GameObject *)0x0);
  }
  this->teamList = (Team *)0x0;
  this->teamNumber = -1;
  this->teamSlot = -1;
  iVar1 = GetHandle(this);
  ControlPanel::FlushLists(&controlPanel,iVar1);
  return;
}
