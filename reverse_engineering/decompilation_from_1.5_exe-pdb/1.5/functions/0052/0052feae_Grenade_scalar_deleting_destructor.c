/*
 * Entry: 0052feae
 * Name: Grenade::`scalar_deleting_destructor'
 * Namespace: Grenade
 * Signature: void * `scalar_deleting_destructor'(Grenade * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Grenade::_scalar_deleting_destructor_(Grenade *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Rocket::~Rocket((Rocket *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
