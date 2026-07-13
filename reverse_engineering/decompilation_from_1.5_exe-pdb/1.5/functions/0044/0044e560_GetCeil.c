/*
 * Entry: 0044e560
 * Name: GetCeil
 * Namespace: Global
 * Signature: int GetCeil(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetCeil(float param_1)

{
  int extraout_EAX;
  
  ceil((double)param_1);
  _ftol2_sse();
  return extraout_EAX;
}
