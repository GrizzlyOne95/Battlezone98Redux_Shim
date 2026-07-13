/*
 * Entry: 004d8858
 * Name: Reticle::Reticle
 * Namespace: Reticle
 * Signature: Reticle * Reticle(Reticle * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Reticle * __thiscall Reticle::Reticle(Reticle *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  this->_padding_ = (int)&_vftable_;
  return this;
}
