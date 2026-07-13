/*
 * Entry: 00457175
 * Name: PersonGlide::`scalar_deleting_destructor'
 * Namespace: PersonGlide
 * Signature: void * `scalar_deleting_destructor'(PersonGlide * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonGlide::_scalar_deleting_destructor_(PersonGlide *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
