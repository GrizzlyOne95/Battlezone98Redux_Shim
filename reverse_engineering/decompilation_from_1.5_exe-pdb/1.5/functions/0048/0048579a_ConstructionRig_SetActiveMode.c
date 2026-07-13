/*
 * Entry: 0048579a
 * Name: ConstructionRig::SetActiveMode
 * Namespace: ConstructionRig
 * Signature: bool SetActiveMode(ConstructionRig * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ConstructionRig::SetActiveMode(ConstructionRig *this,int param_1)

{
  bool bVar1;
  int iVar2;
  
  if (param_1 < 0x19) {
    bVar1 = Producer::SetActiveMode((Producer *)this,param_1);
  }
  else {
    GameObject::SetCommand((GameObject *)this,CMD_BUILD,param_1);
    this->dropClass = (GameObjectClass *)param_1;
    iVar2 = ModeList::FindMode((ModeList *)&this->_padding_,param_1);
    this->_padding_ = iVar2;
    bVar1 = false;
  }
  return bVar1;
}
