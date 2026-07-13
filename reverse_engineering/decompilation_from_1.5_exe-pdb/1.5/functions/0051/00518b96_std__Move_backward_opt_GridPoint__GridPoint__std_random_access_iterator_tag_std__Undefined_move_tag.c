/*
 * Entry: 00518b96
 * Name: std::_Move_backward_opt<GridPoint_*,GridPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: GridPoint * _Move_backward_opt<GridPoint_*,GridPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
std::
_Move_backward_opt<GridPoint_*,GridPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  GridPoint *pGVar1;
  
  pGVar1 = _Copy_backward_opt<GridPoint_*,GridPoint_*>
                     (param_1,param_2,param_3,param_4,(_Nonscalar_ptr_iterator_tag)0x0,
                      (_Range_checked_iterator_tag)0x0);
  return pGVar1;
}
