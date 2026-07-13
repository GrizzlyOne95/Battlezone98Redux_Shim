/*
 * Entry: 005300c6
 * Name: GroundBlast::Submit
 * Namespace: GroundBlast
 * Signature: void Submit(GroundBlast * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GroundBlast::Submit(GroundBlast *this,CAMERA *param_1)

{
  _ZSORTING *p_Var1;
  int iVar2;
  float fVar3;
  float fVar4;
  _ZSORTING *p_Var5;
  long lVar6;
  int unaff_EDI;
  VECTOR_3D local_18;
  double local_c;
  
  iVar2 = *(int *)&this->field_0x10;
  local_18.x = *(float *)(iVar2 + 200);
  local_18.y = *(float *)(iVar2 + 0xcc);
  local_18.z = *(float *)(iVar2 + 0xd0);
  Vector_Transform(&local_18,&local_18,1,(MAT_3D *)(iVar2 + 0x20));
  Vector_Transform(&local_18,&local_18,1,&param_1->Matrix);
  p_Var1 = *(_ZSORTING **)(*(int *)&this->field_0x10 + 0xd4);
  lVar6 = Camera_Bounding_Sphere_Test(param_1,&local_18,(float)p_Var1);
  if (lVar6 < 1) {
    Set_Rounding(unaff_EDI);
    local_c = (double)(*(float *)&this->field_0x18 + (float)Float2Int);
    Set_Rounding(unaff_EDI);
    p_Var5 = SortingTableCurrent;
    SortingTableCurrent->vcnt = 0;
    p_Var5->Type = 9;
    (p_Var5->Skin_Color).Color = local_c._0_4_;
    p_Var5->Bitmap_Operation = 0x90004;
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
