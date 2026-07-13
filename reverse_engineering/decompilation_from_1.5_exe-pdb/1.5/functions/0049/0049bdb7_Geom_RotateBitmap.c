/*
 * Entry: 0049bdb7
 * Name: Geom_RotateBitmap
 * Namespace: Global
 * Signature: void Geom_RotateBitmap(_OBJ76 * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Geom_RotateBitmap(_OBJ76 *param_1,CAMERA *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D *pVVar4;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  local_10.x = (float)((float10)param_2->View_Pyramid[0].x - (float10)(param_1->transform).posit_x);
  local_10.z = (float)((float10)param_2->View_Pyramid[0].z - (float10)(param_1->transform).posit_z);
  local_10.y = 0.0;
  pVVar4 = Normalize_Vector(&local_28,&local_10);
  local_28.x = (param_1->transform).up_x;
  local_28.y = (param_1->transform).up_y;
  local_10.x = pVVar4->x;
  local_28.z = (param_1->transform).up_z;
  local_10.y = pVVar4->y;
  local_10.z = pVVar4->z;
  local_1c.x = local_28.x;
  local_1c.y = local_28.y;
  local_1c.z = local_28.z;
  pVVar4 = Cross_Product(&local_34,&local_28,&local_10);
  local_1c.x = pVVar4->x;
  local_1c.y = pVVar4->y;
  local_1c.z = pVVar4->z;
  pVVar4 = Normalize_Vector(&local_34,&local_1c);
  fVar1 = pVVar4->x;
  fVar2 = pVVar4->y;
  fVar3 = pVVar4->z;
  (param_1->transform).front_x = local_10.x;
  (param_1->transform).front_y = local_10.y;
  (param_1->transform).front_z = local_10.z;
  (param_1->transform).right_x = fVar1;
  (param_1->transform).right_y = fVar2;
  (param_1->transform).right_z = fVar3;
  return;
}
