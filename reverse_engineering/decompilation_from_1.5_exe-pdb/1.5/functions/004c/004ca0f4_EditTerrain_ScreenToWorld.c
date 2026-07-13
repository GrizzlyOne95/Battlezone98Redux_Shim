/*
 * Entry: 004ca0f4
 * Name: EditTerrain::ScreenToWorld
 * Namespace: EditTerrain
 * Signature: int ScreenToWorld(EditTerrain * this, VECTOR_3D * param_1, tagPOINT * param_2, CAMERA * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall
EditTerrain::ScreenToWorld(EditTerrain *this,VECTOR_3D *param_1,tagPOINT *param_2,CAMERA *param_3)

{
  VECTOR_3D_LONG VVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  pVVar2 = param_1;
  param_1->x = (float)DisplayInterface::currentCamera->View_Pyramid[0].x;
  param_1->y = (float)DisplayInterface::currentCamera->View_Pyramid[0].y;
  param_1->z = (float)DisplayInterface::currentCamera->View_Pyramid[0].z;
  local_10.x = ((float)param_2->x - DisplayInterface::currentCamera->Orig_x) /
               DisplayInterface::currentCamera->Const_x;
  local_10.y = ((float)param_2->y - DisplayInterface::currentCamera->Orig_y) /
               DisplayInterface::currentCamera->Const_y;
  local_10.z = 1.0;
  pVVar3 = Vector_Unrotate(&local_1c,&local_10,&DisplayInterface::currentCamera->Matrix);
  local_10.x = pVVar3->x;
  local_10.y = pVVar3->y;
  local_10.z = pVVar3->z;
  pVVar3 = Normalize_Vector(&local_1c,&local_10);
  local_10.x = pVVar3->x;
  local_10.y = pVVar3->y;
  local_10.z = pVVar3->z;
  param_1 = (VECTOR_3D *)TerrainVisibilityRange;
  local_1c.x = pVVar2->x;
  local_1c.y = pVVar2->y;
  local_1c.z = pVVar2->z;
  VVar1.y = (double)local_1c.y;
  VVar1.x = (double)local_1c.x;
  VVar1.z._0_4_ = SUB84((double)local_1c.z,0);
  VVar1.z._4_4_ = (int)((ulonglong)(double)local_1c.z >> 0x20);
  iVar4 = Terrain_GetIntersection(VVar1,*pVVar3,(float *)&param_1,(VECTOR_3D *)0x0);
  if (iVar4 != 0) {
    pVVar2->x = (float)param_1 * local_10.x + pVVar2->x;
    pVVar2->y = (float)param_1 * local_10.y + pVVar2->y;
    pVVar2->z = (float)param_1 * local_10.z + pVVar2->z;
  }
  return (uint)(iVar4 != 0);
}
