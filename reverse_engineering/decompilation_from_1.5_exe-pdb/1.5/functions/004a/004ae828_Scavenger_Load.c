/*
 * Entry: 004ae828
 * Name: Scavenger::Load
 * Namespace: Scavenger
 * Signature: bool Load(Scavenger * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Scavenger::Load(Scavenger *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (version - 0x40fU < 0x3c1) {
    ::in(param_1,&this->scrapHeld,4);
  }
  bVar1 = HoverCraft::Load((HoverCraft *)this,param_1);
  return bVar1;
}
