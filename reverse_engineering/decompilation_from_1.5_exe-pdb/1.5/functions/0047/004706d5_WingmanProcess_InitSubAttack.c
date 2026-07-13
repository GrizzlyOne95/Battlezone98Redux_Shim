/*
 * Entry: 004706d5
 * Name: WingmanProcess::InitSubAttack
 * Namespace: WingmanProcess
 * Signature: void InitSubAttack(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanProcess::InitSubAttack(WingmanProcess *this)

{
  GameObject *pGVar1;
  WingmanBlastAttack *this_00;
  AttackTask *pAVar2;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  if (*(int *)&this->field_0x20 == 8) {
    this_00 = operator_new(0x138);
    if (this_00 != (WingmanBlastAttack *)0x0) {
      pAVar2 = (AttackTask *)
               WingmanBlastAttack::WingmanBlastAttack(this_00,*(Craft **)&this->field_0x2c,pGVar1);
      goto LAB_00470724;
    }
  }
  else {
    pAVar2 = operator_new(0x144);
    if (pAVar2 != (AttackTask *)0x0) {
      pAVar2 = AttackTask::AttackTask(pAVar2,*(Craft **)&this->field_0x2c,pGVar1);
      goto LAB_00470724;
    }
  }
  pAVar2 = (AttackTask *)0x0;
LAB_00470724:
  *(AttackTask **)&this->field_0x30 = pAVar2;
  return;
}
