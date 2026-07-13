/*
 * Entry: 004bfe52
 * Name: std::iter_swap<RadarItem_*,RadarItem_*>
 * Namespace: std
 * Signature: void iter_swap<RadarItem_*,RadarItem_*>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::iter_swap<RadarItem_*,RadarItem_*>(RadarItem *param_1,RadarItem *param_2)

{
  GameObject *pGVar1;
  long lVar2;
  
  if (param_1 != param_2) {
    pGVar1 = param_1->obj;
    lVar2 = param_1->z;
    param_1->obj = param_2->obj;
    param_1->z = param_2->z;
    param_2->z = lVar2;
    param_2->obj = pGVar1;
  }
  return;
}
