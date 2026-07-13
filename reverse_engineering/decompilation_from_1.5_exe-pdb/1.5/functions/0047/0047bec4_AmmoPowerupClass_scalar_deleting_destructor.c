/*
 * Entry: 0047bec4
 * Name: AmmoPowerupClass::`scalar_deleting_destructor'
 * Namespace: AmmoPowerupClass
 * Signature: void * `scalar_deleting_destructor'(AmmoPowerupClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
AmmoPowerupClass::_scalar_deleting_destructor_(AmmoPowerupClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
