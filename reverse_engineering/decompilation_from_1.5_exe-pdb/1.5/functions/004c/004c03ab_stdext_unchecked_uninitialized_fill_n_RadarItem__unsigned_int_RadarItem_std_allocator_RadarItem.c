/*
 * Entry: 004c03ab
 * Name: stdext::unchecked_uninitialized_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>(RadarItem * param_1, uint param_2, RadarItem * param_3, allocator<RadarItem> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>
          (RadarItem *param_1,uint param_2,RadarItem *param_3,allocator<RadarItem> *param_4)

{
  std::_Uninit_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>
            (param_1,param_2,param_3,param_4,(_Nonscalar_ptr_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
