/*
 * Entry: 0040d3a9
 * Name: ArtilleryProcess::InitAttack
 * Namespace: ArtilleryProcess
 * Signature: void InitAttack(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitAttack(ArtilleryProcess *this)

{
  float fVar1;
  
  (**(code **)(*(int *)this->_padding_ + 0x5c))();
  fVar1 = Get_Time();
  this->attackTimeout = fVar1 + 30.0;
  return;
}
