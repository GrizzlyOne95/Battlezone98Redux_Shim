/*
 * Entry: 00518f40
 * Name: std::_Uninit_move<GridPoint_*,GridPoint_*,std::allocator<GridPoint>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: GridPoint * _Uninit_move<GridPoint_*,GridPoint_*,std::allocator<GridPoint>,std::_Undefined_move_tag>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3, allocator<GridPoint> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
std::_Uninit_move<GridPoint_*,GridPoint_*,std::allocator<GridPoint>,std::_Undefined_move_tag>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3,allocator<GridPoint> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  GridPoint *pGVar1;
  
  pGVar1 = stdext::unchecked_uninitialized_copy<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
                     (param_1,param_2,param_3,param_4);
  return pGVar1;
}
