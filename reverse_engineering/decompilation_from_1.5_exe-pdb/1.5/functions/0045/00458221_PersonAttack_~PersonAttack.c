/*
 * Entry: 00458221
 * Name: PersonAttack::~PersonAttack
 * Namespace: PersonAttack
 * Signature: void ~PersonAttack(PersonAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonAttack::~PersonAttack(PersonAttack *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  if (*(AttackGroup **)&this->field_0x108 != (AttackGroup *)0x0) {
    AttackGroup::Leave(*(AttackGroup **)&this->field_0x108,*(GameObject **)&this->field_0x14);
  }
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
