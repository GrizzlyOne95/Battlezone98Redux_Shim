/*
 * Entry: 0047dbb0
 * Name: APC::Save
 * Namespace: APC
 * Signature: bool Save(APC * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall APC::Save(APC *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = ::out(param_1,&this->soldierCount,4,"soldierCount");
  if ((bVar1) && (bVar1 = ::out(param_1,&this->_padding_,4,"state"), bVar1)) {
    bVar1 = HoverCraft::Save((HoverCraft *)this,param_1);
    return bVar1;
  }
  return false;
}
