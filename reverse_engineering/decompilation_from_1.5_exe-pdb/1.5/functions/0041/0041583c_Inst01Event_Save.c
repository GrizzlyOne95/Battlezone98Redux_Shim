/*
 * Entry: 0041583c
 * Name: Inst01Event::Save
 * Namespace: Inst01Event
 * Signature: bool Save(Inst01Event * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst01Event::Save(Inst01Event *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = out_ptr(param_1,&this->_padding_,4,"fMission");
  if (((bVar1) && (bVar1 = out_ptr(param_1,&this->_padding_,4,"fOwner"), bVar1)) &&
     (bVar1 = ::out(param_1,&this->_padding_,4,"exited"), bVar1)) {
    return true;
  }
  return false;
}
