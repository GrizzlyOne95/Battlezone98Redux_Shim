/*
 * Entry: 004ed8a7
 * Name: Submit_Scrounge_Objects
 * Namespace: Global
 * Signature: void Submit_Scrounge_Objects(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Scrounge_Objects(CAMERA *param_1)

{
  _GEOMETRY *p_Var1;
  FACE *pFVar2;
  _ZSORTING *p_Var3;
  VECTOR_3D *pVVar4;
  long lVar5;
  int iVar6;
  MAT_3D *pMVar7;
  COLOR *pCVar8;
  POLYGON_SKIN PVar9;
  TEXTURE *pTVar10;
  COLOR *pCVar11;
  int iVar12;
  uint uVar13;
  _OBJ76 *p_Var14;
  MAT_3D *pMVar15;
  float *pfVar16;
  CAMERA *unaff_EDI;
  float fVar17;
  MAT_3D local_104;
  float local_c4 [16];
  MAT_3D local_84;
  VECTOR_3D local_44;
  VECTOR_3D local_38;
  undefined1 local_2c [12];
  float local_20;
  float fStack_1c;
  float local_18;
  VECTOR_3D *local_14;
  FACE *local_10;
  float *local_c;
  _OBJ76 *local_8;
  
  if ((UserProfilePtr->graphicDetail).scrounge != '\0') {
    pVVar4 = Get_Scrounge_Pos((VECTOR_3D *)local_2c,unaff_EDI);
    local_20 = pVVar4->x;
    fStack_1c = pVVar4->y;
    local_18 = pVVar4->z;
    fVar17 = Terrain_FindFloor(param_1->View_Pyramid[0].x,param_1->View_Pyramid[0].z);
    local_2c._4_8_ = (undefined8)fVar17;
    for (p_Var14 = Scrounge_Object; p_Var14 != (_OBJ76 *)0x0; p_Var14 = p_Var14->sibling) {
      local_c = Scrounge_Tiles[0] + 1;
      local_8 = p_Var14;
      do {
        Rot_Mat.posit_x =
             (p_Var14->transform).posit_x + (double)(*(float (*) [2])(local_c + -1))[0] +
             (double)local_20;
        Rot_Mat.posit_z = (p_Var14->transform).posit_z + (double)local_18 + (double)*local_c;
        lVar5 = Terrain_NodeType(Rot_Mat.posit_x,Rot_Mat.posit_z);
        iVar6 = GeoCache_SelectLOD(p_Var14,ScroungeNodeInfo[lVar5].LOD);
        if (iVar6 != 1) {
          return;
        }
        if (((p_Var14->geom != (_GEOMETRY *)0x0) && (2 < p_Var14->geom->vertex_count)) &&
           (ScroungeNodeInfo[lVar5].display != 0)) {
          fVar17 = Terrain_FindFloor(Rot_Mat.posit_x,Rot_Mat.posit_z);
          Rot_Mat.posit_y = (double)fVar17;
          if (fVar17 - (float)(double)local_2c._4_8_ <= 5.0) {
            pVVar4 = Camera_World_to_Camera
                               (&local_44,param_1,Rot_Mat.posit_x,(double)fVar17,Rot_Mat.posit_z);
            local_38.x = pVVar4->x;
            local_38.y = pVVar4->y;
            local_38.z = pVVar4->z;
            if ((local_38.z <= 120.00001) &&
               (lVar5 = Camera_Bounding_Sphere_Test(param_1,&local_38,2.0), lVar5 < 1)) {
              p_Var1 = p_Var14->geom;
              pMVar7 = Matrix_Multiply(&local_104,&Rot_Mat,&param_1->Matrix);
              pMVar15 = &local_84;
              for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
                pMVar15->right_x = pMVar7->right_x;
                pMVar7 = (MAT_3D *)&pMVar7->right_y;
                pMVar15 = (MAT_3D *)&pMVar15->right_y;
              }
              Vector_Transform(Vertex_Pool,p_Var1->vertex_table,p_Var1->vertex_count,&local_84);
              p_Var14 = local_8;
              pMVar7 = &local_8->transform;
              pMVar15 = pMVar7;
              pfVar16 = local_c4;
              for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
                *pfVar16 = pMVar15->right_x;
                pMVar15 = (MAT_3D *)&pMVar15->right_y;
                pfVar16 = pfVar16 + 1;
              }
              pMVar15 = &Rot_Mat;
              for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
                pMVar7->right_x = pMVar15->right_x;
                pMVar15 = (MAT_3D *)&pMVar15->right_y;
                pMVar7 = (MAT_3D *)&pMVar7->right_y;
              }
              Select_Light_Sources(p_Var14);
              pfVar16 = local_c4;
              pMVar7 = &local_8->transform;
              for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
                pMVar7->right_x = *pfVar16;
                pfVar16 = pfVar16 + 1;
                pMVar7 = (MAT_3D *)&pMVar7->right_y;
              }
              pVVar4 = Vertex_Pool + p_Var1->vertex_count;
              local_14 = pVVar4;
              Apply_Light_Model(&pVVar4->x,Vertex_Pool,p_Var1->normal_table,&Rot_Mat,&local_84,
                                p_Var1->normal_count);
              p_Var3 = SortingTableCurrent;
              p_Var14 = local_8;
              for (pFVar2 = p_Var1->faces; SortingTableCurrent = p_Var3, local_10 = pFVar2,
                  local_8 = p_Var14, pFVar2 != (FACE *)0x0; pFVar2 = pFVar2->front_facet) {
                p_Var3->Type = 4;
                iVar6 = pFVar2->vertex_count;
                iVar12 = 0;
                p_Var3->vcnt = iVar6;
                if (0 < iVar6) {
                  pCVar8 = (COLOR *)&p_Var3[1].Z_Value;
                  pCVar11 = &pFVar2[1].color;
                  do {
                    iVar6 = *(int *)&pCVar11[-2].index;
                    pCVar8[-1] = *pCVar11;
                    *pCVar8 = pCVar11[1];
                    pCVar8[1] = *(COLOR *)(&pVVar4->x + iVar12);
                    pVVar4 = Vertex_Pool + iVar6;
                    ((_ZSORTING *)(pCVar8 + -4))->vcnt = (long)pVVar4->x;
                    *(float *)(pCVar8 + -3) = pVVar4->y;
                    pCVar8[-2] = (COLOR)pVVar4->z;
                    iVar12 = iVar12 + 1;
                    pCVar11 = pCVar11 + 4;
                    pCVar8 = pCVar8 + 6;
                    pVVar4 = local_14;
                  } while (iVar12 < p_Var3->vcnt);
                }
                fVar17 = GetMax((POINT_3D *)(p_Var3 + 1),p_Var3->vcnt);
                p_Var3->Z_Value = fVar17;
                uVar13 = *(uint *)(sniped_by +
                                  ((uint)pFVar2->TextureType + (uint)pFVar2->ShadeType * 8) * 4 +
                                  0xf8);
                p_Var3->Bitmap_Operation = uVar13;
                uVar13 = local_8->render_type_override & uVar13;
                p_Var3->Bitmap_Operation = uVar13 & 0xff;
                PVar9.Color._1_3_ = 0;
                PVar9.Color._0_1_ = (pFVar2->color).index;
                p_Var3->Skin_Color = PVar9;
                if ((uVar13 & 4) != 0) {
                  if (pFVar2->texture_name[0] != '\0') {
                    pTVar10 = Texture_Get(local_8,pFVar2->texture_name);
                    (p_Var3->Skin_Color).Texture = pTVar10;
                    if (pTVar10 != (TEXTURE *)0x0) goto LAB_004edb7f;
                  }
                  p_Var3->Bitmap_Operation = p_Var3->Bitmap_Operation & 0xffffffeb;
                }
LAB_004edb7f:
                ZSORTAdd(p_Var3->Z_Value);
                p_Var3 = SortingTableCurrent;
                p_Var14 = local_8;
              }
            }
          }
        }
        local_c = local_c + 2;
      } while ((int)local_c < 0x62c434);
    }
  }
  return;
}
