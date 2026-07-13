/*
 * Entry: 0041516c
 * Name: SidewaysAndClose
 * Namespace: Global
 * Signature: int SidewaysAndClose(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SidewaysAndClose(_OBJ76 *param_1,_OBJ76 *param_2)

{
  float fVar1;
  ActionInfo local_28;
  
  ActionInfo::ActionInfo(&local_28,param_1,param_2);
  fVar1 = get_obj_dist2D(param_1,param_2);
  if ((fVar1 < 50.0) &&
     ((local_28.my_quad == QUAD_RightRight || (local_28.my_quad == QUAD_LeftLeft)))) {
    return 1;
  }
  return 0;
}
