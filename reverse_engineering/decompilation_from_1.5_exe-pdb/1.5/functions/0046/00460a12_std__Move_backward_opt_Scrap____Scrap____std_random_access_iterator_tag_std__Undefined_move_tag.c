/*
 * Entry: 00460a12
 * Name: std::_Move_backward_opt<Scrap_*_*,Scrap_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Scrap * * _Move_backward_opt<Scrap_*_*,Scrap_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(Scrap * * param_1, Scrap * * param_2, Scrap * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scrap ** __cdecl
std::
_Move_backward_opt<Scrap_*_*,Scrap_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (Scrap **param_1,Scrap **param_2,Scrap **param_3,random_access_iterator_tag param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Scrap **ppSVar1;
  
  ppSVar1 = _Copy_backward_opt<Scrap_*_*,Scrap_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppSVar1;
}
