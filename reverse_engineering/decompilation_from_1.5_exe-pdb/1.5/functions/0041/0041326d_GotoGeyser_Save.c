/*
 * Entry: 0041326d
 * Name: GotoGeyser::Save
 * Namespace: GotoGeyser
 * Signature: bool Save(GotoGeyser * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GotoGeyser::Save(GotoGeyser *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->oneGeyser,4,"oneGeyser");
  if ((bVar1) && (bVar1 = GotoTask::Save((GotoTask *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
