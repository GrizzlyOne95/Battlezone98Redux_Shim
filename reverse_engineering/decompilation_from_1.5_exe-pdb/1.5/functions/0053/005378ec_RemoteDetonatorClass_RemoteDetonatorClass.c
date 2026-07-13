/*
 * Entry: 005378ec
 * Name: RemoteDetonatorClass::RemoteDetonatorClass
 * Namespace: RemoteDetonatorClass
 * Signature: RemoteDetonatorClass * RemoteDetonatorClass(RemoteDetonatorClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RemoteDetonatorClass * __thiscall
RemoteDetonatorClass::RemoteDetonatorClass(RemoteDetonatorClass *this)

{
  MortarClass::MortarClass((MortarClass *)this);
  this->armedReticle = this->_padding_;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = (int)"detonator";
  this->_padding_ = 0x52444554;
  return this;
}
