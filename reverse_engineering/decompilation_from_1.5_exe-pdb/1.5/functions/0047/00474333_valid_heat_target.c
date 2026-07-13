/*
 * Entry: 00474333
 * Name: valid_heat_target
 * Namespace: Global
 * Signature: int valid_heat_target(_OBJ76 * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl valid_heat_target(_OBJ76 *param_1,_OBJ76 *param_2)

{
  MAT_3D *pMVar1;
  int iVar2;
  float *pfVar3;
  MAT_3D *pMVar4;
  MAT_3D local_c4;
  float local_84 [6];
  float local_6c;
  float local_68;
  float local_64;
  MAT_3D local_44;
  
  pMVar1 = obj_rel_parent_matrix(&local_44,param_1,(_OBJ76 *)0x0);
  pfVar3 = local_84;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pfVar3 = pfVar3 + 1;
  }
  pMVar1 = obj_rel_parent_matrix(&local_c4,param_2,(_OBJ76 *)0x0);
  pMVar4 = &local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar4->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  if (0.84 < ABS(local_44.front_x * local_6c +
                 local_44.front_y * local_68 + local_44.front_z * local_64)) {
    return 1;
  }
  return 0;
}
