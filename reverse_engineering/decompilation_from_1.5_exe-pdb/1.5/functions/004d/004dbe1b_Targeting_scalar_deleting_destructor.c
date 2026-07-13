/*
 * Entry: 004dbe1b
 * Name: Targeting::`scalar_deleting_destructor'
 * Namespace: Targeting
 * Signature: void * `scalar_deleting_destructor'(Targeting * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Targeting::_scalar_deleting_destructor_(Targeting *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
