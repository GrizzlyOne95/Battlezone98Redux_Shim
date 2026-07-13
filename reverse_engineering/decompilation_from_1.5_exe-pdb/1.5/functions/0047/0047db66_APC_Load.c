/*
 * Entry: 0047db66
 * Name: APC::Load
 * Namespace: APC
 * Signature: bool Load(APC * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall APC::Load(APC *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::in(param_1,&this->soldierCount,4);
  if ((bVar1) && (bVar1 = ::in(param_1,&this->_padding_,4), bVar1)) {
    bVar1 = HoverCraft::Load((HoverCraft *)this,param_1);
    return bVar1;
  }
  return false;
}
