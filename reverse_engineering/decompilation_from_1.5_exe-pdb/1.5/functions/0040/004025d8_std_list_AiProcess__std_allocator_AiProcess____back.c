/*
 * Entry: 004025d8
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::back
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: AiProcess * * back(list<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiProcess ** __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::back
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  AiProcess **ppAVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppAVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppAVar1;
}
