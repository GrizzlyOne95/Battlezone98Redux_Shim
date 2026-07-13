/*
 * Entry: 004c019b
 * Name: std::_Uninit_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>(RadarItem * param_1, uint param_2, RadarItem * param_3, allocator<RadarItem> * param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>
          (RadarItem *param_1,uint param_2,RadarItem *param_3,allocator<RadarItem> *param_4,
          _Nonscalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  for (; param_2 != 0; param_2 = param_2 - 1) {
    _Construct<RadarItem,RadarItem>(param_1,param_3);
    param_1 = param_1 + 1;
  }
  return;
}
