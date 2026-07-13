/*
 * Entry: 0040d383
 * Name: ArtilleryProcess::InitRescue
 * Namespace: ArtilleryProcess
 * Signature: void InitRescue(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitRescue(ArtilleryProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitRescue((UnitProcess *)this);
  return;
}
