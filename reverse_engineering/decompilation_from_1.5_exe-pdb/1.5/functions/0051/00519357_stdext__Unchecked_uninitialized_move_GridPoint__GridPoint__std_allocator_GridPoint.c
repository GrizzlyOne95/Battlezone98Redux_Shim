/*
 * Entry: 00519357
 * Name: stdext::_Unchecked_uninitialized_move<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
 * Namespace: stdext
 * Signature: GridPoint * _Unchecked_uninitialized_move<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>(GridPoint * param_1, GridPoint * param_2, GridPoint * param_3, allocator<GridPoint> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __cdecl
stdext::_Unchecked_uninitialized_move<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
          (GridPoint *param_1,GridPoint *param_2,GridPoint *param_3,allocator<GridPoint> *param_4)

{
  GridPoint *pGVar1;
  
  pGVar1 = std::_Uninit_copy<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
                     (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                      (_Range_checked_iterator_tag)0x0);
  return pGVar1;
}
