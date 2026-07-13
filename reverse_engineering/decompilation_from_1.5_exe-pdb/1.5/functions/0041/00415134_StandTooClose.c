/*
 * Entry: 00415134
 * Name: StandTooClose
 * Namespace: Global
 * Signature: int StandTooClose(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StandTooClose(_OBJ76 *param_1,_OBJ76 *param_2)

{
  float fVar1;
  
  fVar1 = get_obj_dist2D(param_1,param_2);
  if (fVar1 < 20.0) {
    return 1;
  }
  return 0;
}
