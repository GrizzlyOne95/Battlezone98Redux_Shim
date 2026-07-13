/*
 * Entry: 00495468
 * Name: GameObject::SetAsUser
 * Namespace: GameObject
 * Signature: void SetAsUser(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetAsUser(GameObject *this)

{
  AiProcess *pAVar1;
  GameObject *pGVar2;
  UserProcess *this_00;
  AiMission *pAVar3;
  
  pAVar1 = this->aiProcess;
  if (pAVar1 != (AiProcess *)0x0) {
    (**(code **)pAVar1->_padding_)(1);
    this->aiProcess = (AiProcess *)0x0;
  }
  (**(code **)(this->_padding_ + 8))();
  pGVar2 = userObject;
  Set_User_Entity(this->ent);
  userObject = this;
  if (pGVar2 != (GameObject *)0x0) {
    (**(code **)(pGVar2->_padding_ + 0x10))();
  }
  (**(code **)(this->_padding_ + 4))(userTeamNumber);
  this_00 = ::operator_new(0x70);
  if (this_00 != (UserProcess *)0x0) {
    pAVar3 = AiMission::GetCurrent();
    UserProcess::UserProcess(this_00,pAVar3,this);
  }
  return;
}
