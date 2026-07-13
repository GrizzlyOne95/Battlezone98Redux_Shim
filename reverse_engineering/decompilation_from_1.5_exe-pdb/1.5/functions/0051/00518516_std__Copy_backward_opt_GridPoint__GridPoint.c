/*
 * Entry: 00518516
 * Name: std::_Copy_backward_opt<GridPoint_*,GridPoint_*>
 * Namespace: std
 * Signature: GridPoint * _Copy_backward_opt<GridPoint_*,GridPoint_*>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3, random_access_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
std::_Copy_backward_opt<GridPoint_*,GridPoint_*>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3,
          random_access_iterator_tag param_4,_Nonscalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  _Copy_backward_opt<GridPoint_*,GridPoint_*,std::forward_iterator_tag>
            (param_1,param_2,param_3,SUB41(param_1,0),(_Nonscalar_ptr_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return param_3 + -((int)param_2 - (int)param_1 >> 3);
}
