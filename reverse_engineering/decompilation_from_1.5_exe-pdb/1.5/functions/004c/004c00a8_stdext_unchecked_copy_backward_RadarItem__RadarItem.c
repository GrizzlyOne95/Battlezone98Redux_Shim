/*
 * Entry: 004c00a8
 * Name: stdext::unchecked_copy_backward<RadarItem_*,RadarItem_*>
 * Namespace: stdext
 * Signature: RadarItem * unchecked_copy_backward<RadarItem_*,RadarItem_*>(RadarItem * param_1, RadarItem * param_2, RadarItem * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarItem * __cdecl
stdext::unchecked_copy_backward<RadarItem_*,RadarItem_*>
          (RadarItem *param_1,RadarItem *param_2,RadarItem *param_3)

{
  RadarItem *pRVar1;
  
  pRVar1 = std::_Copy_backward_opt<RadarItem_*,RadarItem_*>
                     (param_1,param_2,param_3,SUB41(param_2,0),
                      (_Nonscalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0
                     );
  return pRVar1;
}
