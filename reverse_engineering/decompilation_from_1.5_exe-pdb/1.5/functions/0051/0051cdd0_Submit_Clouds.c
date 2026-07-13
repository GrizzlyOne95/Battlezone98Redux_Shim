/*
 * Entry: 0051cdd0
 * Name: Submit_Clouds
 * Namespace: Global
 * Signature: void Submit_Clouds(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Clouds(CAMERA *param_1)

{
  float fVar1;
  TEXTURE *pTVar2;
  int unaff_EBX;
  float unaff_ESI;
  int *piVar3;
  int local_10;
  int local_8;
  
  local_10 = CloudSet.cloudCount;
  if (CloudSet.cloudCount != 0) {
    __CIfmod();
    __CIfmod();
    if (0 < local_10) {
      piVar3 = &VisibleCloud[0].type;
      do {
        fVar1 = CloudSet.size[*piVar3];
        pTVar2 = CloudSet.texture[*piVar3];
        local_8 = 9;
        do {
          GenerateCloudPoly(param_1,pTVar2,(VECTOR_3D *)(fVar1 * 0.5),unaff_ESI,unaff_EBX);
          local_8 = local_8 + -1;
        } while (0 < local_8);
        local_10 = local_10 + -1;
        piVar3 = piVar3 + 5;
      } while (0 < local_10);
    }
  }
  return;
}
