/*
 * Entry: 004bf396
 * Name: operator==
 * Namespace: Global
 * Signature: bool operator==(RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl operator==(RadarItem *param_1,RadarItem *param_2)

{
  return (bool)('\x01' - (param_1->z != param_2->z));
}
