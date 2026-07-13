/*
 * Entry: 00467a4c
 * Name: TurretAttack::CheckFollowing
 * Namespace: TurretAttack
 * Signature: bool CheckFollowing(TurretAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretAttack::CheckFollowing(TurretAttack *this)

{
  int iVar1;
  GameObject *pGVar2;
  
  pGVar2 = GameObjectHandle::GetObj(this->_padding_);
  if (pGVar2 == (GameObject *)0x0) {
    this->_padding_ = 1;
    return true;
  }
  iVar1 = ((pGVar2->aiProcess[2].fMission)->processes)._padding_;
  if ((iVar1 != 5) && (iVar1 != 8)) {
    return false;
  }
  this->_padding_ = this->_padding_;
  this->_padding_ = 2;
  return true;
}
