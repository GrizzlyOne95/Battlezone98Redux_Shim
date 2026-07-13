/*
 * Entry: 0040d455
 * Name: ArtilleryProcess::InitWait
 * Namespace: ArtilleryProcess
 * Signature: void InitWait(ArtilleryProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ArtilleryProcess::InitWait(ArtilleryProcess *this)

{
  float fVar1;
  
  if (((char)this->_padding_ != '\0') || (*(float *)(this->_padding_ + 0x110) < 10.0)) {
    (**(code **)(*(int *)this->_padding_ + 0x5c))();
  }
  else {
    *(undefined1 *)&this->_padding_ = 1;
    fVar1 = Get_Time();
    this->_padding_ = (int)(fVar1 + 10.0);
  }
  OffensiveProcess::InitWait((OffensiveProcess *)this);
  return;
}
