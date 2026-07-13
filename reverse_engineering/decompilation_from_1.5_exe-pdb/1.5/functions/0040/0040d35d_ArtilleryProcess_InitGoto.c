/*
 * Entry: 0040d35d
 * Name: ArtilleryProcess::InitGoto
 * Namespace: ArtilleryProcess
 * Signature: void InitGoto(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitGoto(ArtilleryProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitGoto((UnitProcess *)this);
  return;
}
