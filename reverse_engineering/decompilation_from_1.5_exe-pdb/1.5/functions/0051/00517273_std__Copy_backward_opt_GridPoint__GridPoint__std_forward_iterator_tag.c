/*
 * Entry: 00517273
 * Name: std::_Copy_backward_opt<GridPoint_*,GridPoint_*,std::forward_iterator_tag>
 * Namespace: std
 * Signature: GridPoint * _Copy_backward_opt<GridPoint_*,GridPoint_*,std::forward_iterator_tag>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3, forward_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
std::_Copy_backward_opt<GridPoint_*,GridPoint_*,std::forward_iterator_tag>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3,forward_iterator_tag param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  while (param_1 != param_2) {
    param_3[-1].x = param_2[-1].x;
    param_3[-1].y = param_2[-1].y;
    param_2 = param_2 + -1;
    param_3 = param_3 + -1;
  }
  return param_3;
}
