/*
 * Entry: 0044e300
 * Name: OffensiveProcess::InitSubAttack
 * Namespace: OffensiveProcess
 * Signature: void InitSubAttack(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OffensiveProcess::InitSubAttack(OffensiveProcess *this)

{
  GameObject *pGVar1;
  AttackTask *pAVar2;
  
  pGVar1 = GameObjectHandle::GetObj(this->_padding_);
  pAVar2 = operator_new(0x144);
  if (pAVar2 == (AttackTask *)0x0) {
    pAVar2 = (AttackTask *)0x0;
  }
  else {
    pAVar2 = AttackTask::AttackTask(pAVar2,(Craft *)this->_padding_,pGVar1);
  }
  this->_padding_ = (int)pAVar2;
  return;
}
