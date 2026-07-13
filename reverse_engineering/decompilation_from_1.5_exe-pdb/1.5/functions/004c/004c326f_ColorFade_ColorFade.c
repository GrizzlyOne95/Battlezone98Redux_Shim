/*
 * Entry: 004c326f
 * Name: ColorFade::ColorFade
 * Namespace: ColorFade
 * Signature: ColorFade * ColorFade(ColorFade * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ColorFade * __thiscall ColorFade::ColorFade(ColorFade *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  *(byte *)&this->_padding_ = (byte)this->_padding_ & 0xf9;
  this->_padding_ = (int)&_vftable_;
  return this;
}
