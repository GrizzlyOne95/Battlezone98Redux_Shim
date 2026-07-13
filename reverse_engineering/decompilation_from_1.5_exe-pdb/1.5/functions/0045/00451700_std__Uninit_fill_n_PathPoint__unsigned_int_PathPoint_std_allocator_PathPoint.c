/*
 * Entry: 00451700
 * Name: std::_Uninit_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>(PathPoint * param_1, uint param_2, PathPoint * param_3, allocator<PathPoint> * param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>
          (PathPoint *param_1,uint param_2,PathPoint *param_3,allocator<PathPoint> *param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    if (param_1 != (PathPoint *)0x0) {
      (param_1->point).x = (param_3->point).x;
      (param_1->point).z = (param_3->point).z;
      param_1->strip = param_3->strip;
      param_1->seqNo = param_3->seqNo;
    }
    param_1 = param_1 + 1;
  }
  return;
}
