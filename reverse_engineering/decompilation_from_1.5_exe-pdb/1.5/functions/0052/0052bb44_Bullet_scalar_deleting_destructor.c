/*
 * Entry: 0052bb44
 * Name: Bullet::`scalar_deleting_destructor'
 * Namespace: Bullet
 * Signature: void * `scalar_deleting_destructor'(Bullet * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Bullet::_scalar_deleting_destructor_(Bullet *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  Ordnance::~Ordnance((Ordnance *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
