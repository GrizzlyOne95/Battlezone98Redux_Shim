/*
 * Entry: 004d06de
 * Name: LensFlare::LensFlare
 * Namespace: LensFlare
 * Signature: LensFlare * LensFlare(LensFlare * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

LensFlare * __thiscall LensFlare::LensFlare(LensFlare *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  this->field_0x24 = this->field_0x24 & 0xfd;
  *(undefined ***)this = &_vftable_;
  return this;
}
