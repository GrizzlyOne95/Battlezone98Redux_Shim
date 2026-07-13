/*
 * Entry: 00460d58
 * Name: stdext::_Unchecked_uninitialized_move<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*,std::allocator<Scrap_*>_>
 * Namespace: stdext
 * Signature: Scrap * * _Unchecked_uninitialized_move<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*,std::allocator<Scrap_*>_>(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1, _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2, Scrap * * param_3, allocator<Scrap_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __cdecl
stdext::
_Unchecked_uninitialized_move<std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>,Scrap_*_*,std::allocator<Scrap_*>_>
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_1,
          _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> param_2,Scrap **param_3,
          allocator<Scrap_*> *param_4)

{
  Scrap **ppSVar1;
  
  ppSVar1 = unchecked_uninitialized_copy<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>
                      ((Scrap **)param_1._4_4_,(Scrap **)param_2._4_4_,param_3,param_4);
  return ppSVar1;
}
