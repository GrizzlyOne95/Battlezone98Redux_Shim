/*
 * Entry: 0045bb68
 * Name: SAVProcess::InitAttack
 * Namespace: SAVProcess
 * Signature: void InitAttack(SAVProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVProcess::InitAttack(SAVProcess *this)

{
  GameObject *pGVar1;
  int iVar2;
  SAVAttackVehicleTask *pSVar3;
  SAVAttackPersonTask *this_00;
  
  pGVar1 = GameObjectHandle::GetObj(*(int *)&this->field_0x34);
  if (pGVar1 == (GameObject *)0x0) {
LAB_0045bba4:
    this_00 = operator_new(0x138);
    if (this_00 != (SAVAttackPersonTask *)0x0) {
      pSVar3 = (SAVAttackVehicleTask *)
               SAVAttackPersonTask::SAVAttackPersonTask(this_00,*(Craft **)&this->field_0x2c,pGVar1)
      ;
      goto LAB_0045bbc2;
    }
  }
  else {
    iVar2 = (**(code **)pGVar1->_padding_)();
    if (*(int *)(iVar2 + 0x28) == 4) goto LAB_0045bba4;
    pSVar3 = operator_new(0x138);
    if (pSVar3 != (SAVAttackVehicleTask *)0x0) {
      pSVar3 = SAVAttackVehicleTask::SAVAttackVehicleTask
                         (pSVar3,*(Craft **)&this->field_0x2c,pGVar1);
      goto LAB_0045bbc2;
    }
  }
  pSVar3 = (SAVAttackVehicleTask *)0x0;
LAB_0045bbc2:
  *(SAVAttackVehicleTask **)&this->field_0x30 = pSVar3;
  return;
}
