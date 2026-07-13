/*
 * Entry: 0048d4c2
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::front
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: BASE_STRUCT * front(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT * __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::front
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  BASE_STRUCT *pBVar1;
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Myoff = (uint)this;
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::
  _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>
            (&local_c,this->_Myoff,(_Container_base_aux *)this);
  pBVar1 = _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator*(&local_c);
  return pBVar1;
}
