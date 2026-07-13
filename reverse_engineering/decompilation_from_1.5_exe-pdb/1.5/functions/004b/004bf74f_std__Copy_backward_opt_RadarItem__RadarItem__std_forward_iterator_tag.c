/*
 * Entry: 004bf74f
 * Name: std::_Copy_backward_opt<RadarItem_*,RadarItem_*,std::forward_iterator_tag>
 * Namespace: std
 * Signature: RadarItem * _Copy_backward_opt<RadarItem_*,RadarItem_*,std::forward_iterator_tag>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3, forward_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarItem * __cdecl
std::_Copy_backward_opt<RadarItem_*,RadarItem_*,std::forward_iterator_tag>
          (RadarItem *param_1,RadarItem *param_2,RadarItem *param_3,forward_iterator_tag param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  while (param_1 != param_2) {
    param_3[-1].obj = param_2[-1].obj;
    param_3[-1].z = param_2[-1].z;
    param_2 = param_2 + -1;
    param_3 = param_3 + -1;
  }
  return param_3;
}
