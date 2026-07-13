/*
 * Entry: 00451400
 * Name: std::_Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
 * Namespace: std
 * Signature: PathPoint * _Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, allocator<PathPoint> * param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
std::_Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,allocator<PathPoint> *param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    if (param_3 != (PathPoint *)0x0) {
      (param_3->point).x = (param_1->point).x;
      (param_3->point).z = (param_1->point).z;
      param_3->strip = param_1->strip;
      param_3->seqNo = param_1->seqNo;
    }
    param_3 = param_3 + 1;
  }
  return param_3;
}
