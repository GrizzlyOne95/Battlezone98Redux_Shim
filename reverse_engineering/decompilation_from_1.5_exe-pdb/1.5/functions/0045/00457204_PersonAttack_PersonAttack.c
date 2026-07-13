/*
 * Entry: 00457204
 * Name: PersonAttack::PersonAttack
 * Namespace: PersonAttack
 * Signature: PersonAttack * PersonAttack(PersonAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonAttack * __thiscall PersonAttack::PersonAttack(PersonAttack *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
