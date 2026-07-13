/*
 * Entry: 0048d4dd
 * Name: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::back
 * Namespace: std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>
 * Signature: BASE_STRUCT * back(deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BASE_STRUCT * __thiscall
std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::back
          (deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_> *this)

{
  BASE_STRUCT *pBVar1;
  _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1> _Var2;
  undefined1 *puVar3;
  undefined1 local_14 [16];
  
  puVar3 = local_14;
  _Var2 = end(this);
  _Var2 = _Deque_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator-
                    (_Var2._0_4_,(int)puVar3);
  pBVar1 = _Deque_const_iterator<BASE_STRUCT,std::allocator<BASE_STRUCT>,1>::operator*(_Var2._0_4_);
  return pBVar1;
}
