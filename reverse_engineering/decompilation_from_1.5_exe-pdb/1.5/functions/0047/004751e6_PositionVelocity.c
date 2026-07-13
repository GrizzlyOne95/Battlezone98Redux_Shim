/*
 * Entry: 004751e6
 * Name: PositionVelocity
 * Namespace: Global
 * Signature: POINT_VEL * PositionVelocity(POINT_VEL * __return_storage_ptr__, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

POINT_VEL * __cdecl PositionVelocity(POINT_VEL *__return_storage_ptr__,tagENTITY *param_1)

{
  float fVar1;
  float fVar2;
  POINT_VEL *pPVar3;
  tagENTITY *ptVar4;
  SPHERE *pSVar5;
  SPHERE local_24 [2];
  
  ptVar4 = param_1;
  pPVar3 = __return_storage_ptr__;
  ClassGetVelocity(param_1->obj76,&__return_storage_ptr__->v,(float *)&__return_storage_ptr__);
  pSVar5 = Entity_WorldSphere(local_24,ptVar4);
  fVar1 = (pSVar5->origin).y;
  fVar2 = (pSVar5->origin).z;
  (pPVar3->p).x = (pSVar5->origin).x;
  (pPVar3->p).y = fVar1;
  (pPVar3->p).z = fVar2;
  return pPVar3;
}
