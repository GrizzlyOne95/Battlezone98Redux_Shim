/*
 * Entry: 004706a1
 * Name: WingmanProcess::InitAttack
 * Namespace: WingmanProcess
 * Signature: void InitAttack(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::InitAttack(WingmanProcess *this)

{
  GameObject *pGVar1;
  AttackTask *pAVar2;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  pAVar2 = operator_new(0x144);
  if (pAVar2 == (AttackTask *)0x0) {
    pAVar2 = (AttackTask *)0x0;
  }
  else {
    pAVar2 = AttackTask::AttackTask(pAVar2,*(Craft **)&this->field_0x2c,pGVar1);
  }
  *(AttackTask **)&this->field_0x30 = pAVar2;
  return;
}
