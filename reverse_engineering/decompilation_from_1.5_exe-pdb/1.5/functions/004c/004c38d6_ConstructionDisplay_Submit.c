/*
 * Entry: 004c38d6
 * Name: ConstructionDisplay::Submit
 * Namespace: ConstructionDisplay
 * Signature: void Submit(ConstructionDisplay * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionDisplay::Submit(ConstructionDisplay *this,CAMERA *param_1)

{
  VECTOR_3D *pVVar1;
  _ZSORTING *p_Var2;
  float fVar3;
  
  p_Var2 = SortingTableCurrent;
  if ((this->index != 0) && (cameraView == 0)) {
    if ((((byte)D3IniFlags & 1) == 0) || (View_Record.Current_View == OVER_VIEW)) {
      pVVar1 = this->corner;
      Vector_Transform(pVVar1,pVVar1,5,&param_1->Matrix);
      p_Var2 = SortingTableCurrent;
      SortingTableCurrent->vcnt = 0;
      p_Var2->Type = 10;
      p_Var2->Bitmap_Operation = 4;
      p_Var2->Skin_Color = (POLYGON_SKIN)this->index;
      p_Var2[1].vcnt = (long)pVVar1->x;
      p_Var2[1].Skin_Color = (POLYGON_SKIN)this->corner[0].y;
      p_Var2[1].Bitmap_Operation = (long)this->corner[0].z;
      p_Var2[1].Type = (long)this->corner[1].x;
      p_Var2[1].Z_Value = this->corner[1].y;
      p_Var2[1].Next = (_ZSORTING *)this->corner[1].z;
      p_Var2[1].Previous = (_ZSORTING *)this->corner[2].x;
      p_Var2[2].vcnt = (long)this->corner[2].y;
      p_Var2[2].Skin_Color = (POLYGON_SKIN)this->corner[2].z;
      p_Var2[2].Bitmap_Operation = (long)this->corner[3].x;
      p_Var2[2].Type = (long)this->corner[3].y;
      p_Var2[2].Z_Value = this->corner[3].z;
      fVar3 = VectGetMin((VECTOR_3D *)(p_Var2 + 1),4);
    }
    else {
      SortingTableCurrent->Type = 1;
      p_Var2->vcnt = 0;
      p_Var2->Bitmap_Operation = 4;
      p_Var2->Skin_Color = (POLYGON_SKIN)this->index;
      p_Var2[1].Skin_Color = *(POLYGON_SKIN *)(this->corner + 4);
      p_Var2[1].Bitmap_Operation = (long)this->corner[4].y;
      p_Var2[1].Type = (long)this->corner[4].z;
      p_Var2[1].vcnt = (long)this->radius;
      fVar3 = VectGetMin(this->corner,4);
    }
    p_Var2->Z_Value = fVar3;
    ZSORTAdd(fVar3);
    this->index = 0;
  }
  return;
}
