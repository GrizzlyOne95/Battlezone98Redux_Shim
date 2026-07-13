/*
 * Entry: 0040b4c7
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::back
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>
 * Signature: AOI * * back(list<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AOI ** __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::back(list<AOI_*,std::allocator<AOI_*>_> *this)

{
  AOI **ppAVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppAVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppAVar1;
}
