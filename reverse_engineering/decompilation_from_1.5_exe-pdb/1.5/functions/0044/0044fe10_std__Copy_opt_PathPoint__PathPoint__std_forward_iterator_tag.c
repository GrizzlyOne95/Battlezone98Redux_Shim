/*
 * Entry: 0044fe10
 * Name: std::_Copy_opt<PathPoint_*,PathPoint_*,std::forward_iterator_tag>
 * Namespace: std
 * Signature: PathPoint * _Copy_opt<PathPoint_*,PathPoint_*,std::forward_iterator_tag>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, forward_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
std::_Copy_opt<PathPoint_*,PathPoint_*,std::forward_iterator_tag>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,forward_iterator_tag param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    (param_3->point).x = (param_1->point).x;
    (param_3->point).z = (param_1->point).z;
    param_3->strip = param_1->strip;
    param_3->seqNo = param_1->seqNo;
    param_3 = param_3 + 1;
  }
  return param_3;
}
