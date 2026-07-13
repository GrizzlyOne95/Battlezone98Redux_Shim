/*
 * Entry: 0040d2db
 * Name: ArtilleryProcess::~ArtilleryProcess
 * Namespace: ArtilleryProcess
 * Signature: void ~ArtilleryProcess(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::~ArtilleryProcess(ArtilleryProcess *this)

{
  this->_padding_ = (int)&OffensiveProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  this->_padding_ = 0;
  UnitProcess::~UnitProcess((UnitProcess *)this);
  return;
}
