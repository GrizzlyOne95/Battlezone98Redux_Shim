/*
 * Entry: 0052b68c
 * Name: BounceBomb::`scalar_deleting_destructor'
 * Namespace: BounceBomb
 * Signature: void * `scalar_deleting_destructor'(BounceBomb * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BounceBomb::_scalar_deleting_destructor_(BounceBomb *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Grenade::~Grenade((Grenade *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
