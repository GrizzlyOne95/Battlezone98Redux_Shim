/*
 * Entry: 0052594e
 * Name: NewObj
 * Namespace: Global
 * Signature: _OBJ76 * NewObj(_OBJ76 * param_1, StructObjectType * param_2, long64 * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl NewObj(_OBJ76 *param_1,StructObjectType *param_2,long64 *param_3,int param_4)

{
  SPHERE *pSVar1;
  float *pfVar2;
  float *pfVar3;
  _OBJ76 *p_Var4;
  int iVar5;
  MAT_3D *pMVar6;
  MAT_3D *pMVar7;
  
  p_Var4 = create_obj_ext(param_1,param_3);
  if (p_Var4 != (_OBJ76 *)0x0) {
    pMVar7 = &p_Var4->transform;
    File_Matrix_To_I76_Matrix(pMVar7,&param_2->TransformMatrix);
    p_Var4->flags = param_2->ObjectFlags;
    iVar5 = _strnicmp((char *)param_3,"null",4);
    if ((((iVar5 == 0) && (pMVar7->right_x == 0.0)) && ((p_Var4->transform).right_y == 0.0)) &&
       ((p_Var4->transform).right_z == 0.0)) {
      pMVar6 = &Identity_Matrix;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar7->right_x = pMVar6->right_x;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
    }
    iVar5 = param_2->Class;
    if (((iVar5 == 1) || (iVar5 == 3)) || (iVar5 == 6)) {
      iVar5 = Craft_GetClass(&param_2->GeometryFile,iVar5);
      param_2->Class = iVar5;
    }
    ClassCreate(p_Var4,param_2->Class);
    if (param_4 == 0) {
      (p_Var4->bSphere).radius = param_2->SphereRadius;
      pSVar1 = &p_Var4->bSphere;
      (pSVar1->origin).x = (param_2->GeoCenter).x;
      (p_Var4->bSphere).origin.y = (param_2->GeoCenter).y;
      (p_Var4->bSphere).origin.z = (param_2->GeoCenter).z;
      (p_Var4->bBox).min.x = (pSVar1->origin).x - param_2->BoxHalfHeightX;
      pfVar2 = &(p_Var4->bSphere).origin.y;
      (p_Var4->bBox).max.x = param_2->BoxHalfHeightX + (pSVar1->origin).x;
      (p_Var4->bBox).min.y = *pfVar2 - param_2->BoxHalfHeightY;
      pfVar3 = &(p_Var4->bSphere).origin.z;
      (p_Var4->bBox).max.y = param_2->BoxHalfHeightY + *pfVar2;
      (p_Var4->bBox).min.z = *pfVar3 - param_2->BoxHalfHeightZ;
      (p_Var4->bBox).max.z = param_2->BoxHalfHeightZ + *pfVar3;
      if (param_2->Class == 0xf) {
        Spinner_SetRate(p_Var4,param_2->Target);
        Spinner_SetDDR(p_Var4,param_2->ddr);
      }
    }
  }
  return p_Var4;
}
