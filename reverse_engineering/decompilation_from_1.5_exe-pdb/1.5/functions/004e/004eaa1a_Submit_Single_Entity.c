/*
 * Entry: 004eaa1a
 * Name: Submit_Single_Entity
 * Namespace: Global
 * Signature: void Submit_Single_Entity(CAMERA * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Single_Entity(CAMERA *param_1,tagENTITY *param_2)

{
  float fVar1;
  _OBJ76 *p_Var2;
  _ZSORTING *p_Var3;
  VECTOR_3D_LONG *pVVar4;
  POLYGON_SKIN *pPVar5;
  long lVar6;
  POLYGON_SKIN PVar7;
  MAT_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  VECTOR_3D_LONG local_34;
  VECTOR_3D local_1c;
  POLYGON_SKIN local_10;
  POLYGON_SKIN PStack_c;
  POLYGON_SKIN PStack_8;
  
  param_2->mergeNext = (tagENTITY *)0x0;
  param_2->mergePoly = (void *)0x0;
  param_2->mergeCount = 0;
  Get_Visible_Lights(param_1);
  p_Var2 = param_2->obj76;
  if (p_Var2 != (_OBJ76 *)0x0) {
    if ((p_Var2->flags & 0x100) == 0) {
      pVVar4 = Long_Vector_Transform(&local_34,unaff_EDI,unaff_ESI);
      pPVar5 = (POLYGON_SKIN *)
               Camera_World_to_Camera(&local_1c,param_1,pVVar4->x,pVVar4->y,pVVar4->z);
      local_10 = *pPVar5;
      PStack_c = pPVar5[1];
      PStack_8 = pPVar5[2];
      lVar6 = Camera_Bounding_Sphere_Test(param_1,(VECTOR_3D *)&local_10,(param_2->bSphere).radius);
      p_Var3 = SortingTableCurrent;
      if (lVar6 < 1) {
        SortingTableCurrent->Type = 6;
        p_Var3->vcnt = 0;
        p_Var3[2].Bitmap_Operation = (long)param_2;
        p_Var3[1].vcnt = (long)param_2->obj76;
        p_Var3[2].Skin_Color.Color = 0;
        p_Var3[2].vcnt = 0;
        p_Var3[1].Next = (_ZSORTING *)0x0;
        p_Var3[1].Previous = (_ZSORTING *)0x25;
        p_Var3[1].Skin_Color = local_10;
        p_Var3[1].Bitmap_Operation = (long)PStack_c;
        p_Var3[1].Type = (long)PStack_8;
        p_Var3[1].Z_Value = (param_2->bSphere).radius;
        fVar1 = (float)p_Var3[1].Type - (param_2->bSphere).radius;
        p_Var3->Z_Value = fVar1;
        ZSORTAdd(fVar1);
      }
    }
    else {
      for (p_Var2 = p_Var2->child; p_Var2 != (_OBJ76 *)0x0; p_Var2 = p_Var2->sibling) {
        pVVar4 = Long_Vector_Transform(&local_34,(VECTOR_3D *)&local_34,unaff_ESI);
        pPVar5 = (POLYGON_SKIN *)
                 Camera_World_to_Camera(&local_1c,param_1,pVVar4->x,pVVar4->y,pVVar4->z);
        local_10 = *pPVar5;
        PStack_c = pPVar5[1];
        PStack_8 = pPVar5[2];
        lVar6 = Camera_Bounding_Sphere_Test(param_1,(VECTOR_3D *)&local_10,10.0);
        p_Var3 = SortingTableCurrent;
        if (lVar6 < 1) {
          SortingTableCurrent->Type = (p_Var2->flags & 0x40 | 0xa0) >> 5;
          p_Var3->vcnt = 0;
          p_Var2->render_type_override = p_Var2->render_type_override & 0xffffffee;
          p_Var3[2].Bitmap_Operation = 0;
          p_Var3[1].vcnt = (long)p_Var2;
          p_Var3[2].vcnt = 0;
          p_Var3[1].Skin_Color = local_10;
          p_Var3[1].Bitmap_Operation = (long)PStack_c;
          p_Var3[1].Type = (long)PStack_8;
          p_Var3[1].Next = (_ZSORTING *)0x0;
          p_Var3[1].Previous = (_ZSORTING *)0x25;
          PVar7.Color._1_3_ = 0;
          PVar7.Color._0_1_ = p_Var2->child == (_OBJ76 *)0x0;
          p_Var3[2].Skin_Color = PVar7;
          fVar1 = (p_Var2->bSphere).radius;
          p_Var3[1].Z_Value = fVar1;
          fVar1 = (float)p_Var3[1].Type - fVar1;
          p_Var3->Z_Value = fVar1;
          ZSORTAdd(fVar1);
        }
      }
    }
  }
  return;
}
