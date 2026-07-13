/*
 * Entry: 00532aec
 * Name: ObjectLobberClass::ObjectLobberClass
 * Namespace: ObjectLobberClass
 * Signature: ObjectLobberClass * ObjectLobberClass(ObjectLobberClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ObjectLobberClass * __thiscall ObjectLobberClass::ObjectLobberClass(ObjectLobberClass *this)

{
  WeaponClass::WeaponClass((WeaponClass *)this);
  this->shotDelay = 1.0;
  this->shotSpeed = 100.0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x4c4f4242;
  this->_padding_ = (int)"lobber";
  strncpy((char *)&this->_padding_,"wcbl.wav",0x10);
  return this;
}
