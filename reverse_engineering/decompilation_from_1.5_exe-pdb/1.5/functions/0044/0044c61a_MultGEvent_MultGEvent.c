/*
 * Entry: 0044c61a
 * Name: MultGEvent::MultGEvent
 * Namespace: MultGEvent
 * Signature: MultGEvent * MultGEvent(MultGEvent * this, AiMission * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MultGEvent * __thiscall MultGEvent::MultGEvent(MultGEvent *this,AiMission *param_1)

{
  uint uVar1;
  uint uVar2;
  char *_Dest;
  bool bVar3;
  char *_Format;
  
  uVar2 = 0;
  AiProcess::AiProcess((AiProcess *)this,param_1,(GameObject *)0x0);
  this->_padding_ = (int)&_vftable_;
  this->starttimer = 1;
  this->reset = 0;
  this->state = 0;
  this->bad_guy[0] = 0;
  this->bad_guy[1] = 0;
  this->bad_guy[2] = 0;
  _Dest = this->pup[0].str;
  do {
    uVar1 = uVar2 & 0x80000001;
    bVar3 = uVar1 == 0;
    if ((int)uVar1 < 0) {
      bVar3 = (uVar1 - 1 | 0xfffffffe) == 0xffffffff;
    }
    if (bVar3) {
      _Format = "repa%d";
    }
    else {
      _Format = "ammo%d";
    }
    sprintf(_Dest,_Format,(int)uVar2 / 2);
    uVar2 = uVar2 + 1;
    _Dest = _Dest + 0x20;
  } while (uVar2 < 0x1e);
  return this;
}
