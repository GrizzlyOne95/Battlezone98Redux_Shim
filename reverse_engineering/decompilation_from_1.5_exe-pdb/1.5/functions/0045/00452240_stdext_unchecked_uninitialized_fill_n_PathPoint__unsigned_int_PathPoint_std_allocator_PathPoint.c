/*
 * Entry: 00452240
 * Name: stdext::unchecked_uninitialized_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>(PathPoint * param_1, uint param_2, PathPoint * param_3, allocator<PathPoint> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>
          (PathPoint *param_1,uint param_2,PathPoint *param_3,allocator<PathPoint> *param_4)

{
  std::_Uninit_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>
            (param_1,param_2,param_3,param_4,(_Nonscalar_ptr_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
