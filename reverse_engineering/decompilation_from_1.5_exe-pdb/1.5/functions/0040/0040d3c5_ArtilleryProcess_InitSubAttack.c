/*
 * Entry: 0040d3c5
 * Name: ArtilleryProcess::InitSubAttack
 * Namespace: ArtilleryProcess
 * Signature: void InitSubAttack(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitSubAttack(ArtilleryProcess *this)

{
  float fVar1;
  
  fVar1 = Get_Time();
  this->attackTimeout = fVar1 + 30.0;
  return;
}
