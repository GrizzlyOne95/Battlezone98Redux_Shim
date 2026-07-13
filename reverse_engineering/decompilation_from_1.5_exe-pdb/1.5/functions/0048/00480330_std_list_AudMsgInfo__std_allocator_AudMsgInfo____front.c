/*
 * Entry: 00480330
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::front
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: AudMsgInfo * * front(list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AudMsgInfo ** __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::front
          (list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  AudMsgInfo **ppAVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead->_Next,this);
  ppAVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppAVar1;
}
