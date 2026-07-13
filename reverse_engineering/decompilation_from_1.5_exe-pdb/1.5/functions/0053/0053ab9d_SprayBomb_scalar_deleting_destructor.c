/*
 * Entry: 0053ab9d
 * Name: SprayBomb::`scalar_deleting_destructor'
 * Namespace: SprayBomb
 * Signature: void * `scalar_deleting_destructor'(SprayBomb * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SprayBomb::_scalar_deleting_destructor_(SprayBomb *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Grenade::~Grenade((Grenade *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
