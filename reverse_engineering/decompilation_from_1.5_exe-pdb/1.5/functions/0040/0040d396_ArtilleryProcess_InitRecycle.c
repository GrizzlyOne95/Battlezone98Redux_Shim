/*
 * Entry: 0040d396
 * Name: ArtilleryProcess::InitRecycle
 * Namespace: ArtilleryProcess
 * Signature: void InitRecycle(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitRecycle(ArtilleryProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitRecycle((UnitProcess *)this);
  return;
}
