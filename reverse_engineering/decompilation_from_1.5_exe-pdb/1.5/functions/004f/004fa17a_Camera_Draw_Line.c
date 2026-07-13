/*
 * Entry: 004fa17a
 * Name: Camera_Draw_Line
 * Namespace: Global
 * Signature: void Camera_Draw_Line(CAMERA * param_1, VECTOR_3D * param_2, VECTOR_3D * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Camera_Draw_Line(CAMERA *param_1,VECTOR_3D *param_2,VECTOR_3D *param_3,long param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  long local_24;
  long local_1c;
  long local_14;
  long local_c;
  
  fVar2 = param_2->z - param_1->View_Frustrum[0].z;
  uVar4 = ((uint)fVar2 & 0xbfffffff | (uint)(param_3->z - param_1->View_Frustrum[0].z) >> 1) >> 0x1e
  ;
  if (uVar4 != 3) {
    if (uVar4 != 0) {
      fVar3 = (param_1->View_Frustrum[0].z - param_2->z) / (param_3->z - param_2->z);
      fVar1 = param_1->View_Frustrum[0].z;
      if (((uint)fVar2 & 0x80000000) == 0) {
        param_3->z = fVar1;
        param_3->x = (param_3->x - param_2->x) * fVar3 + param_2->x;
        param_3->y = (param_3->y - param_2->y) * fVar3 + param_2->y;
      }
      else {
        param_2->z = fVar1;
        param_2->x = (param_3->x - param_2->x) * fVar3 + param_2->x;
        param_2->y = (param_3->y - param_2->y) * fVar3 + param_2->y;
      }
    }
    fVar2 = param_1->View_Frustrum[4].z - param_2->z;
    uVar4 = ((uint)fVar2 & 0xbfffffff | (uint)(param_1->View_Frustrum[4].z - param_3->z) >> 1) >>
            0x1e;
    if (uVar4 != 3) {
      if (uVar4 != 0) {
        fVar3 = (param_1->View_Frustrum[4].z - param_2->z) / (param_3->z - param_2->z);
        fVar1 = param_1->View_Frustrum[4].z;
        if (((uint)fVar2 & 0x80000000) == 0) {
          param_3->z = fVar1;
          param_3->x = (param_3->x - param_2->x) * fVar3 + param_2->x;
          param_3->y = (param_3->y - param_2->y) * fVar3 + param_2->y;
        }
        else {
          param_2->z = fVar1;
          param_2->x = (param_3->x - param_2->x) * fVar3 + param_2->x;
          param_2->y = (param_3->y - param_2->y) * fVar3 + param_2->y;
        }
      }
      fVar2 = 1.0 / param_2->z;
      fVar1 = (float)Float2Int;
      fVar3 = 1.0 / param_3->z;
      local_c = SUB84((double)(param_3->y * param_1->Const_y * fVar3 + param_1->Orig_y + fVar1),0);
      local_14 = SUB84((double)(param_1->Const_x * param_3->x * fVar3 + param_1->Orig_x + fVar1),0);
      local_1c = SUB84((double)(param_2->y * param_1->Const_y * fVar2 + param_1->Orig_y + fVar1),0);
      local_24 = SUB84((double)(param_2->x * param_1->Const_x * fVar2 + param_1->Orig_x + fVar1),0);
      Graphic_Line(param_1->Buffer,local_24,local_1c,local_14,local_c,param_4,SOLID_PIXELS);
    }
  }
  return;
}
