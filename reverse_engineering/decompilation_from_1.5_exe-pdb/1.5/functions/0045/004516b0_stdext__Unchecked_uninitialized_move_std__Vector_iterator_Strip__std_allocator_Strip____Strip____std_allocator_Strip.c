/*
 * Entry: 004516b0
 * Name: stdext::_Unchecked_uninitialized_move<std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>,Strip_*_*,std::allocator<Strip_*>_>
 * Namespace: stdext
 * Signature: Strip * * _Unchecked_uninitialized_move<std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>,Strip_*_*,std::allocator<Strip_*>_>(_Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_1, _Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_2, Strip * * param_3, allocator<Strip_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Strip ** __cdecl
stdext::
_Unchecked_uninitialized_move<std::_Vector_iterator<Strip_*,std::allocator<Strip_*>_>,Strip_*_*,std::allocator<Strip_*>_>
          (_Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_1,
          _Vector_iterator<Strip_*,std::allocator<Strip_*>_> param_2,Strip **param_3,
          allocator<Strip_*> *param_4)

{
  int iVar1;
  
  iVar1 = (int)(param_2._4_4_ - param_1._4_4_) >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,(void *)param_1._4_4_,iVar1 * 4);
  }
  return param_3 + iVar1;
}
