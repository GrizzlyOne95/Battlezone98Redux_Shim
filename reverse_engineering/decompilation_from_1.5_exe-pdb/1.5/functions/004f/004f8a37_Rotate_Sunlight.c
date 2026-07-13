/*
 * Entry: 004f8a37
 * Name: Rotate_Sunlight
 * Namespace: Global
 * Signature: void Rotate_Sunlight(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Rotate_Sunlight(void)

{
  MAT_3D *pMVar1;
  VECTOR_3D *pVVar2;
  int iVar3;
  MAT_3D *pMVar4;
  MAT_3D local_9c;
  MAT_3D local_5c;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  local_10.x = 0.0;
  local_10.y = 1.0;
  local_10.z = 0.0;
  pMVar1 = Build_Axis_Rotation_Matrix
                     (&local_9c,TOD_tbl[Lights_Struct.TOD_entry].Angle,__Earth_Axis__.x,
                      __Earth_Axis__.y,__Earth_Axis__.z);
  pMVar4 = &local_5c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  pVVar2 = Vector_Rotate(&local_1c,&local_10,&local_5c);
  Sun_Light.x = pVVar2->x;
  Sun_Light.y = pVVar2->y;
  Sun_Light.z = pVVar2->z;
  return;
}
