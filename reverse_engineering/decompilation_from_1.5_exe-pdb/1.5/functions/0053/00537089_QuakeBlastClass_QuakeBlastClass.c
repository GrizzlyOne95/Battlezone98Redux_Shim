/*
 * Entry: 00537089
 * Name: QuakeBlastClass::QuakeBlastClass
 * Namespace: QuakeBlastClass
 * Signature: QuakeBlastClass * QuakeBlastClass(QuakeBlastClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

QuakeBlastClass * __thiscall QuakeBlastClass::QuakeBlastClass(QuakeBlastClass *this)

{
  ExplosionClass::ExplosionClass((ExplosionClass *)this);
  this->quakeCount = 0;
  this->quakeClass = (OrdnanceClass *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x5155414b;
  this->_padding_ = (int)"quakeblast";
  return this;
}
