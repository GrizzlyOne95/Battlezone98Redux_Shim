/*
 * Entry: 00498d7a
 * Name: GameObjectClass::~GameObjectClass
 * Namespace: GameObjectClass
 * Signature: void ~GameObjectClass(GameObjectClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObjectClass::~GameObjectClass(GameObjectClass *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->infoText != (char *)0x0) {
    operator_delete__(this->infoText);
  }
  Attachable::~Attachable((Attachable *)this);
  return;
}
