/*
 * Entry: 0049a940
 * Name: std::_Uninit_move<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Geizer * * _Uninit_move<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>,std::_Undefined_move_tag>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3, allocator<Geizer_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __cdecl
std::_Uninit_move<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>,std::_Undefined_move_tag>
          (Geizer **param_1,Geizer **param_2,Geizer **param_3,allocator<Geizer_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Geizer **ppGVar1;
  
  ppGVar1 = stdext::unchecked_uninitialized_copy<Geizer_*_*,Geizer_*_*,std::allocator<Geizer_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppGVar1;
}
