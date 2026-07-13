/*
 * Entry: 00413478
 * Name: GotoGeyser::GotoGeyser
 * Namespace: GotoGeyser
 * Signature: GotoGeyser * GotoGeyser(GotoGeyser * this, Craft * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GotoGeyser * __thiscall GotoGeyser::GotoGeyser(GotoGeyser *this,Craft *param_1)

{
  VECTOR_3D *pVVar1;
  Geizer *pGVar2;
  
  pGVar2 = (Geizer *)0x0;
  pVVar1 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
  pGVar2 = GetNearestGeizer(pVVar1,pGVar2);
  GotoTask::GotoTask((GotoTask *)this,param_1,(GameObject *)pGVar2);
  this->_padding_ = (int)&_vftable_;
  if (this->_padding_ == 0) {
    Say(param_1,ATTACK_MSG,0);
  }
  else {
    Say(param_1,REPAIR_MSG,0);
    *(undefined1 *)((int)&this->_padding_ + 2) = 1;
    this->blocked = false;
    this->oneGeyser = 0;
  }
  return this;
}
