/*
 * Entry: 005323a3
 * Name: Mortar::`scalar_deleting_destructor'
 * Namespace: Mortar
 * Signature: void * `scalar_deleting_destructor'(Mortar * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Mortar::_scalar_deleting_destructor_(Mortar *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Cannon::~Cannon((Cannon *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
