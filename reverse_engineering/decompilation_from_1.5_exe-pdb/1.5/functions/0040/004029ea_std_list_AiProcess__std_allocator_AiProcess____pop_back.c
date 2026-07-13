/*
 * Entry: 004029ea
 * Name: std::list<AiProcess_*,std::allocator<AiProcess_*>_>::pop_back
 * Namespace: std::list<AiProcess_*,std::allocator<AiProcess_*>_>
 * Signature: void pop_back(list<AiProcess_*,std::allocator<AiProcess_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AiProcess_*,std::allocator<AiProcess_*>_>::pop_back
          (list<AiProcess_*,std::allocator<AiProcess_*>_> *this)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  _Var1._Ptr = (_Node *)local_c._padding_;
  _Var1._padding_ = (int)&local_c;
  erase(this,_Var1);
  return;
}
