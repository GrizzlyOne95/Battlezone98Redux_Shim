/*
 * Entry: 0053d6b2
 * Name: TorpedoClass::~TorpedoClass
 * Namespace: TorpedoClass
 * Signature: void ~TorpedoClass(TorpedoClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TorpedoClass::~TorpedoClass(TorpedoClass *this)

{
  this->_padding_ = (int)&_vftable_;
  PowerUpClass::~PowerUpClass((PowerUpClass *)this);
  return;
}
