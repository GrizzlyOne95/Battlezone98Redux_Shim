/*
 * Entry: 0044ec70
 * Name: SharedEdge
 * Namespace: Global
 * Signature: SE SharedEdge(Strip * param_1, Strip * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SE __cdecl SharedEdge(Strip *param_1,Strip *param_2)

{
  SE SVar1;
  
  if (param_2->x1 == param_1->x0) {
    return SE_X0;
  }
  if (param_2->z1 == param_1->z0) {
    return SE_Z0;
  }
  SVar1 = SE_X1;
  if (param_2->x0 != param_1->x1) {
    SVar1 = SE_Z1;
  }
  return SVar1;
}
