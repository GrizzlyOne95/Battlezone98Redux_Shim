/*
 * Entry: 00473452
 * Name: CreateMovingBBoxe
 * Namespace: Global
 * Signature: void CreateMovingBBoxe(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CreateMovingBBoxe(tagENTITY *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  SPHERE *pSVar4;
  SPHERE local_38;
  float local_28;
  float local_24;
  float local_20;
  float fStack_1c;
  VECTOR_3D local_18;
  float local_c;
  float local_8;
  
  local_8 = TimeStep();
  pSVar4 = Entity_WorldSphere(&local_38,param_1);
  local_28 = (pSVar4->origin).x;
  local_24 = (pSVar4->origin).y;
  local_20 = (pSVar4->origin).z;
  fStack_1c = pSVar4->radius;
  ClassGetVelocity(param_1->obj76,&local_18,&local_c);
  (param_1->bBox).min.x = local_28;
  (param_1->bBox).min.y = local_24;
  (param_1->bBox).min.z = local_20;
  fVar1 = local_18.x * local_8 + local_28;
  (param_1->bBox).max.x = fVar1;
  fVar2 = local_18.y * local_8 + local_24;
  (param_1->bBox).max.y = fVar2;
  fVar3 = local_18.z * local_8 + local_20;
  (param_1->bBox).max.z = fVar3;
  if (fVar1 < local_28) {
    (param_1->bBox).min.x = fVar1;
    (param_1->bBox).max.x = local_28;
  }
  if (fVar2 < local_24) {
    (param_1->bBox).min.y = fVar2;
    (param_1->bBox).max.y = local_24;
  }
  if (fVar3 < local_20) {
    (param_1->bBox).min.z = fVar3;
    (param_1->bBox).max.z = local_20;
  }
  (param_1->bBox).min.x = (param_1->bBox).min.x - (param_1->bSphere).radius;
  (param_1->bBox).min.y = (param_1->bBox).min.y - (param_1->bSphere).radius;
  (param_1->bBox).min.z = (param_1->bBox).min.z - (param_1->bSphere).radius;
  (param_1->bBox).max.x = (param_1->bBox).max.x + (param_1->bSphere).radius;
  (param_1->bBox).max.y = (param_1->bBox).max.y + (param_1->bSphere).radius;
  (param_1->bBox).max.z = (param_1->bBox).max.z + (param_1->bSphere).radius;
  return;
}
