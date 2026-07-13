/*
 * Entry: 0048b732
 * Name: std::_Distance2<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,unsigned_int>
 * Namespace: std
 * Signature: void _Distance2<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,unsigned_int>(_Iterator<1> param_1, _Iterator<1> param_2, uint * param_3, bidirectional_iterator_tag param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Distance2<std::list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>::_Iterator<1>,unsigned_int>
          (_Iterator<1> param_1,_Iterator<1> param_2,uint *param_3,
          bidirectional_iterator_tag param_4)

{
  bool bVar1;
  
  bVar1 = list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
          ::_Const_iterator<1>::operator==
                    ((_Const_iterator<1> *)&param_1,(_Const_iterator<1> *)&param_2);
  while (!bVar1) {
    *param_3 = *param_3 + 1;
    list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
    ::_Const_iterator<1>::operator++((_Const_iterator<1> *)&param_1);
    bVar1 = list<std::pair<unsigned_long_const_,unsigned_long>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
            ::_Const_iterator<1>::operator==
                      ((_Const_iterator<1> *)&param_1,(_Const_iterator<1> *)&param_2);
  }
  return;
}
