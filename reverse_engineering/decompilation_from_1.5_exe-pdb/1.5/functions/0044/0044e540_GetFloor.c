/*
 * Entry: 0044e540
 * Name: GetFloor
 * Namespace: Global
 * Signature: int GetFloor(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetFloor(float param_1)

{
  int extraout_EAX;
  
  floor((double)param_1);
  _ftol2_sse();
  return extraout_EAX;
}
