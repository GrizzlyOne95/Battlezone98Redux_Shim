/*
 * Entry: 004da01e
 * Name: ShockWaveEffect::Submit
 * Namespace: ShockWaveEffect
 * Signature: void Submit(ShockWaveEffect * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ShockWaveEffect::Submit(ShockWaveEffect *this,CAMERA *param_1)

{
  VECTOR_3D *pVVar1;
  undefined4 *puVar2;
  _ZSORTING *p_Var3;
  long lVar4;
  long extraout_EAX;
  int iVar5;
  int iVar6;
  long *plVar7;
  int unaff_EDI;
  float *pfVar8;
  float fVar9;
  VECTOR_3D local_3c;
  double local_30;
  SINCOS local_28;
  float local_20;
  ShockWaveEffect *local_1c;
  float *local_18;
  float *local_14;
  int local_10;
  float local_c;
  float local_8;
  
  local_10 = 0;
  if (0 < this->shockwaveCount) {
    pfVar8 = &this->shockwaveList[0].outerRad;
    local_1c = this;
    do {
      local_14 = pfVar8;
      Vector_Transform(&local_3c,(VECTOR_3D *)(pfVar8 + -3),1,&param_1->Matrix);
      lVar4 = Camera_Bounding_Sphere_Test(param_1,&local_3c,*pfVar8);
      if (lVar4 < 1) {
        Set_Rounding(unaff_EDI);
        local_30 = (double)(pfVar8[5] + (float)Float2Int);
        Set_Rounding(unaff_EDI);
        GetSpriteTextureUV(local_30._0_4_,&local_20,&local_8,&local_c,(float *)&local_18);
        local_8 = 0.0;
        iVar6 = 0;
        do {
          local_28 = SinCos((float)(int)local_8 * 0.2617994);
          local_8 = (float)((int)local_8 + 1);
          *(float *)((int)&Vertex_Pool->x + iVar6) = *pfVar8 * local_28.Cos + local_3c.x;
          iVar5 = iVar6 + 0x18;
          *(float *)((int)&Vertex_Pool->y + iVar6) = *pfVar8 * local_28.Sin + local_3c.y;
          *(float *)((int)&Vertex_Pool->z + iVar6) = local_3c.z;
          *(float *)((int)&Vertex_Pool[1].x + iVar6) = pfVar8[1] * local_28.Cos + local_3c.x;
          *(float *)((int)&Vertex_Pool[1].y + iVar6) = pfVar8[1] * local_28.Sin + local_3c.y;
          *(float *)((int)&Vertex_Pool[1].z + iVar6) = local_3c.z;
          iVar6 = iVar5;
        } while (iVar5 < 0x240);
        local_c = 0.0;
        local_18 = pfVar8 + 5;
        local_8 = 0.0;
        do {
          p_Var3 = SortingTableCurrent;
          if (local_c == 0.0) {
            iVar6 = 0x2e;
          }
          else {
            iVar6 = (int)local_c + -2;
          }
          SortingTableCurrent->vcnt = 0;
          p_Var3->Type = 10;
          p_Var3->Bitmap_Operation = 4;
          _ftol2_sse();
          (p_Var3->Skin_Color).Color = extraout_EAX;
          pVVar1 = Vertex_Pool + iVar6;
          p_Var3[1].vcnt = (long)pVVar1->x;
          p_Var3[1].Skin_Color = (POLYGON_SKIN)pVVar1->y;
          p_Var3[1].Bitmap_Operation = (long)pVVar1->z;
          plVar7 = (long *)((int)&Vertex_Pool->x + (int)local_8);
          p_Var3[1].Type = *plVar7;
          p_Var3[1].Z_Value = (float)plVar7[1];
          p_Var3[1].Next = (_ZSORTING *)plVar7[2];
          puVar2 = (undefined4 *)((int)&Vertex_Pool[1].x + (int)local_8);
          p_Var3[1].Previous = (_ZSORTING *)*puVar2;
          p_Var3[2].vcnt = puVar2[1];
          p_Var3[2].Skin_Color = *(POLYGON_SKIN *)(puVar2 + 2);
          pVVar1 = Vertex_Pool + iVar6 + 1;
          p_Var3[2].Bitmap_Operation = (long)pVVar1->x;
          p_Var3[2].Type = (long)pVVar1->y;
          p_Var3[2].Z_Value = pVVar1->z;
          fVar9 = VectGetMin((VECTOR_3D *)(p_Var3 + 1),4);
          p_Var3->Z_Value = fVar9;
          ZSORTAdd(fVar9);
          local_c = (float)((int)local_c + 2);
          local_8 = (float)((int)local_8 + 0x18);
          this = local_1c;
          pfVar8 = local_14;
        } while ((int)local_8 < 0x240);
      }
      local_10 = local_10 + 1;
      pfVar8 = pfVar8 + 9;
    } while (local_10 < this->shockwaveCount);
  }
  return;
}
