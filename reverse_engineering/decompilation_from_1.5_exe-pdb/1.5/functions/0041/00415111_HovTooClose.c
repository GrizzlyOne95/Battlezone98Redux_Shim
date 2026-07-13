/*
 * Entry: 00415111
 * Name: HovTooClose
 * Namespace: Global
 * Signature: int HovTooClose(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl HovTooClose(_OBJ76 *param_1,_OBJ76 *param_2)

{
  float fVar1;
  
  fVar1 = get_obj_dist2D(param_1,param_2);
  if (fVar1 < 20.0) {
    return 1;
  }
  return 0;
}
