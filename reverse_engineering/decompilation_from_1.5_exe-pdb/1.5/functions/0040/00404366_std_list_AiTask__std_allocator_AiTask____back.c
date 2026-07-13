/*
 * Entry: 00404366
 * Name: std::list<AiTask_*,std::allocator<AiTask_*>_>::back
 * Namespace: std::list<AiTask_*,std::allocator<AiTask_*>_>
 * Signature: AiTask * * back(list<AiTask_*,std::allocator<AiTask_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiTask ** __thiscall
std::list<AiTask_*,std::allocator<AiTask_*>_>::back(list<AiTask_*,std::allocator<AiTask_*>_> *this)

{
  AiTask **ppAVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppAVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppAVar1;
}
