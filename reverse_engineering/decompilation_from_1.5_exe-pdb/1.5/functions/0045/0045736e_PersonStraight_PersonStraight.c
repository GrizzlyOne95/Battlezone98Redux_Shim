/*
 * Entry: 0045736e
 * Name: PersonStraight::PersonStraight
 * Namespace: PersonStraight
 * Signature: PersonStraight * PersonStraight(PersonStraight * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonStraight * __thiscall
PersonStraight::PersonStraight(PersonStraight *this,Craft *param_1,GameObject *param_2)

{
  AiPath *pAVar1;
  undefined4 *puVar2;
  int iVar3;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 2;
  if (param_2 != (GameObject *)0x0) {
    pAVar1 = operator_new(0x1c);
    if (pAVar1 == (AiPath *)0x0) {
      pAVar1 = (AiPath *)0x0;
    }
    else {
      pAVar1 = AiPath::AiPath(pAVar1,(char *)0x0,2);
    }
    *(AiPath **)&this->field_0x44 = pAVar1;
    puVar2 = (undefined4 *)(**(code **)(param_1->_padding_ + 0xc))();
    **(undefined4 **)(*(int *)&this->field_0x44 + 8) = *puVar2;
    iVar3 = (**(code **)(param_1->_padding_ + 0xc))();
    *(undefined4 *)(*(int *)(*(int *)&this->field_0x44 + 8) + 4) = *(undefined4 *)(iVar3 + 8);
    puVar2 = (undefined4 *)(**(code **)(param_2->_padding_ + 0xc))();
    *(undefined4 *)(*(int *)(*(int *)&this->field_0x44 + 8) + 8) = *puVar2;
    iVar3 = (**(code **)(param_2->_padding_ + 0xc))();
    *(undefined4 *)(*(int *)(*(int *)&this->field_0x44 + 8) + 0xc) = *(undefined4 *)(iVar3 + 8);
    *(undefined4 *)(*(int *)&this->field_0x44 + 0x10) = 0;
    *(undefined4 *)&this->field_0x48 = 1;
  }
  return this;
}
