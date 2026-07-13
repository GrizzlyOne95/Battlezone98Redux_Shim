/*
 * Entry: 004ce5c0
 * Name: FlagDisplay::FlagDisplay
 * Namespace: FlagDisplay
 * Signature: FlagDisplay * FlagDisplay(FlagDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlagDisplay * __thiscall FlagDisplay::FlagDisplay(FlagDisplay *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  this->flagTexture[0] = (TEXTURE *)0x0;
  this->flagTexture[1] = (TEXTURE *)0x0;
  this->flagTexture[2] = (TEXTURE *)0x0;
  this->_padding_ = (int)&_vftable_;
  return this;
}
