/*
 * Entry: 004c19f9
 * Name: BoundingBox::DrawBox
 * Namespace: BoundingBox
 * Signature: void DrawBox(BoundingBox * this, VECTOR_3D * param_1, VECTOR_3D * param_2, MAT_3D * param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
BoundingBox::DrawBox
          (BoundingBox *this,VECTOR_3D *param_1,VECTOR_3D *param_2,MAT_3D *param_3,long param_4)

{
  tagPOINT *ptVar1;
  int *piVar2;
  VECTOR_3D *pVVar3;
  tagPOINT tVar4;
  tagPOINT local_a4 [8];
  VECTOR_3D local_64;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_64.x = param_1->x;
  local_64.y = param_1->y;
  local_64.z = param_1->z;
  local_58 = param_1->x;
  local_54 = param_1->y;
  local_50 = param_2->z;
  local_4c = param_1->x;
  local_48 = param_2->y;
  local_44 = param_1->z;
  local_40 = param_1->x;
  local_3c = param_2->y;
  local_38 = param_2->z;
  local_34 = param_2->x;
  local_30 = param_1->y;
  local_2c = param_1->z;
  local_28 = param_2->x;
  local_24 = param_1->y;
  local_20 = param_2->z;
  local_1c = param_2->x;
  local_18 = param_2->y;
  local_14 = param_1->z;
  local_10 = param_2->x;
  local_c = param_2->y;
  local_8 = param_2->z;
  if (param_3 != (MAT_3D *)0x0) {
    Vector_Transform(&local_64,&local_64,8,param_3);
  }
  param_3 = (MAT_3D *)0x0;
  ptVar1 = local_a4;
  pVVar3 = &local_64;
  do {
    tVar4 = WorldToScreen(pVVar3,DisplayInterface::currentCamera,(float *)&param_1);
    *ptVar1 = tVar4;
    if ((float)param_1 < 0.0) {
      return;
    }
    param_3 = (MAT_3D *)((int)&param_3->right_x + 1);
    pVVar3 = pVVar3 + 1;
    ptVar1 = ptVar1 + 1;
  } while ((int)param_3 < 8);
  piVar2 = &DAT_005e4154;
  do {
    Graphic_Line(DisplayInterface::currentBuffer,local_a4[piVar2[-1]].x,local_a4[piVar2[-1]].y,
                 local_a4[*piVar2].x,local_a4[*piVar2].y,param_4,SOLID_PIXELS);
    piVar2 = piVar2 + 2;
  } while ((int)piVar2 < 0x5e41b4);
  return;
}
