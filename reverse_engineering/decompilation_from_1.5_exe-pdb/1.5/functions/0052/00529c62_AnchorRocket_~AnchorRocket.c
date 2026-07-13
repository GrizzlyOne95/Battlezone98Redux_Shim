/*
 * Entry: 00529c62
 * Name: AnchorRocket::~AnchorRocket
 * Namespace: AnchorRocket
 * Signature: void ~AnchorRocket(AnchorRocket * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnchorRocket::~AnchorRocket(AnchorRocket *this)

{
  this->_padding_ = (int)&_vftable_;
  Rocket::~Rocket((Rocket *)this);
  return;
}
