/*
 * Entry: 005380da
 * Name: Rocket::Submit
 * Namespace: Rocket
 * Signature: void Submit(Rocket * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Rocket::Submit(Rocket *this,CAMERA *param_1)

{
  _ZSORTING *p_Var1;
  float fVar2;
  _ZSORTING *p_Var3;
  MAT_3D *pMVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float fVar10;
  MAT_3D local_d0;
  float local_90 [4];
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  double local_68;
  double local_60;
  double local_58;
  VECTOR_3D local_50;
  Rocket *local_44;
  float local_40;
  float local_3c;
  float local_38;
  int local_34;
  float local_30;
  TEXTURE *local_2c;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  local_34 = this->_padding_;
  if ((*(byte *)(local_34 + 0x14) & 8) != 0) {
    iVar8 = this->_padding_;
    local_44 = this;
    if (0 < *(int *)(iVar8 + 0x7c)) {
      local_30 = *(float *)(iVar8 + 0x70);
      local_2c = *(TEXTURE **)(iVar8 + 0x74);
      pMVar4 = Matrix_Multiply(&local_d0,(MAT_3D *)(this->_padding_ + 0x20),&param_1->Matrix);
      pfVar9 = local_90;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar9 = pMVar4->right_x;
        pMVar4 = (MAT_3D *)&pMVar4->right_y;
        pfVar9 = pfVar9 + 1;
      }
      local_28 = (float)local_68;
      local_24 = (float)local_60;
      local_20 = (float)local_58;
      local_1c.x = local_28 + -(local_78 * (float)local_2c);
      local_1c.y = local_24 + -(local_74 * (float)local_2c);
      local_1c.z = local_20 + -(local_70 * (float)local_2c);
      local_50.x = -(local_78 * (float)local_2c) * 0.5 + local_28;
      local_50.y = -(local_74 * (float)local_2c) * 0.5 + local_24;
      local_50.z = -(local_70 * (float)local_2c) * 0.5 + local_20;
      lVar5 = Camera_Bounding_Sphere_Test(param_1,&local_50,(float)local_2c * 0.5 + local_30);
      if (lVar5 < 1) {
        iVar8 = this->_padding_;
        iVar6 = rand();
        p_Var1 = SortingTableCurrent;
        local_90[0] = local_90[0] * local_30;
        local_90[1] = local_90[1] * local_30;
        local_90[2] = local_90[2] * local_30;
        local_40 = local_90[3] * local_30;
        local_3c = local_80 * local_30;
        local_38 = local_7c * local_30;
        local_2c = (TEXTURE *)(iVar6 % *(int *)(iVar8 + 0x7c) + *(int *)(iVar8 + 0x78));
        SortingTableCurrent->vcnt = 0;
        p_Var1->Type = 10;
        p_Var1->Bitmap_Operation = 4;
        (p_Var1->Skin_Color).Texture = local_2c;
        p_Var1[1].vcnt = (long)(local_90[0] + local_28);
        p_Var1[1].Skin_Color = (POLYGON_SKIN)(local_24 + local_90[1]);
        p_Var1[1].Bitmap_Operation = (long)(local_90[2] + local_20);
        p_Var1[1].Type = (long)(local_90[0] + local_1c.x);
        p_Var1[1].Z_Value = local_1c.y + local_90[1];
        p_Var1[1].Next = (_ZSORTING *)(local_90[2] + local_1c.z);
        p_Var1[1].Previous = (_ZSORTING *)(local_1c.x - local_90[0]);
        local_10 = local_28 - local_90[0];
        p_Var1[2].vcnt = (long)(local_1c.y - local_90[1]);
        p_Var1[2].Skin_Color = (POLYGON_SKIN)(local_1c.z - local_90[2]);
        local_c = local_24 - local_90[1];
        local_8 = local_20 - local_90[2];
        p_Var1[2].Bitmap_Operation = (long)local_10;
        p_Var1[2].Type = (long)local_c;
        p_Var1[2].Z_Value = local_8;
        fVar10 = VectGetMin((VECTOR_3D *)(p_Var1 + 1),4);
        p_Var1->Z_Value = fVar10;
        ZSORTAdd(fVar10);
        p_Var1 = SortingTableCurrent;
        SortingTableCurrent->vcnt = 0;
        p_Var1->Type = 10;
        (p_Var1->Skin_Color).Texture = local_2c;
        p_Var1->Bitmap_Operation = 4;
        p_Var1[1].vcnt = (long)(local_28 + local_40);
        p_Var1[1].Skin_Color = (POLYGON_SKIN)(local_24 + local_3c);
        p_Var1[1].Bitmap_Operation = (long)(local_20 + local_38);
        p_Var1[1].Type = (long)(local_40 + local_1c.x);
        p_Var1[1].Z_Value = local_3c + local_1c.y;
        p_Var1[1].Next = (_ZSORTING *)(local_1c.z + local_38);
        p_Var1[1].Previous = (_ZSORTING *)(local_1c.x - local_40);
        p_Var1[2].vcnt = (long)(local_1c.y - local_3c);
        local_10 = local_28 - local_40;
        p_Var1[2].Skin_Color = (POLYGON_SKIN)(local_1c.z - local_38);
        local_c = local_24 - local_3c;
        local_8 = local_20 - local_38;
        p_Var1[2].Bitmap_Operation = (long)local_10;
        p_Var1[2].Type = (long)local_c;
        p_Var1[2].Z_Value = local_8;
        fVar10 = VectGetMin((VECTOR_3D *)(p_Var1 + 1),4);
        p_Var1->Z_Value = fVar10;
        ZSORTAdd(fVar10);
        this = local_44;
      }
    }
    if (0 < *(int *)(this->_padding_ + 0x88)) {
      p_Var1 = *(_ZSORTING **)(this->_padding_ + 0x80);
      if (*(int *)(this->_padding_ + 100) == 0) {
        local_1c.x = (float)*(double *)(local_34 + 0x48);
        local_1c.y = (float)*(double *)(local_34 + 0x50);
        local_1c.z = (float)*(double *)(local_34 + 0x58);
      }
      else {
        local_1c.x = (float)*(double *)(local_34 + 0x48) - *(float *)(local_34 + 0x38) * 0.05;
        local_1c.y = (float)*(double *)(local_34 + 0x50) - *(float *)(local_34 + 0x3c) * 0.05;
        local_1c.z = (float)*(double *)(local_34 + 0x58) - *(float *)(local_34 + 0x40) * 0.05;
      }
      Vector_Transform(&local_1c,&local_1c,1,&param_1->Matrix);
      lVar5 = Camera_Bounding_Sphere_Test(param_1,&local_1c,(float)p_Var1);
      if (lVar5 < 1) {
        iVar7 = rand();
        p_Var3 = SortingTableCurrent;
        iVar8 = *(int *)(this->_padding_ + 0x88);
        SortingTableCurrent->vcnt = 0;
        p_Var3->Type = 9;
        iVar6 = *(int *)(this->_padding_ + 0x84);
        p_Var3->Bitmap_Operation = 0x50004;
        (p_Var3->Skin_Color).Texture = (TEXTURE *)(iVar6 + iVar7 % iVar8);
        fVar10 = 1.0 / local_1c.z;
        p_Var3[1].vcnt = (long)(param_1->Const_x * fVar10 * local_1c.x + param_1->Orig_x);
        p_Var3[1].Skin_Color =
             (POLYGON_SKIN)(local_1c.y * fVar10 * param_1->Const_y + param_1->Orig_y);
        p_Var3[1].Bitmap_Operation = (long)local_1c.z;
        fVar2 = param_1->Const_x * fVar10 * (float)p_Var1;
        p_Var3[1].Type = (long)(fVar2 + fVar2);
        p_Var3[1].Z_Value = fVar10 * (float)p_Var1 * param_1->Const_y * -2.0;
        p_Var3[1].Previous = (_ZSORTING *)local_1c.x;
        p_Var3[2].vcnt = (long)local_1c.y;
        p_Var3[2].Skin_Color = (POLYGON_SKIN)local_1c.z;
        p_Var3[1].Next = p_Var1;
        p_Var3->Z_Value = local_1c.z - (float)p_Var1;
        ZSORTAdd(local_1c.z - (float)p_Var1);
      }
    }
  }
  return;
}
