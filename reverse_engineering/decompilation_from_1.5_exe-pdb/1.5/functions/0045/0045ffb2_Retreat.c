/*
 * Entry: 0045ffb2
 * Name: Retreat
 * Namespace: Global
 * Signature: void Retreat(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Retreat(int param_1,int param_2,int param_3)

{
  SetIndependence(param_1,0);
  Goto(param_1,param_2,param_3);
  return;
}
