/*
 * Entry: 00415837
 * Name: Inst01Event::Load
 * Namespace: Inst01Event
 * Signature: bool Load(Inst01Event * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Inst01Event::Load(Inst01Event *this,_iobuf *param_1)

{
  bool bVar1;
  
  bVar1 = in_ptr(param_1,(void **)&this->_padding_,4,"AiProcess",this);
  if (((bVar1) && (bVar1 = in_ptr(param_1,(void **)&this->_padding_,4,"AiProcess",this), bVar1)) &&
     (bVar1 = ::in(param_1,&this->_padding_,4), bVar1)) {
    return true;
  }
  return false;
}
