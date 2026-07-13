/*
 * Entry: 0040bb45
 * Name: APCAttack::APCAttack
 * Namespace: APCAttack
 * Signature: APCAttack * APCAttack(APCAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

APCAttack * __thiscall APCAttack::APCAttack(APCAttack *this)

{
  UnitTask::UnitTask((UnitTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
