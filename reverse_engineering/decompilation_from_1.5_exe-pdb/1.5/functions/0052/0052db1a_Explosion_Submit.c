/*
 * Entry: 0052db1a
 * Name: Explosion::Submit
 * Namespace: Explosion
 * Signature: void Submit(Explosion * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Explosion::Submit(Explosion *this,CAMERA *param_1)

{
  _ZSORTING *p_Var1;
  _OBJ76 *p_Var2;
  float fVar3;
  float fVar4;
  _ZSORTING *p_Var5;
  long lVar6;
  int unaff_EDI;
  VECTOR_3D local_18;
  double local_c;
  
  p_Var2 = this->obj;
  local_18.x = (p_Var2->bSphere).origin.x;
  local_18.y = (p_Var2->bSphere).origin.y;
  local_18.z = (p_Var2->bSphere).origin.z;
  Vector_Transform(&local_18,&local_18,1,&p_Var2->transform);
  Vector_Transform(&local_18,&local_18,1,&param_1->Matrix);
  p_Var1 = (_ZSORTING *)(this->obj->bSphere).radius;
  lVar6 = Camera_Bounding_Sphere_Test(param_1,&local_18,(float)p_Var1);
  if (lVar6 < 1) {
    Set_Rounding(unaff_EDI);
    local_c = (double)(this->frameIndex + (float)Float2Int);
    Set_Rounding(unaff_EDI);
    p_Var5 = SortingTableCurrent;
    SortingTableCurrent->vcnt = 0;
    p_Var5->Type = 9;
    (p_Var5->Skin_Color).Color = local_c._0_4_;
    p_Var5->Bitmap_Operation = 0x50004;
    fVar3 = 1.0 / local_18.z;
    p_Var5[1].vcnt = (long)(param_1->Const_x * local_18.x * fVar3 + param_1->Orig_x);
    p_Var5[1].Skin_Color = (POLYGON_SKIN)(param_1->Const_y * local_18.y * fVar3 + param_1->Orig_y);
    p_Var5[1].Bitmap_Operation = (long)local_18.z;
    fVar4 = param_1->Const_x * fVar3 * (float)p_Var1;
    p_Var5[1].Type = (long)(fVar4 + fVar4);
    p_Var5[1].Z_Value = param_1->Const_y * fVar3 * (float)p_Var1 * -2.0;
    p_Var5[1].Previous = (_ZSORTING *)local_18.x;
    p_Var5[2].vcnt = (long)local_18.y;
    p_Var5[2].Skin_Color = (POLYGON_SKIN)local_18.z;
    p_Var5[1].Next = p_Var1;
    p_Var5->Z_Value = local_18.z - (float)p_Var1;
    ZSORTAdd(local_18.z - (float)p_Var1);
  }
  return;
}
