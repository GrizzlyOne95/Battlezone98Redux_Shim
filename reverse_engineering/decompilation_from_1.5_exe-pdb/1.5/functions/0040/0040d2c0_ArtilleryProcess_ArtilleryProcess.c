/*
 * Entry: 0040d2c0
 * Name: ArtilleryProcess::ArtilleryProcess
 * Namespace: ArtilleryProcess
 * Signature: ArtilleryProcess * ArtilleryProcess(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArtilleryProcess * __thiscall ArtilleryProcess::ArtilleryProcess(ArtilleryProcess *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  this->attackTimeout = 0.0;
  this->_padding_ = (int)&_vftable_;
  *(undefined1 *)&this->_padding_ = 0;
  return this;
}
