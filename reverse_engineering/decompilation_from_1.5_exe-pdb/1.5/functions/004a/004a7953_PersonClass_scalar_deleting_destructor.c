/*
 * Entry: 004a7953
 * Name: PersonClass::`scalar_deleting_destructor'
 * Namespace: PersonClass
 * Signature: void * `scalar_deleting_destructor'(PersonClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonClass::_scalar_deleting_destructor_(PersonClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  CraftClass::~CraftClass((CraftClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
