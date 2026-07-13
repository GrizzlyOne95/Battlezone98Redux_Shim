/*
 * Entry: 005317a1
 * Name: MagnetMineClass::`scalar_deleting_destructor'
 * Namespace: MagnetMineClass
 * Signature: void * `scalar_deleting_destructor'(MagnetMineClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MagnetMineClass::_scalar_deleting_destructor_(MagnetMineClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  MineClass::~MineClass((MineClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
