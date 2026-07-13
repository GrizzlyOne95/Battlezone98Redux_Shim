/*
 * Entry: 0045eba9
 * Name: GetPosition
 * Namespace: Global
 * Signature: bool GetPosition(VECTOR_3D * param_1, AiPath * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GetPosition(VECTOR_3D *param_1,AiPath *param_2,int param_3)

{
  float *pfVar1;
  int in_EAX;
  int iVar2;
  float *unaff_EDI;
  float local_8;
  
  if (in_EAX != 0) {
    iVar2 = Clamp((int)param_1,0,*(int *)(in_EAX + 4) + -1);
    pfVar1 = (float *)(*(int *)(in_EAX + 8) + iVar2 * 8);
    Terrain_GetHeightAndNormal((double)*pfVar1,(double)pfVar1[1],&local_8,(VECTOR_3D *)0x0);
    *unaff_EDI = *pfVar1;
    unaff_EDI[1] = local_8;
    unaff_EDI[2] = pfVar1[1];
  }
  return in_EAX != 0;
}
