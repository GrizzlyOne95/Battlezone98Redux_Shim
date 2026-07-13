/*
 * Entry: 004733f9
 * Name: CreateBBoxe
 * Namespace: Global
 * Signature: void CreateBBoxe(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CreateBBoxe(tagENTITY *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  SPHERE *pSVar5;
  SPHERE local_24 [2];
  
  pSVar5 = Entity_WorldSphere(local_24,param_1);
  fVar1 = (pSVar5->origin).x;
  fVar2 = (pSVar5->origin).y;
  fVar3 = (pSVar5->origin).z;
  fVar4 = pSVar5->radius;
  (param_1->bBox).min.x = fVar1 - fVar4;
  (param_1->bBox).min.y = fVar2 - fVar4;
  (param_1->bBox).min.z = fVar3 - fVar4;
  (param_1->bBox).max.x = fVar1 + fVar4;
  (param_1->bBox).max.y = fVar2 + fVar4;
  (param_1->bBox).max.z = fVar4 + fVar3;
  return;
}
