/*
 * Entry: 004c368f
 * Name: ConstructionBlob::Submit
 * Namespace: ConstructionBlob
 * Signature: void Submit(ConstructionBlob * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionBlob::Submit(ConstructionBlob *this,CAMERA *param_1)

{
  int iVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  _ZSORTING *p_Var6;
  _ZSORTING *p_Var7;
  long lVar8;
  int unaff_EDI;
  VECTOR_3D local_28;
  _ZSORTING *local_1c;
  double local_18;
  int local_10;
  ConstructionBlob *local_c;
  Blob *local_8;
  
  local_c = this;
  local_10 = Set_Rounding(unaff_EDI);
  local_8 = this->blobList;
  if (local_8 < this->blobPtr) {
    do {
      local_28.x = (local_8->sphere).origin.x;
      local_28.y = (local_8->sphere).origin.y;
      local_28.z = (local_8->sphere).origin.z;
      local_1c = (_ZSORTING *)(local_8->sphere).radius;
      Vector_Transform(&local_28,&local_28,1,&param_1->Matrix);
      lVar8 = Camera_Bounding_Sphere_Test(param_1,&local_28,(float)local_1c);
      p_Var7 = SortingTableCurrent;
      if (lVar8 < 1) {
        iVar1 = local_c->blobFrames;
        iVar3 = local_c->blobIndex;
        iVar4 = local_c->blobTexture;
        fVar2 = local_8->scale;
        p_Var6 = SortingTableCurrent + 1;
        fVar5 = (float)Float2Int;
        SortingTableCurrent->vcnt = 0;
        p_Var7->Type = 9;
        p_Var7->Bitmap_Operation = 0x50004;
        local_18 = (double)((float)iVar1 * fVar2 + fVar5);
        (p_Var7->Skin_Color).Texture = (TEXTURE *)(local_18._0_4_ + iVar3 + iVar4);
        fVar2 = 1.0 / local_28.z;
        p_Var7[1].vcnt = (long)(param_1->Const_x * local_28.x * fVar2 + param_1->Orig_x);
        p_Var7[1].Skin_Color =
             (POLYGON_SKIN)(local_28.y * fVar2 * param_1->Const_y + param_1->Orig_y);
        p_Var7[1].Bitmap_Operation = (long)local_28.z;
        fVar5 = param_1->Const_x * fVar2 * (float)local_1c;
        p_Var7[1].Type = (long)(fVar5 + fVar5);
        p_Var7[1].Z_Value = fVar2 * (float)local_1c * param_1->Const_y * -2.0;
        p_Var6->Previous = (_ZSORTING *)local_28.x;
        p_Var7[2].vcnt = (long)local_28.y;
        p_Var7[2].Skin_Color = (POLYGON_SKIN)local_28.z;
        p_Var7[1].Next = local_1c;
        p_Var7->Z_Value = local_28.z - (float)local_1c;
        ZSORTAdd(local_28.z - (float)local_1c);
      }
      local_8 = local_8 + 1;
    } while (local_8 < local_c->blobPtr);
  }
  Set_Rounding(unaff_EDI);
  return;
}
