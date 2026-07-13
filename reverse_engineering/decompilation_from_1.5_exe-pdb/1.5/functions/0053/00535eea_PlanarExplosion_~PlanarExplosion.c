/*
 * Entry: 00535eea
 * Name: PlanarExplosion::~PlanarExplosion
 * Namespace: PlanarExplosion
 * Signature: void ~PlanarExplosion(PlanarExplosion * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlanarExplosion::~PlanarExplosion(PlanarExplosion *this)

{
  this->_padding_ = (int)&_vftable_;
  Explosion::~Explosion((Explosion *)this);
  return;
}
