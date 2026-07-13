/*
 * Entry: 004036d2
 * Name: std::list<AiPath_*,std::allocator<AiPath_*>_>::back
 * Namespace: std::list<AiPath_*,std::allocator<AiPath_*>_>
 * Signature: AiPath * * back(list<AiPath_*,std::allocator<AiPath_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiPath ** __thiscall
std::list<AiPath_*,std::allocator<AiPath_*>_>::back(list<AiPath_*,std::allocator<AiPath_*>_> *this)

{
  AiPath **ppAVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppAVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppAVar1;
}
