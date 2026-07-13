/*
 * Entry: 004fa34d
 * Name: Camera_Draw_Pixel
 * Namespace: Global
 * Signature: void Camera_Draw_Pixel(CAMERA * param_1, VECTOR_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Camera_Draw_Pixel(CAMERA *param_1,VECTOR_3D *param_2,long param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  _GRAPHIC_BUFFER *p_Var11;
  float fVar12;
  float fVar13;
  int iVar14;
  uint uVar15;
  int local_14;
  int local_c;
  
  if ((param_1->View_Frustrum[0].z <= param_2->z) && (param_2->z <= param_1->View_Frustrum[4].z)) {
    fVar12 = 1.0 / param_2->z;
    p_Var11 = param_1->Buffer;
    iVar7 = (p_Var11->Pane).x0;
    iVar8 = (p_Var11->Pane).y0;
    iVar9 = (p_Var11->Pane).x1;
    iVar10 = (p_Var11->Pane).y1;
    fVar1 = param_1->Const_x;
    fVar2 = param_2->x;
    fVar3 = param_1->Orig_x;
    fVar13 = (float)Float2Int;
    fVar4 = param_1->Const_y;
    fVar5 = param_2->y;
    fVar6 = param_1->Orig_y;
    if (0x1e0 < Device.Viewport.Width) {
      param_2 = (VECTOR_3D *)0x0;
      do {
        iVar14 = (int)param_2 / 2;
        uVar15 = (uint)param_2 & 0x80000001;
        if ((int)uVar15 < 0) {
          uVar15 = (uVar15 - 1 | 0xfffffffe) + 1;
        }
        local_c = SUB84((double)(fVar4 * fVar5 * fVar12 + fVar6 + fVar13),0);
        local_14 = SUB84((double)(fVar1 * fVar2 * fVar12 + fVar3 + fVar13),0);
        if (-1 < (int)((iVar9 - uVar15) - local_14 | (iVar10 - iVar14) - local_c |
                       (iVar14 - iVar8) + local_c | (uVar15 - iVar7) + local_14)) {
          p_Var11->Buffer[local_14 + iVar7 + uVar15 + (iVar14 + iVar8 + local_c) * p_Var11->Width] =
               (uchar)param_3;
        }
        param_2 = (VECTOR_3D *)((int)&param_2->x + 1);
      } while ((int)param_2 < 4);
    }
  }
  return;
}
