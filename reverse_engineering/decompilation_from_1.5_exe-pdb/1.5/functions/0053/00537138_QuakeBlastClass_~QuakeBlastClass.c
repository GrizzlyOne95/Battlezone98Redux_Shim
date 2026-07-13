/*
 * Entry: 00537138
 * Name: QuakeBlastClass::~QuakeBlastClass
 * Namespace: QuakeBlastClass
 * Signature: void ~QuakeBlastClass(QuakeBlastClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall QuakeBlastClass::~QuakeBlastClass(QuakeBlastClass *this)

{
  this->_padding_ = (int)&_vftable_;
  ExplosionClass::~ExplosionClass((ExplosionClass *)this);
  return;
}
