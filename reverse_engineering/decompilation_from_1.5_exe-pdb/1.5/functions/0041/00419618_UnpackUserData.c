/*
 * Entry: 00419618
 * Name: UnpackUserData
 * Namespace: Global
 * Signature: void UnpackUserData(char * * param_1, lua_State * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnpackUserData(char **param_1,lua_State *param_2)

{
  float *pfVar1;
  byte bVar2;
  MAT_3D *pMVar3;
  VECTOR_3D *pVVar4;
  int iVar5;
  int *unaff_EBX;
  lua_State *unaff_EDI;
  MAT_3D local_48;
  MAT_3D *local_8;
  
  bVar2 = *(byte *)(*unaff_EBX + -1) & 0x1f;
  if (bVar2 == 1) {
    pVVar4 = NewVector(unaff_EDI);
    pfVar1 = (float *)*unaff_EBX;
    pVVar4->x = *pfVar1;
    pVVar4->y = pfVar1[1];
    pVVar4->z = pfVar1[2];
    *unaff_EBX = *unaff_EBX + 0xc;
  }
  else if (bVar2 == 2) {
    local_8 = NewMatrix(unaff_EDI);
    pMVar3 = NetUtil_ExpandMatrix(&local_48,(REDUCED_MAT)*(uchar (*) [14])*unaff_EBX);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      local_8->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      local_8 = (MAT_3D *)&local_8->right_y;
    }
    *unaff_EBX = *unaff_EBX + 0xe;
  }
  return;
}
