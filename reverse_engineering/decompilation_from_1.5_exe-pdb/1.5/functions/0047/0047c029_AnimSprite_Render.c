/*
 * Entry: 0047c029
 * Name: AnimSprite::Render
 * Namespace: AnimSprite
 * Signature: void Render(AnimSprite * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnimSprite::Render(AnimSprite *this,CAMERA *param_1)

{
  _OBJ76 *p_Var1;
  _ZSORTING *p_Var2;
  _ZSORTING *p_Var3;
  MAT_3D *pMVar4;
  long lVar5;
  VECTOR_3D *pVVar6;
  int iVar7;
  POLYGON_SKIN *pPVar8;
  MAT_3D *pMVar9;
  float10 fVar10;
  MAT_3D local_a8;
  VECTOR_3D local_68;
  undefined1 local_5c [20];
  _ZSORTING *p_Stack_48;
  _ZSORTING *p_Stack_44;
  _ZSORTING *local_40;
  _ZSORTING *p_Stack_3c;
  long lStack_38;
  _ZSORTING *local_34;
  long lStack_30;
  POLYGON_SKIN PStack_2c;
  long local_28;
  POLYGON_SKIN PStack_24;
  long lStack_20;
  VECTOR_3D local_1c;
  float local_10;
  undefined8 local_c;
  
  if (((this->obj->flags & 0x10) == 0) || (View_Record.Intenal_View == 0)) {
    Rot_Mat.posit_x = (this->obj->transform).posit_x;
    Rot_Mat.posit_y = (this->obj->transform).posit_y;
    Rot_Mat.posit_z = (this->obj->transform).posit_z;
    local_c = (double)CONCAT44(&param_1->Matrix,(uint)local_c);
    pMVar4 = Matrix_Multiply((MAT_3D *)local_5c,&Rot_Mat,&param_1->Matrix);
    pMVar9 = &local_a8;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar9->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    p_Var1 = this->obj;
    local_1c.x = (p_Var1->bSphere).origin.x;
    local_1c.y = (p_Var1->bSphere).origin.y;
    local_1c.z = (p_Var1->bSphere).origin.z;
    Vector_Transform(&local_1c,&local_1c,1,&local_a8);
    lVar5 = Camera_Bounding_Sphere_Test(param_1,&local_1c,(this->obj->bSphere).radius);
    if (lVar5 < 1) {
      Vector_Transform((VECTOR_3D *)(local_5c + 0x10),this->geometry,4,&local_a8);
      pVVar6 = Vector_Rotate(&local_68,(VECTOR_3D *)&(this->obj->transform).front_x,local_c._4_4_);
      p_Var3 = SortingTableCurrent;
      local_10 = pVVar6->x;
      fVar10 = (float10)fpatan((float10)local_10,(float10)pVVar6->z);
      p_Var2 = SortingTableCurrent + 3;
      local_c = (double)(((float10)3.1415927 - fVar10) * (float10)1.2732395 + (float10)Float2Int);
      pPVar8 = (POLYGON_SKIN *)(*this->frame + ((uint)local_c & 7));
      SortingTableCurrent->Type = 4;
      p_Var3->vcnt = 4;
      p_Var3->Bitmap_Operation = 0x44;
      p_Var3->Skin_Color = *pPVar8;
      p_Var2->Z_Value = (float)local_5c._16_4_;
      p_Var3[3].Next = p_Stack_48;
      p_Var3[3].Previous = p_Stack_44;
      *(POLYGON_SKIN *)(p_Var3 + 4) = pPVar8[1];
      p_Var3[4].Skin_Color = pPVar8[2];
      p_Var3[4].Bitmap_Operation = (long)TerrainIntensity;
      p_Var3[2].Next = local_40;
      p_Var3[2].Previous = p_Stack_3c;
      p_Var3[3].vcnt = lStack_38;
      p_Var3[3].Skin_Color = pPVar8[3];
      p_Var3[3].Bitmap_Operation = (long)pPVar8[2];
      p_Var3[3].Type = (long)TerrainIntensity;
      p_Var3[1].Previous = local_34;
      p_Var3[2].vcnt = lStack_30;
      p_Var3[2].Skin_Color = PStack_2c;
      p_Var3[2].Bitmap_Operation = (long)pPVar8[3];
      p_Var3[2].Type = (long)pPVar8[4];
      p_Var3[2].Z_Value = TerrainIntensity;
      p_Var3[1].vcnt = local_28;
      p_Var3[1].Skin_Color = PStack_24;
      p_Var3[1].Bitmap_Operation = lStack_20;
      p_Var3[1].Type = (long)pPVar8[1];
      p_Var3[1].Z_Value = (float)pPVar8[4];
      p_Var3[1].Next = (_ZSORTING *)TerrainIntensity;
      p_Var3->Z_Value = (float)local_a8.posit_z;
      ZSORTAdd((float)local_a8.posit_z);
    }
  }
  return;
}
