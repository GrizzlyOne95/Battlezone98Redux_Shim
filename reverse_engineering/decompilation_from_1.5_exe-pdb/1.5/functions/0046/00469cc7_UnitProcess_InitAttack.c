/*
 * Entry: 00469cc7
 * Name: UnitProcess::InitAttack
 * Namespace: UnitProcess
 * Signature: void InitAttack(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::InitAttack(UnitProcess *this)

{
  GameObject *pGVar1;
  AttackTask *pAVar2;
  
  pGVar1 = GameObjectHandle::GetObj(this->whoHandle);
  pAVar2 = operator_new(0x144);
  if (pAVar2 == (AttackTask *)0x0) {
    pAVar2 = (AttackTask *)0x0;
  }
  else {
    pAVar2 = AttackTask::AttackTask(pAVar2,this->me,pGVar1);
  }
  this->task = (AiTask *)pAVar2;
  return;
}
