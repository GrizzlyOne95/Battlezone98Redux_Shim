/*
 * Entry: 004bf6dc
 * Name: std::swap<RadarItem>
 * Namespace: std
 * Signature: void swap<RadarItem>(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::swap<RadarItem>(RadarItem *param_1,RadarItem *param_2)

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
