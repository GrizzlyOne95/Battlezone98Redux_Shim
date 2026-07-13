/*
 * Entry: 00460d86
 * Name: stdext::_Unchecked_uninitialized_move<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>
 * Namespace: stdext
 * Signature: Scrap * * _Unchecked_uninitialized_move<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3, allocator<Scrap_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __cdecl
stdext::_Unchecked_uninitialized_move<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>
          (Scrap **param_1,Scrap **param_2,Scrap **param_3,allocator<Scrap_*> *param_4)

{
  Scrap **ppSVar1;
  
  ppSVar1 = std::_Uninit_copy<Scrap_*_*,Scrap_*_*,std::allocator<Scrap_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
