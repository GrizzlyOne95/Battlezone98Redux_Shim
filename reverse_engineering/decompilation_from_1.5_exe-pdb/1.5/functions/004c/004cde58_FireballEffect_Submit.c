/*
 * Entry: 004cde58
 * Name: FireballEffect::Submit
 * Namespace: FireballEffect
 * Signature: void Submit(FireballEffect * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FireballEffect::Submit(FireballEffect *this,CAMERA *param_1)

{
  VECTOR_3D *pVVar1;
  float fVar2;
  float fVar3;
  _ZSORTING *p_Var4;
  uint uVar5;
  long lVar6;
  int unaff_EDI;
  VECTOR_3D local_24;
  double local_18;
  int local_10;
  FireballEffect *local_c;
  uint local_8;
  
  local_c = this;
  local_10 = Set_Rounding(unaff_EDI);
  uVar5 = this->indexFirst;
  if (this->indexFirst != this->indexLast) {
    do {
      local_8 = uVar5 + 1;
      pVVar1 = &this->fireballList[uVar5].pos;
      if (0x1f < local_8) {
        local_8 = 0;
      }
      Vector_Transform(&local_24,pVVar1,1,&param_1->Matrix);
      lVar6 = Camera_Bounding_Sphere_Test(param_1,&local_24,pVVar1[2].z);
      p_Var4 = SortingTableCurrent;
      if (lVar6 < 1) {
        fVar2 = pVVar1[2].x;
        fVar3 = (float)Float2Int;
        SortingTableCurrent->vcnt = 0;
        p_Var4->Type = 9;
        p_Var4->Bitmap_Operation = 0x50004;
        local_18 = (double)(fVar2 + fVar3);
        (p_Var4->Skin_Color).Color = local_18._0_4_;
        fVar2 = 1.0 / local_24.z;
        p_Var4[1].vcnt = (long)(param_1->Const_x * local_24.x * fVar2 + param_1->Orig_x);
        p_Var4[1].Skin_Color =
             (POLYGON_SKIN)(local_24.y * fVar2 * param_1->Const_y + param_1->Orig_y);
        p_Var4[1].Bitmap_Operation = (long)local_24.z;
        fVar3 = param_1->Const_x * pVVar1[2].z * fVar2;
        p_Var4[1].Type = (long)(fVar3 + fVar3);
        p_Var4[1].Z_Value = fVar2 * pVVar1[2].z * param_1->Const_y * -2.0;
        p_Var4[1].Previous = (_ZSORTING *)local_24.x;
        p_Var4[2].vcnt = (long)local_24.y;
        p_Var4[2].Skin_Color = (POLYGON_SKIN)local_24.z;
        p_Var4[1].Next = (_ZSORTING *)pVVar1[2].z;
        fVar2 = local_24.z - pVVar1[2].z;
        p_Var4->Z_Value = fVar2;
        ZSORTAdd(fVar2);
        this = local_c;
      }
      uVar5 = local_8;
    } while (local_8 != this->indexLast);
  }
  Set_Rounding(unaff_EDI);
  return;
}
