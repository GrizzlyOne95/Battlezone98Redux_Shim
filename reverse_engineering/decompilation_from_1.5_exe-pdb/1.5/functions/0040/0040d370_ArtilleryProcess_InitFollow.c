/*
 * Entry: 0040d370
 * Name: ArtilleryProcess::InitFollow
 * Namespace: ArtilleryProcess
 * Signature: void InitFollow(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitFollow(ArtilleryProcess *this)

{
  (**(code **)(*(int *)this->_padding_ + 0x60))();
  UnitProcess::InitFollow((UnitProcess *)this);
  return;
}
