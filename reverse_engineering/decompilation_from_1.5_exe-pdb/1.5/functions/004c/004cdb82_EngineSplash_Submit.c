/*
 * Entry: 004cdb82
 * Name: EngineSplash::Submit
 * Namespace: EngineSplash
 * Signature: void Submit(EngineSplash * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EngineSplash::Submit(EngineSplash *this,CAMERA *param_1)

{
  double dVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  _ZSORTING *p_Var4;
  MAT_3D *pMVar5;
  long lVar6;
  VECTOR_3D *pVVar7;
  int iVar8;
  Splash *pSVar9;
  EngineSplash *pEVar10;
  int unaff_EDI;
  Splash *pSVar11;
  float fVar12;
  MAT_3D local_b4;
  VECTOR_3D local_74;
  VECTOR_3D local_68;
  float local_5c;
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
  int local_20;
  undefined4 uStack_1c;
  int local_18;
  VECTOR_3D local_14;
  EngineSplash *local_8;
  
  local_8 = this;
  local_18 = Set_Rounding(unaff_EDI);
  this->splashIndex = this->splashIndex + 1;
  if (this->splashVariance <= this->splashIndex) {
    this->splashIndex = 0;
  }
  pSVar9 = this->splashList;
  if (pSVar9 < this->splashPtr) {
    do {
      pMVar5 = Matrix_Multiply(&local_b4,&pSVar9->transform,&param_1->Matrix);
      pEVar10 = local_8;
      pSVar11 = pSVar9;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        (pSVar11->transform).right_x = pMVar5->right_x;
        pMVar5 = (MAT_3D *)&pMVar5->right_y;
        pSVar11 = (Splash *)&(pSVar11->transform).right_y;
      }
      local_44 = (float)(pSVar9->transform).posit_x;
      local_40 = (float)(pSVar9->transform).posit_y;
      local_3c = (float)(pSVar9->transform).posit_z;
      local_14.x = local_44;
      local_14.y = local_40;
      local_14.z = local_3c;
      lVar6 = Camera_Bounding_Sphere_Test(param_1,&local_14,local_8->splashRadius);
      if (lVar6 < 1) {
        dVar1 = (double)((float)pEVar10->splashFrames * pSVar9->scale + (float)Float2Int);
        local_2c = (pSVar9->transform).front_x;
        local_20 = SUB84(dVar1,0);
        _local_20 = CONCAT44((int)((ulonglong)dVar1 >> 0x20),
                             local_20 + pEVar10->splashTexture + pEVar10->splashIndex);
        local_28 = (pSVar9->transform).front_y;
        local_24 = (pSVar9->transform).front_z;
        VVar2.x = (pSVar9->transform).front_x;
        VVar2.y = (pSVar9->transform).front_y;
        VVar2.z = (pSVar9->transform).front_z;
        pVVar7 = ScaleVector(&local_68,local_8->splashRadius,VVar2);
        local_5c = (pSVar9->transform).right_x;
        local_58 = (pSVar9->transform).right_y;
        local_50 = pVVar7->x;
        local_54 = (pSVar9->transform).right_z;
        VVar3.x = (pSVar9->transform).right_x;
        VVar3.y = (pSVar9->transform).right_y;
        VVar3.z = (pSVar9->transform).right_z;
        local_4c = pVVar7->y;
        local_48 = pVVar7->z;
        pVVar7 = ScaleVector(&local_74,local_8->splashRadius,VVar3);
        p_Var4 = SortingTableCurrent;
        local_38 = pVVar7->x;
        local_34 = pVVar7->y;
        local_30 = pVVar7->z;
        SortingTableCurrent->vcnt = 0;
        (p_Var4->Skin_Color).Color = local_20;
        p_Var4->Type = 10;
        p_Var4->Bitmap_Operation = 4;
        p_Var4[1].vcnt = (long)((local_14.x + local_50) - local_38);
        p_Var4[1].Skin_Color = (POLYGON_SKIN)((local_14.y + local_4c) - local_34);
        p_Var4[1].Bitmap_Operation = (long)((local_14.z + local_48) - local_30);
        p_Var4[1].Type = (long)(local_38 + local_50 + local_14.x);
        p_Var4[1].Z_Value = local_34 + local_4c + local_14.y;
        p_Var4[1].Next = (_ZSORTING *)(local_30 + local_48 + local_14.z);
        p_Var4[1].Previous = (_ZSORTING *)((local_14.x - local_50) + local_38);
        p_Var4[2].vcnt = (long)((local_14.y - local_4c) + local_34);
        p_Var4[2].Skin_Color = (POLYGON_SKIN)((local_14.z - local_48) + local_30);
        p_Var4[2].Bitmap_Operation = (long)((local_14.x - local_50) - local_38);
        p_Var4[2].Type = (long)((local_14.y - local_4c) - local_34);
        p_Var4[2].Z_Value = (local_14.z - local_48) - local_30;
        fVar12 = VectGetMin((VECTOR_3D *)(p_Var4 + 1),4);
        p_Var4->Z_Value = fVar12;
        ZSORTAdd(fVar12);
        pEVar10 = local_8;
      }
      pSVar9 = pSVar9 + 1;
      this = local_8;
    } while (pSVar9 < pEVar10->splashPtr);
  }
  this->splashPtr = this->splashList;
  Set_Rounding(unaff_EDI);
  return;
}
