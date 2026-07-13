/*
 * Entry: 004151af
 * Name: FleePlentyFar
 * Namespace: Global
 * Signature: int FleePlentyFar(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FleePlentyFar(_OBJ76 *param_1,_OBJ76 *param_2)

{
  float fVar1;
  
  fVar1 = get_obj_dist2D(param_1,param_2);
  if (50.0 < fVar1) {
    return 1;
  }
  return 0;
}
