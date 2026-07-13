/*
 * Entry: 004eb693
 * Name: Submit_All_Entities
 * Namespace: Global
 * Signature: void Submit_All_Entities(CAMERA * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */

void __cdecl Submit_All_Entities(CAMERA *param_1,tagENTITY *param_2)

{
  float fVar1;
  _ZSORTING *p_Var2;
  tagENTITY *ptVar3;
  VECTOR_3D_LONG *pVVar4;
  POLYGON_SKIN *pPVar5;
  long lVar6;
  uint uVar7;
  int iVar8;
  POLYGON_SKIN PVar9;
  MAT_3D *unaff_EBX;
  _OBJ76 *p_Var10;
  VECTOR_3D_LONG *unaff_EDI;
  CAMERA *pCVar11;
  POLYGON_SKIN local_7858 [2304];
  uint local_5458 [768];
  POLYGON_SKIN local_4858 [2304];
  tagENTITY *local_2458 [768];
  uint local_1858 [768];
  tagENTITY *local_c58 [768];
  VECTOR_3D_LONG local_58;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  POLYGON_SKIN local_28;
  POLYGON_SKIN PStack_24;
  POLYGON_SKIN PStack_20;
  POLYGON_SKIN *local_1c;
  int local_18;
  POLYGON_SKIN *local_14;
  tagENTITY *local_10;
  int local_c;
  CAMERA *local_8;
  
  local_8 = (CAMERA *)0x4eb6a0;
  Get_Visible_Lights(param_1);
  local_8 = (CAMERA *)0x0;
  local_c = 0;
  local_18 = 0;
  if (0 < world_count) {
    local_1c = local_4858;
    local_14 = local_7858;
    local_10 = world;
    do {
      ptVar3 = local_10;
      p_Var10 = local_10->obj76;
      if (p_Var10 != (_OBJ76 *)0x0) {
        if ((p_Var10->flags & 0x100) == 0) {
          if (local_10 != param_2) {
            pVVar4 = Long_Vector_Transform(&local_58,(VECTOR_3D *)unaff_EDI,unaff_EBX);
            if (((0.0001 <= (ptVar3->bSphere).radius) &&
                (ABS(pVVar4->x - (param_1->bSphere_Center).x) <= param_1->bSphere_Radius)) &&
               (ABS(pVVar4->z - (param_1->bSphere_Center).z) <= param_1->bSphere_Radius)) {
              pPVar5 = (POLYGON_SKIN *)
                       Camera_World_to_Camera(&local_40,param_1,pVVar4->x,pVVar4->y,pVVar4->z);
              fVar1 = (local_10->bSphere).radius;
              local_28 = *pPVar5;
              PStack_24 = pPVar5[1];
              PStack_20 = pPVar5[2];
              if (local_10->animFlags != '\0') {
                fVar1 = fVar1 + fVar1;
              }
              uVar7 = Camera_Bounding_Sphere_Test(param_1,(VECTOR_3D *)&local_28,fVar1);
              ptVar3 = local_10;
              if ((int)uVar7 < 1) {
                iVar8 = dynamic_object(local_10->obj76);
                pCVar11 = local_8;
                pPVar5 = local_14;
                if (iVar8 == 1) {
                  local_c58[(int)local_8] = ptVar3;
                  *pPVar5 = local_28;
                  pPVar5[1] = PStack_24;
                  pPVar5[2] = PStack_20;
                  local_1858[(int)pCVar11] = ~uVar7 & 0x100;
                  if ((int)pCVar11 < 0x2ff) {
                    local_8 = (CAMERA *)((int)&local_8->Orig_x + 1);
                    local_14 = local_14 + 3;
                  }
                }
                else {
                  local_2458[local_c] = ptVar3;
                  *local_1c = local_28;
                  local_1c[1] = PStack_24;
                  local_1c[2] = PStack_20;
                  local_5458[local_c] = ~uVar7 & 0x100;
                  if ((int)local_8 < 0x2ff) {
                    local_c = local_c + 1;
                    local_1c = local_1c + 3;
                  }
                }
              }
            }
          }
        }
        else {
          for (p_Var10 = p_Var10->child; p_Var10 != (_OBJ76 *)0x0; p_Var10 = p_Var10->sibling) {
            unaff_EDI = &local_58;
            pVVar4 = Long_Vector_Transform(unaff_EDI,(VECTOR_3D *)unaff_EDI,unaff_EBX);
            if (((0.0001 <= (p_Var10->bSphere).radius) &&
                (ABS(pVVar4->x - (param_1->bSphere_Center).x) <= param_1->bSphere_Radius)) &&
               (ABS(pVVar4->z - (param_1->bSphere_Center).z) <= param_1->bSphere_Radius)) {
              pPVar5 = (POLYGON_SKIN *)
                       Camera_World_to_Camera(&local_34,param_1,pVVar4->x,pVVar4->y,pVVar4->z);
              local_28 = *pPVar5;
              PStack_24 = pPVar5[1];
              PStack_20 = pPVar5[2];
              lVar6 = Camera_Bounding_Sphere_Test
                                (param_1,(VECTOR_3D *)&local_28,(p_Var10->bSphere).radius);
              p_Var2 = SortingTableCurrent;
              if (lVar6 < 1) {
                SortingTableCurrent->Type = (p_Var10->flags & 0x40 | 0xa0) >> 5;
                p_Var2->vcnt = 0;
                p_Var10->render_type_override = p_Var10->render_type_override & 0xffffffee;
                p_Var2[2].Bitmap_Operation = 0;
                p_Var2[1].vcnt = (long)p_Var10;
                p_Var2[2].vcnt = 0;
                p_Var2[1].Skin_Color = local_28;
                p_Var2[1].Bitmap_Operation = (long)PStack_24;
                p_Var2[1].Type = (long)PStack_20;
                p_Var2[1].Next = (_ZSORTING *)0x0;
                p_Var2[1].Previous =
                     (_ZSORTING *)(0x25 - (uint)(1 < (UserProfilePtr->graphicDetail).objDetail));
                PVar9.Color._1_3_ = 0;
                PVar9.Color._0_1_ = p_Var10->child == (_OBJ76 *)0x0;
                p_Var2[2].Skin_Color = PVar9;
                fVar1 = (p_Var10->bSphere).radius;
                p_Var2[1].Z_Value = fVar1;
                fVar1 = (float)p_Var2[1].Type - fVar1;
                p_Var2->Z_Value = fVar1;
                ZSORTAdd(fVar1);
              }
            }
          }
        }
      }
      local_18 = local_18 + 1;
      local_10 = local_10 + 1;
    } while (local_18 < world_count);
  }
  pCVar11 = local_8;
  ComputeRenderQuality
            (param_1,(long)local_8,local_c,(long *)local_1858,(long *)local_5458,local_c58,
             local_2458,(VECTOR_3D *)local_7858,(VECTOR_3D *)local_4858);
  MergeAndAdd(local_8,(long)local_1858,(long)local_5458,(long *)local_c58,(long *)local_2458,
              (tagENTITY **)&local_7858[0].Texture,(tagENTITY **)&local_4858[0].Texture,
              (VECTOR_3D *)param_1,(VECTOR_3D *)pCVar11);
  return;
}
