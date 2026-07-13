/*
 * Entry: 00532601
 * Name: ObjectLobber::~ObjectLobber
 * Namespace: ObjectLobber
 * Signature: void ~ObjectLobber(ObjectLobber * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ObjectLobber::~ObjectLobber(ObjectLobber *this)

{
  this->_padding_ = (int)&_vftable_;
  Weapon::~Weapon((Weapon *)this);
  return;
}
