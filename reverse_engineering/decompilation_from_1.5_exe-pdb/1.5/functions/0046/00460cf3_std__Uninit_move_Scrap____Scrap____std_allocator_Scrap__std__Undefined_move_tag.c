/*
 * Entry: 00460cf3
 * Name: std::_Uninit_move<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Scrap * * _Uninit_move<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>,std::_Undefined_move_tag>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3, allocator<Scrap_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __cdecl
std::_Uninit_move<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>,std::_Undefined_move_tag>
          (Scrap **param_1,Scrap **param_2,Scrap **param_3,allocator<Scrap_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Scrap **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppSVar1;
}
