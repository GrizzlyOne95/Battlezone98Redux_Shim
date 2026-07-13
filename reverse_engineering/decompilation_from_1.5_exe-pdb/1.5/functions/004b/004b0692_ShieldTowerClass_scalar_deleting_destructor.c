/*
 * Entry: 004b0692
 * Name: ShieldTowerClass::`scalar_deleting_destructor'
 * Namespace: ShieldTowerClass
 * Signature: void * `scalar_deleting_destructor'(ShieldTowerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ShieldTowerClass::_scalar_deleting_destructor_(ShieldTowerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
