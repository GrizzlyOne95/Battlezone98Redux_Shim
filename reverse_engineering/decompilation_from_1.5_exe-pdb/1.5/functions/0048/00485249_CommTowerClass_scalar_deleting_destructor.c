/*
 * Entry: 00485249
 * Name: CommTowerClass::`scalar_deleting_destructor'
 * Namespace: CommTowerClass
 * Signature: void * `scalar_deleting_destructor'(CommTowerClass * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall CommTowerClass::_scalar_deleting_destructor_(CommTowerClass *this,uint param_1)

{
  this->_padding_ = (int)&_vftable_;
  GameObjectClass::~GameObjectClass((GameObjectClass *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
