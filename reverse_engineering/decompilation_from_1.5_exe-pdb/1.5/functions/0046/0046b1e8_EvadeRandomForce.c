/*
 * Entry: 0046b1e8
 * Name: EvadeRandomForce
 * Namespace: Global
 * Signature: void EvadeRandomForce(GameObject * param_1, float param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EvadeRandomForce(GameObject *param_1,float param_2,VECTOR_3D *param_3)

{
  float *unaff_ESI;
  int unaff_EDI;
  float fVar1;
  float fVar2;
  
  fVar1 = Get_TimeLocal();
  fVar2 = Noise1D((float)*(int *)(unaff_EDI + 0x154) + fVar1 * 0.5);
  *unaff_ESI = fVar2 * (float)param_1 + *unaff_ESI;
  fVar1 = Noise1D((float)*(int *)(unaff_EDI + 0x154) + fVar1 * 0.5 + 17.59);
  unaff_ESI[2] = fVar1 * (float)param_1 + unaff_ESI[2];
  return;
}
