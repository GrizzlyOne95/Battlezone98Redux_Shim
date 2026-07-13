/*
 * Entry: 00539b58
 * Name: SniperGun::`scalar_deleting_destructor'
 * Namespace: SniperGun
 * Signature: void * `scalar_deleting_destructor'(SniperGun * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SniperGun::_scalar_deleting_destructor_(SniperGun *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Cannon::~Cannon((Cannon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
