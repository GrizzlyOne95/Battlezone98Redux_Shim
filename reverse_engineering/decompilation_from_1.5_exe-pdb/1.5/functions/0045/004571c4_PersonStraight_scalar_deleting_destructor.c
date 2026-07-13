/*
 * Entry: 004571c4
 * Name: PersonStraight::`scalar_deleting_destructor'
 * Namespace: PersonStraight
 * Signature: void * `scalar_deleting_destructor'(PersonStraight * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonStraight::_scalar_deleting_destructor_(PersonStraight *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
