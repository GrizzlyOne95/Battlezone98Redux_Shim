/*
 * Entry: 00532b9f
 * Name: ObjectLobberClass::~ObjectLobberClass
 * Namespace: ObjectLobberClass
 * Signature: void ~ObjectLobberClass(ObjectLobberClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ObjectLobberClass::~ObjectLobberClass(ObjectLobberClass *this)

{
  this->_padding_ = (int)&_vftable_;
  WeaponClass::~WeaponClass((WeaponClass *)this);
  return;
}
