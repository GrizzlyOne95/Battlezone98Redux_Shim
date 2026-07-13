/*
 * Entry: 0052f8ef
 * Name: FlamePuff::Submit
 * Namespace: FlamePuff
 * Signature: void Submit(FlamePuff * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FlamePuff::Submit(FlamePuff *this,CAMERA *param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  _ZSORTING *p_Var4;
  long lVar5;
  VECTOR_3D local_10;
  
  iVar1 = this->_padding_;
  local_10.x = (float)*(double *)(iVar1 + 0x48);
  local_10.y = (float)*(double *)(iVar1 + 0x50);
  local_10.z = (float)*(double *)(iVar1 + 0x58);
  Vector_Transform(&local_10,&local_10,1,&param_1->Matrix);
  lVar5 = Camera_Bounding_Sphere_Test(param_1,&local_10,*(float *)(this->_padding_ + 0xd4));
  p_Var4 = SortingTableCurrent;
  if (lVar5 < 1) {
    SortingTableCurrent->vcnt = 0;
    p_Var4->Type = 9;
    p_Var4->Skin_Color = (POLYGON_SKIN)this->flameIndex;
    p_Var4->Bitmap_Operation = 0x50004;
    fVar2 = 1.0 / local_10.z;
    p_Var4[1].vcnt = (long)(param_1->Const_x * local_10.x * fVar2 + param_1->Orig_x);
    p_Var4[1].Skin_Color = (POLYGON_SKIN)(param_1->Const_y * local_10.y * fVar2 + param_1->Orig_y);
    p_Var4[1].Bitmap_Operation = (long)local_10.z;
    fVar3 = *(float *)(this->_padding_ + 0xd4) * param_1->Const_x * fVar2;
    p_Var4[1].Type = (long)(fVar3 + fVar3);
    p_Var4[1].Z_Value = *(float *)(this->_padding_ + 0xd4) * param_1->Const_y * fVar2 * -2.0;
    p_Var4[1].Previous = (_ZSORTING *)local_10.x;
    p_Var4[2].vcnt = (long)local_10.y;
    p_Var4[2].Skin_Color = (POLYGON_SKIN)local_10.z;
    p_Var4[1].Next = *(_ZSORTING **)(this->_padding_ + 0xd4);
    p_Var4->Z_Value = local_10.z;
    ZSORTAdd(local_10.z);
  }
  return;
}
