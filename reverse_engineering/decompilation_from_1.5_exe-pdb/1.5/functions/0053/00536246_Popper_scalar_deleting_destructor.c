/*
 * Entry: 00536246
 * Name: Popper::`scalar_deleting_destructor'
 * Namespace: Popper
 * Signature: void * `scalar_deleting_destructor'(Popper * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Popper::_scalar_deleting_destructor_(Popper *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Grenade::~Grenade((Grenade *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
