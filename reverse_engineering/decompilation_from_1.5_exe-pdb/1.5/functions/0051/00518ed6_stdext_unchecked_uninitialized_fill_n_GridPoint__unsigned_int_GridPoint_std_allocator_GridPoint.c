/*
 * Entry: 00518ed6
 * Name: stdext::unchecked_uninitialized_fill_n<GridPoint_*,unsigned_int,GridPoint,std::allocator<GridPoint>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<GridPoint_*,unsigned_int,GridPoint,std::allocator<GridPoint>_>(GridPoint * param_1, uint param_2, GridPoint * param_3, allocator<GridPoint> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<GridPoint_*,unsigned_int,GridPoint,std::allocator<GridPoint>_>
          (GridPoint *param_1,uint param_2,GridPoint *param_3,allocator<GridPoint> *param_4)

{
  std::_Uninit_fill_n<GridPoint_*,unsigned_int,GridPoint,std::allocator<GridPoint>_>
            (param_1,param_2,param_3,param_4,(_Nonscalar_ptr_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
