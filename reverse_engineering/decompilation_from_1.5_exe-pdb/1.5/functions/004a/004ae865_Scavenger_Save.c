/*
 * Entry: 004ae865
 * Name: Scavenger::Save
 * Namespace: Scavenger
 * Signature: bool Save(Scavenger * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Scavenger::Save(Scavenger *this,_iobuf *param_1)

{
  bool bVar1;
  
  ::out(param_1,&this->scrapHeld,4,"scrapHeld");
  bVar1 = HoverCraft::Save((HoverCraft *)this,param_1);
  return bVar1;
}
