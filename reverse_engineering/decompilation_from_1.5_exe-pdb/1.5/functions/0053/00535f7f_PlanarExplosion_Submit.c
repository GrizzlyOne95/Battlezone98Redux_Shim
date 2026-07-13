/*
 * Entry: 00535f7f
 * Name: PlanarExplosion::Submit
 * Namespace: PlanarExplosion
 * Signature: void Submit(PlanarExplosion * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlanarExplosion::Submit(PlanarExplosion *this,CAMERA *param_1)

{
  int iVar1;
  _ZSORTING *p_Var2;
  long lVar3;
  VECTOR_3D *pVVar4;
  int unaff_EDI;
  float fVar5;
  POLYGON_SKIN local_4c;
  long lStack_48;
  long lStack_44;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  double local_10;
  MAT_3D *local_8;
  
  iVar1 = this->_padding_;
  local_1c.x = *(float *)(iVar1 + 200);
  local_1c.y = *(float *)(iVar1 + 0xcc);
  local_1c.z = *(float *)(iVar1 + 0xd0);
  Vector_Transform((VECTOR_3D *)&local_4c,&local_1c,1,(MAT_3D *)(iVar1 + 0x20));
  local_8 = &param_1->Matrix;
  Vector_Transform(&local_1c,(VECTOR_3D *)&local_4c,1,local_8);
  fVar5 = *(float *)(this->_padding_ + 0xd4);
  Set_Rounding(unaff_EDI);
  local_10 = (double)((float)this->_padding_ + (float)Float2Int);
  Set_Rounding(unaff_EDI);
  if ((((byte)D3IniFlags & 1) == 0) || (6400.0 <= local_1c.x * local_1c.x + local_1c.z * local_1c.z)
     ) {
    local_1c.y = local_1c.y + 0.1;
    lVar3 = Camera_Bounding_Sphere_Test(param_1,&local_1c,fVar5);
    if (0 < lVar3) {
      return;
    }
    iVar1 = this->_padding_;
    local_28.x = *(float *)(iVar1 + 0x38);
    local_28.y = *(float *)(iVar1 + 0x3c);
    local_28.z = *(float *)(iVar1 + 0x40);
    local_40.x = *(float *)(iVar1 + 0x20);
    local_40.y = *(float *)(iVar1 + 0x24);
    local_40.z = *(float *)(iVar1 + 0x28);
    local_34.x = local_40.x;
    local_34.y = local_40.y;
    local_34.z = local_40.z;
    pVVar4 = Vector_Rotate(&local_40,&local_28,local_8);
    local_28.x = pVVar4->x;
    local_28.y = pVVar4->y;
    local_28.z = pVVar4->z;
    pVVar4 = Vector_Rotate(&local_40,&local_34,local_8);
    p_Var2 = SortingTableCurrent;
    local_34.x = pVVar4->x;
    local_34.y = pVVar4->y;
    local_34.z = pVVar4->z;
    SortingTableCurrent->vcnt = 0;
    (p_Var2->Skin_Color).Color = local_10._0_4_;
    p_Var2->Type = 10;
    p_Var2->Bitmap_Operation = 4;
    p_Var2[1].vcnt = (long)((local_28.x - local_34.x) * fVar5 + local_1c.x);
    p_Var2[1].Skin_Color = (POLYGON_SKIN)((local_28.y - local_34.y) * fVar5 + local_1c.y);
    p_Var2[1].Bitmap_Operation = (long)((local_28.z - local_34.z) * fVar5 + local_1c.z);
    p_Var2[1].Type = (long)((local_34.x + local_28.x) * fVar5 + local_1c.x);
    p_Var2[1].Z_Value = (local_34.y + local_28.y) * fVar5 + local_1c.y;
    p_Var2[1].Next = (_ZSORTING *)((local_34.z + local_28.z) * fVar5 + local_1c.z);
    p_Var2[1].Previous = (_ZSORTING *)((local_34.x - local_28.x) * fVar5 + local_1c.x);
    p_Var2[2].vcnt = (long)((local_34.y - local_28.y) * fVar5 + local_1c.y);
    p_Var2[2].Skin_Color = (POLYGON_SKIN)((local_34.z - local_28.z) * fVar5 + local_1c.z);
    p_Var2[2].Bitmap_Operation = (long)((-local_28.x - local_34.x) * fVar5 + local_1c.x);
    p_Var2[2].Type = (long)((-local_28.y - local_34.y) * fVar5 + local_1c.y);
    p_Var2[2].Z_Value = fVar5 * (-local_28.z - local_34.z) + local_1c.z;
    fVar5 = VectGetMin((VECTOR_3D *)(p_Var2 + 1),4);
    p_Var2->Z_Value = fVar5;
  }
  else {
    lVar3 = Camera_Bounding_Sphere_Test(param_1,&local_1c,fVar5);
    p_Var2 = SortingTableCurrent;
    if (0 < lVar3) {
      return;
    }
    SortingTableCurrent->vcnt = 0;
    p_Var2->Type = 1;
    p_Var2->Bitmap_Operation = 4;
    (p_Var2->Skin_Color).Color = local_10._0_4_;
    p_Var2[1].Skin_Color = local_4c;
    p_Var2[1].Bitmap_Operation = lStack_48;
    p_Var2[1].Type = lStack_44;
    p_Var2[1].vcnt = (long)fVar5;
    p_Var2->Z_Value = local_1c.z;
    fVar5 = local_1c.z;
  }
  ZSORTAdd(fVar5);
  return;
}
