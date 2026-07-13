/*
 * Entry: 00484d8e
 * Name: CommTower::Cleanup
 * Namespace: CommTower
 * Signature: void Cleanup(CommTower * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CommTower::Cleanup(CommTower *this)

{
  GameObject *pGVar1;
  
  if (GameObject::userTeamNumber == this->_padding_) {
    pGVar1 = GameObjectHandle::GetObj(this->powerSource);
    if (pGVar1 != (GameObject *)0x0) {
      controlPanel.satelliteEnabled = controlPanel.satelliteEnabled + -1;
    }
  }
  Building::Cleanup((Building *)this);
  return;
}
