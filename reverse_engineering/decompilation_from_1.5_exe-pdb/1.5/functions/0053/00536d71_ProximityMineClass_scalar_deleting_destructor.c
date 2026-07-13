/*
 * Entry: 00536d71
 * Name: ProximityMineClass::`scalar_deleting_destructor'
 * Namespace: ProximityMineClass
 * Signature: void * `scalar_deleting_destructor'(ProximityMineClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
ProximityMineClass::_scalar_deleting_destructor_(ProximityMineClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  MineClass::~MineClass((MineClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
