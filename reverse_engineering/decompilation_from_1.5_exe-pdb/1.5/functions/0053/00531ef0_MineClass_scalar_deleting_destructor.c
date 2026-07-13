/*
 * Entry: 00531ef0
 * Name: MineClass::`scalar_deleting_destructor'
 * Namespace: MineClass
 * Signature: void * `scalar_deleting_destructor'(MineClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MineClass::_scalar_deleting_destructor_(MineClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
