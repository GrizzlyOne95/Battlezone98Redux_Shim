/*
 * Entry: 0053dc27
 * Name: Tracer::Submit
 * Namespace: Tracer
 * Signature: void Submit(Tracer * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tracer::Submit(Tracer *this,CAMERA *param_1)

{
  POLYGON_SKIN PVar1;
  MAT_3D *pMVar2;
  long lVar3;
  int iVar4;
  _ZSORTING *p_Var5;
  float *pfVar6;
  float fVar7;
  MAT_3D local_c8;
  float local_88 [4];
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  double local_60;
  double local_58;
  double local_50;
  VECTOR_3D local_48;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  _ZSORTING *local_2c;
  float local_28;
  POLYGON_SKIN local_24;
  float local_20;
  float local_1c;
  POLYGON_SKIN local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  local_3c = *(float *)(this->_padding_ + 0x80);
  local_20 = *(float *)(this->_padding_ + 0x7c);
  if (this->shotDistance < local_20) {
    local_20 = this->shotDistance;
  }
  pMVar2 = Matrix_Multiply(&local_c8,(MAT_3D *)(this->_padding_ + 0x20),&param_1->Matrix);
  pfVar6 = local_88;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar6 = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pfVar6 = pfVar6 + 1;
  }
  local_1c = (float)local_60;
  local_18 = (POLYGON_SKIN)(float)local_58;
  local_14 = (float)local_50;
  local_2c = (_ZSORTING *)(local_1c + -(local_70 * local_20));
  local_28 = (float)local_18 + -(local_6c * local_20);
  local_24 = (POLYGON_SKIN)(local_14 + -(local_68 * local_20));
  local_48.x = -(local_70 * local_20) * 0.5 + local_1c;
  local_48.y = -(local_6c * local_20) * 0.5 + (float)local_18;
  local_48.z = -(local_68 * local_20) * 0.5 + local_14;
  lVar3 = Camera_Bounding_Sphere_Test(param_1,&local_48,*(float *)(this->_padding_ + 0x7c) * 0.5);
  p_Var5 = SortingTableCurrent;
  if (lVar3 < 1) {
    if ((useD3D != 0) || (local_48.z <= *(float *)(this->_padding_ + 0x78))) {
      PVar1 = *(POLYGON_SKIN *)(this->_padding_ + 0x70);
      local_88[0] = local_88[0] * local_3c;
      SortingTableCurrent->vcnt = 0;
      p_Var5->Skin_Color = PVar1;
      local_88[1] = local_88[1] * local_3c;
      p_Var5->Type = 10;
      local_88[2] = local_88[2] * local_3c;
      local_38 = local_88[3] * local_3c;
      p_Var5->Bitmap_Operation = 4;
      local_34 = local_78 * local_3c;
      local_30 = local_74 * local_3c;
      p_Var5[1].vcnt = (long)(local_88[0] + local_1c);
      p_Var5[1].Skin_Color = (POLYGON_SKIN)(local_18.Color + local_88[1]);
      p_Var5[1].Bitmap_Operation = (long)(local_88[2] + local_14);
      p_Var5[1].Type = (long)(local_88[0] + (float)local_2c);
      p_Var5[1].Z_Value = local_28 + local_88[1];
      p_Var5[1].Next = (_ZSORTING *)(local_88[2] + (float)local_24);
      p_Var5[1].Previous = (_ZSORTING *)((float)local_2c - local_88[0]);
      local_10 = local_1c - local_88[0];
      p_Var5[2].vcnt = (long)(local_28 - local_88[1]);
      p_Var5[2].Skin_Color = (POLYGON_SKIN)(local_24.Color - local_88[2]);
      local_c = (float)local_18 - local_88[1];
      local_8 = local_14 - local_88[2];
      p_Var5[2].Bitmap_Operation = (long)local_10;
      p_Var5[2].Type = (long)local_c;
      p_Var5[2].Z_Value = local_8;
      fVar7 = VectGetMin((VECTOR_3D *)(p_Var5 + 1),4);
      p_Var5->Z_Value = fVar7;
      ZSORTAdd(fVar7);
      p_Var5 = SortingTableCurrent;
      SortingTableCurrent->vcnt = 0;
      p_Var5->Skin_Color = PVar1;
      p_Var5->Type = 10;
      p_Var5->Bitmap_Operation = 4;
      p_Var5[1].vcnt = (long)(local_1c + local_38);
      p_Var5[1].Skin_Color = (POLYGON_SKIN)(local_18.Color + local_34);
      p_Var5[1].Bitmap_Operation = (long)(local_14 + local_30);
      p_Var5[1].Type = (long)(local_38 + (float)local_2c);
      p_Var5[1].Z_Value = local_34 + local_28;
      p_Var5[1].Next = (_ZSORTING *)((float)local_24 + local_30);
      p_Var5[1].Previous = (_ZSORTING *)((float)local_2c - local_38);
      p_Var5[2].vcnt = (long)(local_28 - local_34);
      local_10 = local_1c - local_38;
      p_Var5[2].Skin_Color = (POLYGON_SKIN)(local_24.Color - local_30);
      local_c = (float)local_18 - local_34;
      local_8 = local_14 - local_30;
      p_Var5[2].Bitmap_Operation = (long)local_10;
      p_Var5[2].Type = (long)local_c;
      p_Var5[2].Z_Value = local_8;
      fVar7 = VectGetMin((VECTOR_3D *)(p_Var5 + 1),4);
    }
    else {
      PVar1 = *(POLYGON_SKIN *)(this->_padding_ + 0x74);
      SortingTableCurrent[1].Type = 0;
      p_Var5->Bitmap_Operation = 0;
      p_Var5[1].Z_Value = 0.0;
      p_Var5->Skin_Color = PVar1;
      ((VECTOR_3D *)&p_Var5[1].vcnt)->x = local_1c;
      p_Var5[1].Skin_Color = local_18;
      p_Var5[1].Bitmap_Operation = (long)local_14;
      p_Var5->Type = 8;
      p_Var5->vcnt = 2;
      fVar7 = TerrainIntensity;
      p_Var5[1].Previous = local_2c;
      p_Var5[1].Next = (_ZSORTING *)fVar7;
      p_Var5[2].Bitmap_Operation = 0;
      p_Var5[2].Type = 0;
      p_Var5[2].vcnt = (long)local_28;
      p_Var5[2].Skin_Color = local_24;
      p_Var5[2].Z_Value = TerrainIntensity;
      fVar7 = GetMin((POINT_3D *)(p_Var5 + 1),2);
    }
    p_Var5->Z_Value = fVar7;
    ZSORTAdd(fVar7);
  }
  return;
}
