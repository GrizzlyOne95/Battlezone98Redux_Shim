/*
 * Entry: 0048dc84
 * Name: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>
 * Namespace: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
 * Signature: void _Insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>(list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_> * this, _Const_iterator<1> param_1, _Const_iterator<1> param_2, _Const_iterator<1> param_3, forward_iterator_tag param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::
list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
::
_Insert<std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Const_iterator<1>_>
          (list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
           *this,_Const_iterator<1> param_1,_Const_iterator<1> param_2,_Const_iterator<1> param_3,
          forward_iterator_tag param_4)

{
  bool bVar1;
  pair<unsigned_long_const_,float> *ppVar2;
  
  while( true ) {
    bVar1 = _Const_iterator<1>::operator==(&param_2,&param_3);
    if (bVar1) break;
    ppVar2 = _Const_iterator<1>::operator*(&param_2);
    _Insert(this,param_1,ppVar2);
    _Const_iterator<1>::operator++(&param_2);
  }
  return;
}
