/*
 * Entry: 004f0629
 * Name: Camera_Set_Clipping_Rect
 * Namespace: Global
 * Signature: void Camera_Set_Clipping_Rect(CAMERA * param_1, long param_2, long param_3, long param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Camera_Set_Clipping_Rect(CAMERA *param_1,long param_2,long param_3,long param_4,long param_5)

{
  float fVar1;
  _GRAPHIC_BUFFER *p_Var2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  PLANE *pPVar8;
  float *pfVar9;
  int iVar10;
  PLANE local_3c;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  p_Var2 = param_1->Buffer;
  local_3c.surf_normal.x = (float)(p_Var2->Pane).x0;
  local_3c.surf_normal.y = (float)(p_Var2->Pane).y0;
  local_3c.surf_normal.z = (float)(p_Var2->Pane).x1;
  local_3c.dist = (float)(p_Var2->Pane).y1;
  Graphic_Buffer_Set_Pane(p_Var2,param_2,param_3,param_4,param_5);
  p_Var2 = param_1->Buffer;
  local_2c = (p_Var2->Pane).x0;
  local_28 = (p_Var2->Pane).y0;
  local_24 = (p_Var2->Pane).x1;
  local_20 = (p_Var2->Pane).y1;
  (p_Var2->Pane).x0 = (long)local_3c.surf_normal.x;
  (p_Var2->Pane).y0 = (long)local_3c.surf_normal.y;
  (p_Var2->Pane).x1 = (long)local_3c.surf_normal.z;
  (p_Var2->Pane).y1 = (long)local_3c.dist;
  param_1->Left = (float)local_2c;
  param_1->Bottom = (float)local_28;
  param_1->Right = (float)local_24;
  param_1->Top = (float)local_20;
  fVar5 = 1.0 / param_1->Const_x;
  fVar7 = fVar5 * 0.1;
  local_8 = 1.0 / param_1->Const_y;
  local_c = (float)local_2c - param_1->Orig_x;
  fVar4 = local_c * fVar7;
  param_1->View_Frustrum[0].x = fVar4;
  local_10 = (float)local_28 - param_1->Orig_y;
  fVar1 = local_10 * local_8 * 0.1;
  param_1->View_Frustrum[0].y = fVar1;
  param_1->View_Frustrum[0].z = 0.1;
  fVar3 = (float)local_24 - param_1->Orig_x;
  fVar7 = fVar3 * fVar7;
  param_1->View_Frustrum[1].x = fVar7;
  param_1->View_Frustrum[2].x = fVar7;
  param_1->View_Frustrum[1].y = fVar1;
  param_1->View_Frustrum[1].z = 0.1;
  fVar7 = (float)local_20 - param_1->Orig_y;
  fVar1 = fVar7 * local_8 * 0.1;
  param_1->View_Frustrum[2].y = fVar1;
  param_1->View_Frustrum[3].y = fVar1;
  param_1->View_Frustrum[2].z = 0.1;
  param_1->View_Frustrum[3].z = 0.1;
  param_1->View_Frustrum[3].x = fVar4;
  fVar1 = param_1->Max_Depth;
  if (!NAN(fVar1) && 1640.0 < fVar1 != (fVar1 == 1640.0)) {
    fVar1 = 1640.0;
  }
  fVar5 = fVar5 * fVar1;
  fVar4 = local_c * fVar5;
  param_1->View_Frustrum[4].x = fVar4;
  fVar6 = local_10 * local_8 * fVar1;
  param_1->View_Frustrum[4].y = fVar6;
  param_1->View_Frustrum[4].z = fVar1;
  fVar3 = fVar3 * fVar5;
  param_1->View_Frustrum[5].x = fVar3;
  param_1->View_Frustrum[6].x = fVar3;
  param_1->View_Frustrum[5].y = fVar6;
  param_1->View_Frustrum[5].z = fVar1;
  fVar7 = fVar7 * local_8 * fVar1;
  param_1->View_Frustrum[6].y = fVar7;
  param_1->View_Frustrum[6].z = fVar1;
  param_1->View_Frustrum[7].x = fVar4;
  param_1->View_Frustrum[7].y = fVar7;
  param_1->View_Frustrum[7].z = fVar1;
  local_1c.x = 0.0;
  local_1c.y = 0.0;
  local_1c.z = 0.0;
  pPVar8 = Plane_Equation(&local_3c,&local_1c,param_1->View_Frustrum + 4,param_1->View_Frustrum + 7)
  ;
  param_1->View_Volume[0].surf_normal.x = (pPVar8->surf_normal).x;
  param_1->View_Volume[0].surf_normal.y = (pPVar8->surf_normal).y;
  param_1->View_Volume[0].surf_normal.z = (pPVar8->surf_normal).z;
  param_1->View_Volume[0].dist = pPVar8->dist;
  pPVar8 = Plane_Equation(&local_3c,&local_1c,param_1->View_Frustrum + 5,param_1->View_Frustrum + 6)
  ;
  param_1->View_Volume[1].surf_normal.x = (pPVar8->surf_normal).x;
  param_1->View_Volume[1].surf_normal.y = (pPVar8->surf_normal).y;
  param_1->View_Volume[1].surf_normal.z = (pPVar8->surf_normal).z;
  param_1->View_Volume[1].dist = pPVar8->dist;
  pPVar8 = Plane_Equation(&local_3c,&local_1c,param_1->View_Frustrum + 4,param_1->View_Frustrum + 5)
  ;
  param_1->View_Volume[2].surf_normal.x = (pPVar8->surf_normal).x;
  param_1->View_Volume[2].surf_normal.y = (pPVar8->surf_normal).y;
  param_1->View_Volume[2].surf_normal.z = (pPVar8->surf_normal).z;
  param_1->View_Volume[2].dist = pPVar8->dist;
  pPVar8 = Plane_Equation(&local_3c,&local_1c,param_1->View_Frustrum + 6,param_1->View_Frustrum + 7)
  ;
  param_1->View_Volume[3].surf_normal.x = (pPVar8->surf_normal).x;
  param_1->View_Volume[3].surf_normal.y = (pPVar8->surf_normal).y;
  param_1->View_Volume[3].surf_normal.z = (pPVar8->surf_normal).z;
  param_1->View_Volume[3].dist = pPVar8->dist;
  pPVar8 = Plane_Equation(&local_3c,param_1->View_Frustrum + 4,param_1->View_Frustrum + 5,
                          param_1->View_Frustrum + 6);
  param_1->View_Volume[4].surf_normal.x = (pPVar8->surf_normal).x;
  param_1->View_Volume[4].surf_normal.y = (pPVar8->surf_normal).y;
  param_1->View_Volume[4].surf_normal.z = (pPVar8->surf_normal).z;
  param_1->View_Volume[4].dist = pPVar8->dist;
  pPVar8 = Plane_Equation(&local_3c,param_1->View_Frustrum,param_1->View_Frustrum + 1,
                          param_1->View_Frustrum + 2);
  param_1->View_Volume[5].surf_normal.x = (pPVar8->surf_normal).x;
  param_1->View_Volume[5].surf_normal.y = (pPVar8->surf_normal).y;
  param_1->View_Volume[5].surf_normal.z = (pPVar8->surf_normal).z;
  param_1->View_Volume[5].dist = pPVar8->dist;
  iVar10 = 4;
  pfVar9 = &param_1->View_Frustrum[4].y;
  do {
    local_1c.x = ((VECTOR_3D *)(pfVar9 + -1))->x + local_1c.x;
    iVar10 = iVar10 + -1;
    local_1c.y = *pfVar9 + local_1c.y;
    local_1c.z = pfVar9[1] + local_1c.z;
    pfVar9 = pfVar9 + 3;
  } while (iVar10 != 0);
  iVar10 = 6;
  pfVar9 = &param_1->View_Volume[0].surf_normal.y;
  do {
    if (((VECTOR_3D *)(pfVar9 + -1))->x * local_1c.x * 0.2 +
        *pfVar9 * local_1c.y * 0.2 + pfVar9[1] * local_1c.z * 0.2 + pfVar9[2] < 0.0) {
      ((VECTOR_3D *)(pfVar9 + -1))->x = -((VECTOR_3D *)(pfVar9 + -1))->x;
      *pfVar9 = -*pfVar9;
      pfVar9[1] = -pfVar9[1];
      pfVar9[2] = -pfVar9[2];
    }
    pfVar9 = pfVar9 + 4;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  return;
}
