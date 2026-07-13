/*
 * Entry: 0041322c
 * Name: GotoGeyser::Load
 * Namespace: GotoGeyser
 * Signature: bool Load(GotoGeyser * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoGeyser::Load(GotoGeyser *this,_iobuf *param_1)

{
  bool bVar1;
  
  this->blocked = false;
  bVar1 = ::in(param_1,&this->oneGeyser,4);
  if ((bVar1) && (bVar1 = GotoTask::Load((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
