/*
 * Entry: 004bf376
 * Name: operator<
 * Namespace: Global
 * Signature: bool operator<(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl operator<(RadarItem *param_1,RadarItem *param_2)

{
  return param_2->z < param_1->z;
}
