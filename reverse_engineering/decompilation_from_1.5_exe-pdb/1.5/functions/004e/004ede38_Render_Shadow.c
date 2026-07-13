/*
 * Entry: 004ede38
 * Name: Render_Shadow
 * Namespace: Global
 * Signature: void Render_Shadow(tagENTITY * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Shadow(tagENTITY *param_1,CAMERA *param_2)

{
  float fVar1;
  float fVar2;
  TEXTURE *pTVar3;
  VECTOR_3D *pVVar4;
  int iVar5;
  float *pfVar6;
  MAT_3D local_e0;
  VECTOR_3D local_a0;
  POINT_3D local_94;
  undefined4 local_7c;
  undefined4 uStack_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  VECTOR_3D local_34;
  undefined4 local_28;
  undefined4 uStack_24;
  float local_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 local_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  if ((param_1->obj76->flags & 0x400) == 0) {
    pVVar4 = Get_Shadow_Vector(&local_a0,param_1);
    Light_Vector.x = pVVar4->x;
    Light_Vector.y = pVVar4->y;
    Light_Vector.z = pVVar4->z;
    if ((0.01 <= Light_Vector.y) &&
       (iVar5 = Get_Shadow_Matrix(param_2,&local_e0,&param_1->worldOrigin,&param_1->obj76->transform
                                 ), iVar5 != 0)) {
      Vector_Transform(&local_34,param_1->shadowPoly,4,&local_e0);
      pTVar3 = Shadow_Texture;
      local_94.Vector.x = local_34.x;
      local_94.Vector.y = local_34.y;
      local_94.Vector.z = local_34.z;
      local_94.Texel.u = 0.0;
      local_94.Texel.v = 0.0;
      local_94.Texel.field2_0x8.luma = 0.0;
      local_7c = local_28;
      uStack_78 = uStack_24;
      local_74 = local_20;
      local_70 = 0x3f800000;
      local_6c = 0;
      local_68 = 0;
      local_64 = local_1c;
      uStack_60 = uStack_18;
      uStack_5c = uStack_14;
      local_58 = 0x3f800000;
      local_54 = 0x3f800000;
      local_50 = 0;
      local_4c = local_10;
      uStack_48 = uStack_c;
      uStack_44 = uStack_8;
      local_40 = 0;
      local_38 = 0;
      local_3c = 0x3f800000;
      if (Shadow_Texture == (TEXTURE *)0x0) {
        if (useD3D == 0) {
          __Camera_Software_Draw_polygon__(param_2,&local_94,4,(POLYGON_SKIN)0xfe,0xc0);
        }
        else {
          __Camera_Hardware_Draw_polygon__(param_2,&local_94,4,(POLYGON_SKIN)0xfe,0xc0);
        }
      }
      else {
        Vector_Transform(&local_34,param_1->shadowPoly,4,&param_1->obj76->transform);
        pfVar6 = &local_20;
        iVar5 = 3;
        fVar1 = local_34.x;
        fVar2 = local_34.z;
        do {
          if (pfVar6[-2] < local_34.x) {
            local_34.x = pfVar6[-2];
          }
          if (fVar1 < pfVar6[-2]) {
            fVar1 = pfVar6[-2];
          }
          if (*pfVar6 < local_34.z) {
            local_34.z = *pfVar6;
          }
          if (fVar2 < *pfVar6) {
            fVar2 = *pfVar6;
          }
          pfVar6 = pfVar6 + 3;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        DrawGroundPoly(param_2,&Center,fVar1 - local_34.x,fVar2 - local_34.z,pTVar3,0xd4);
      }
    }
  }
  return;
}
