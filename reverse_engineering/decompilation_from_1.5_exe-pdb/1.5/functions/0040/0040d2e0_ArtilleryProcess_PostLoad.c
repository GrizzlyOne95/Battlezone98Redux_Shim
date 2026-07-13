/*
 * Entry: 0040d2e0
 * Name: ArtilleryProcess::PostLoad
 * Namespace: ArtilleryProcess
 * Signature: bool PostLoad(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ArtilleryProcess::PostLoad(ArtilleryProcess *this)

{
  bool bVar1;
  float fVar2;
  
  if ((this->_padding_ == 7) || (this->_padding_ == 0xf)) {
    fVar2 = Get_Time();
    this->attackTimeout = fVar2 + 30.0;
  }
  bVar1 = OffensiveProcess::PostLoad((OffensiveProcess *)this);
  return bVar1;
}
