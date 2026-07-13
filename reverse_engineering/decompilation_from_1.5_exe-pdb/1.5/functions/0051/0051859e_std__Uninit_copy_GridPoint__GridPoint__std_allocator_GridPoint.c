/*
 * Entry: 0051859e
 * Name: std::_Uninit_copy<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
 * Namespace: std
 * Signature: GridPoint * _Uninit_copy<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3, allocator<GridPoint> * param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
std::_Uninit_copy<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3,allocator<GridPoint> *param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    _Construct<GridPoint,GridPoint>(param_3,param_1);
    param_3 = param_3 + 1;
  }
  return param_3;
}
