/*
 * Entry: 004c9657
 * Name: EarthQuake::EarthQuake
 * Namespace: EarthQuake
 * Signature: EarthQuake * EarthQuake(EarthQuake * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EarthQuake * __thiscall EarthQuake::EarthQuake(EarthQuake *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  this->scale = 0.0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
