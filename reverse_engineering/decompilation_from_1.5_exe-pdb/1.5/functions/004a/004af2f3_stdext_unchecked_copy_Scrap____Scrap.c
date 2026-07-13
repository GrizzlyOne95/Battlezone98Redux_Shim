/*
 * Entry: 004af2f3
 * Name: stdext::unchecked_copy<Scrap_*_*,Scrap_*_*>
 * Namespace: stdext
 * Signature: Scrap * * unchecked_copy<Scrap_*_*,Scrap_*_*>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __cdecl
stdext::unchecked_copy<Scrap_*_*,Scrap_*_*>(Scrap **param_1,Scrap **param_2,Scrap **param_3)

{
  Scrap **ppSVar1;
  
  ppSVar1 = std::_Copy_opt<Scrap_*_*,Scrap_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
