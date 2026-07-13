/*
 * Entry: 005335f2
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::back
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: Ordnance * * back(list<Ordnance_*,std::allocator<Ordnance_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Ordnance ** __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::back
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this)

{
  Ordnance **ppOVar1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Const_iterator<1>::operator--(&local_c);
  ppOVar1 = _Const_iterator<1>::operator*(&local_c);
  return ppOVar1;
}
