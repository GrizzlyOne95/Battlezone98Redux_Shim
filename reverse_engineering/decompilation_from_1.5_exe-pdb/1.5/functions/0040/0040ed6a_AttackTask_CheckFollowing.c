/*
 * Entry: 0040ed6a
 * Name: AttackTask::CheckFollowing
 * Namespace: AttackTask
 * Signature: bool CheckFollowing(AttackTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AttackTask::CheckFollowing(AttackTask *this)

{
  AiMission *pAVar1;
  int iVar2;
  GameObject *pGVar3;
  
  pGVar3 = GameObjectHandle::GetObj(this->_padding_);
  if (((pGVar3 == (GameObject *)0x0) || (pGVar3->aiProcess == (AiProcess *)0x0)) ||
     (pAVar1 = pGVar3->aiProcess[2].fMission, pAVar1 == (AiMission *)0x0)) {
    this->_padding_ = 1;
    return true;
  }
  iVar2 = (pAVar1->processes)._padding_;
  if ((iVar2 != 5) && ((iVar2 < 7 || (10 < iVar2)))) {
    return false;
  }
  this->_padding_ = this->_padding_;
  this->_padding_ = 2;
  return true;
}
