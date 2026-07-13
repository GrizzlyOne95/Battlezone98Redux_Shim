/*
 * Entry: 0052baaa
 * Name: GetOrdBBox
 * Namespace: Global
 * Signature: BBOX * GetOrdBBox(BBOX * __return_storage_ptr__, VECTOR_3D * param_1, float param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BBOX * __cdecl
GetOrdBBox(BBOX *__return_storage_ptr__,VECTOR_3D *param_1,float param_2,VECTOR_3D *param_3)

{
  float *pfVar1;
  float *pfVar2;
  VECTOR_3D *pVVar3;
  BBOX *unaff_EBX;
  VECTOR_3D local_1c;
  float local_10;
  float fStack_c;
  float fStack_8;
  
  (unaff_EBX->min).x = (__return_storage_ptr__->min).x;
  (unaff_EBX->min).y = (__return_storage_ptr__->min).y;
  (unaff_EBX->min).z = (__return_storage_ptr__->min).z;
  pVVar3 = AddMultVectors(&local_1c,__return_storage_ptr__->min,(float)param_1,*(VECTOR_3D *)param_2
                         );
  local_10 = pVVar3->x;
  fStack_c = pVVar3->y;
  fStack_8 = pVVar3->z;
  pVVar3 = &unaff_EBX->max;
  pVVar3->x = local_10;
  (unaff_EBX->max).y = fStack_c;
  (unaff_EBX->max).z = fStack_8;
  if (pVVar3->x < (unaff_EBX->min).x) {
    std::swap<float>((float *)unaff_EBX,&pVVar3->x);
  }
  pfVar1 = &(unaff_EBX->max).y;
  pfVar2 = &(unaff_EBX->min).y;
  if (*pfVar1 < *pfVar2) {
    std::swap<float>(pfVar2,pfVar1);
  }
  pfVar1 = &(unaff_EBX->max).z;
  pfVar2 = &(unaff_EBX->min).z;
  if (*pfVar1 < *pfVar2) {
    std::swap<float>(pfVar2,pfVar1);
  }
  return unaff_EBX;
}
