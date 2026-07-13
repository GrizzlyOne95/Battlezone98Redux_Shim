/*
 * Entry: 00474fd2
 * Name: PointVelPoly
 * Namespace: Global
 * Signature: int PointVelPoly(POINT_VEL param_1, _clsn_poly * param_2, VECTOR_3D * param_3, float param_4, float * param_5, VECTOR_3D * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointVelPoly(POINT_VEL param_1,_clsn_poly *param_2,VECTOR_3D *param_3,float param_4,float *param_5,
            VECTOR_3D *param_6)

{
  float fVar1;
  float fVar2;
  float *in_EAX;
  VECTOR_3D *pVVar3;
  int iVar4;
  VECTOR_3D *__return_storage_ptr__;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  float local_8;
  
  fVar1 = param_1.p.z * in_EAX[2] + param_1.p.y * in_EAX[1] + *in_EAX * param_1.p.x + in_EAX[3];
  if (((-0.1 < fVar1) &&
      (fVar2 = param_1.v.z * in_EAX[2] + param_1.v.y * in_EAX[1] + *in_EAX * param_1.v.x,
      NAN(fVar2) || -1.1920929e-07 < fVar2 == (fVar2 == -1.1920929e-07))) &&
     (local_8 = -(fVar1 / fVar2), local_8 <= (float)param_3)) {
    __return_storage_ptr__ = &local_20;
    pVVar3 = AddMultVectors(__return_storage_ptr__,param_1.p,local_8,param_1.v);
    local_14.x = pVVar3->x;
    local_14.y = pVVar3->y;
    local_14.z = pVVar3->z;
    iVar4 = inside_poly(param_2,&local_14,__return_storage_ptr__);
    if (iVar4 != 0) {
      *(float *)param_4 = local_8;
      *param_5 = *in_EAX;
      param_5[1] = in_EAX[1];
      param_5[2] = in_EAX[2];
      return 1;
    }
  }
  return 0;
}
