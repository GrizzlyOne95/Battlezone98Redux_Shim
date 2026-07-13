/*
 * Entry: 00537186
 * Name: QuakeBlast::~QuakeBlast
 * Namespace: QuakeBlast
 * Signature: void ~QuakeBlast(QuakeBlast * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall QuakeBlast::~QuakeBlast(QuakeBlast *this)

{
  this->_padding_ = (int)&_vftable_;
  Explosion::~Explosion((Explosion *)this);
  return;
}
