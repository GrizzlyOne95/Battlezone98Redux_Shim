/*
 * Entry: 00484d5b
 * Name: CommTower::Init
 * Namespace: CommTower
 * Signature: void Init(CommTower * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CommTower::Init(CommTower *this,int param_1)

{
  GameObject *pGVar1;
  
  Building::Init((Building *)this,param_1);
  if (GameObject::userTeamNumber == this->_padding_) {
    pGVar1 = GameObjectHandle::GetObj(this->powerSource);
    if (pGVar1 != (GameObject *)0x0) {
      controlPanel.satelliteEnabled = controlPanel.satelliteEnabled + 1;
    }
  }
  return;
}
