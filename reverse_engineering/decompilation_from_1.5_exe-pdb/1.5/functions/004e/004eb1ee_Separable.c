/*
 * Entry: 004eb1ee
 * Name: Separable
 * Namespace: Global
 * Signature: int Separable(tagENTITY * param_1, VECTOR_3D * param_2, tagENTITY * param_3, VECTOR_3D * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Separable(tagENTITY *param_1,VECTOR_3D *param_2,tagENTITY *param_3,VECTOR_3D *param_4)

{
  float fVar1;
  float fVar2;
  float *in_EAX;
  float *in_ECX;
  int in_EDX;
  
  fVar1 = *(float *)(in_EDX + 0x14) + (param_1->bSphere).radius;
  fVar2 = in_ECX[2] - in_EAX[2];
  if ((ABS(fVar2) <= fVar1) &&
     (fVar2 * fVar2 + (*in_ECX - *in_EAX) * (*in_ECX - *in_EAX) < fVar1 * fVar1)) {
    return 0;
  }
  return 1;
}
