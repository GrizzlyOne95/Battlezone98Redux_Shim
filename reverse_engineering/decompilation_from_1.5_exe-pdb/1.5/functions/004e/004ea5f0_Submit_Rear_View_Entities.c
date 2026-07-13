/*
 * Entry: 004ea5f0
 * Name: Submit_Rear_View_Entities
 * Namespace: Global
 * Signature: void Submit_Rear_View_Entities(CAMERA * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Rear_View_Entities(CAMERA *param_1,tagENTITY *param_2)

{
  float fVar1;
  _OBJ76 *p_Var2;
  _ZSORTING *p_Var3;
  VECTOR_3D_LONG *pVVar4;
  POLYGON_SKIN *pPVar5;
  long lVar6;
  uint uVar7;
  POLYGON_SKIN PVar8;
  tagENTITY *ptVar9;
  MAT_3D *unaff_ESI;
  VECTOR_3D_LONG *unaff_EDI;
  VECTOR_3D_LONG local_48;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  POLYGON_SKIN local_18;
  POLYGON_SKIN PStack_14;
  POLYGON_SKIN PStack_10;
  int local_c;
  _OBJ76 *local_8;
  
  Get_Visible_Lights(param_1);
  local_c = 0;
  if (0 < world_count) {
    ptVar9 = world;
    do {
      p_Var2 = ptVar9->obj76;
      ptVar9->mergeNext = (tagENTITY *)0x0;
      ptVar9->mergePoly = (void *)0x0;
      if (p_Var2 != (_OBJ76 *)0x0) {
        if ((p_Var2->flags & 0x100) == 0) {
          if (ptVar9 != param_2) {
            pVVar4 = Long_Vector_Transform(&local_48,(VECTOR_3D *)unaff_EDI,unaff_ESI);
            pPVar5 = (POLYGON_SKIN *)
                     Camera_World_to_Camera(&local_30,param_1,pVVar4->x,pVVar4->y,pVVar4->z);
            fVar1 = (ptVar9->bSphere).radius;
            local_18 = *pPVar5;
            PStack_14 = pPVar5[1];
            PStack_10 = pPVar5[2];
            if (ptVar9->animFlags != '\0') {
              fVar1 = fVar1 + fVar1;
            }
            uVar7 = Camera_Bounding_Sphere_Test(param_1,(VECTOR_3D *)&local_18,fVar1);
            p_Var3 = SortingTableCurrent;
            if ((int)uVar7 < 1) {
              p_Var2 = ptVar9->obj76;
              SortingTableCurrent->vcnt = 0;
              p_Var3->Type = 6;
              p_Var3[2].Skin_Color.Color = 0;
              p_Var3[2].vcnt = ~uVar7 & 0x100;
              p_Var3[1].Next = (_ZSORTING *)0x0;
              p_Var3[2].Bitmap_Operation = (long)ptVar9;
              p_Var3[1].vcnt = (long)p_Var2;
              p_Var3[1].Previous = (_ZSORTING *)(0x21 - (uint)(useD3D != 0));
              p_Var3[1].Skin_Color = local_18;
              p_Var3[1].Bitmap_Operation = (long)PStack_14;
              p_Var3[1].Type = (long)PStack_10;
              fVar1 = (ptVar9->bSphere).radius;
              p_Var3[1].Z_Value = fVar1;
              fVar1 = (float)p_Var3[1].Type - fVar1;
              p_Var3->Z_Value = fVar1;
              ZSORTAdd(fVar1);
            }
          }
        }
        else {
          local_8 = p_Var2->child;
          if (local_8 != (_OBJ76 *)0x0) {
            do {
              unaff_EDI = &local_48;
              pVVar4 = Long_Vector_Transform(unaff_EDI,(VECTOR_3D *)unaff_EDI,unaff_ESI);
              pPVar5 = (POLYGON_SKIN *)
                       Camera_World_to_Camera(&local_24,param_1,pVVar4->x,pVVar4->y,pVVar4->z);
              local_18 = *pPVar5;
              PStack_14 = pPVar5[1];
              PStack_10 = pPVar5[2];
              lVar6 = Camera_Bounding_Sphere_Test(param_1,(VECTOR_3D *)&local_18,10.0);
              p_Var3 = SortingTableCurrent;
              if (lVar6 < 1) {
                SortingTableCurrent->Type = (local_8->flags & 0x40 | 0xa0) >> 5;
                p_Var3->vcnt = 0;
                local_8->render_type_override = local_8->render_type_override & 0xffffffee;
                p_Var3[2].Bitmap_Operation = 0;
                p_Var3[2].vcnt = 0;
                p_Var3[1].Next = (_ZSORTING *)0x0;
                p_Var3[1].vcnt = (long)local_8;
                p_Var3[1].Previous = (_ZSORTING *)0x21;
                PVar8.Color._1_3_ = 0;
                PVar8.Color._0_1_ = local_8->child == (_OBJ76 *)0x0;
                p_Var3[2].Skin_Color = PVar8;
                p_Var3[1].Skin_Color = local_18;
                p_Var3[1].Bitmap_Operation = (long)PStack_14;
                p_Var3[1].Type = (long)PStack_10;
                fVar1 = (local_8->bSphere).radius;
                p_Var3[1].Z_Value = fVar1;
                fVar1 = (float)p_Var3[1].Type - fVar1;
                p_Var3->Z_Value = fVar1;
                ZSORTAdd(fVar1);
              }
              local_8 = local_8->sibling;
            } while (local_8 != (_OBJ76 *)0x0);
            local_8 = (_OBJ76 *)0x0;
          }
        }
      }
      local_c = local_c + 1;
      ptVar9 = ptVar9 + 1;
    } while (local_c < world_count);
  }
  return;
}
