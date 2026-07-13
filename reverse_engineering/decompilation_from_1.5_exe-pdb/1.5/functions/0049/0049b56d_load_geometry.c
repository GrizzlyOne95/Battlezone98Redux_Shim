/*
 * Entry: 0049b56d
 * Name: load_geometry
 * Namespace: Global
 * Signature: _GEOMETRY * load_geometry(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_GEOMETRY * __cdecl load_geometry(char *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  _GEOMETRY *p_Var5;
  int iVar6;
  long lVar7;
  float *pfVar8;
  VECTOR_3D *pVVar9;
  FACE *pFVar10;
  char *pcVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  FACE *pFVar15;
  float *pfVar16;
  VECTOR_3D local_c4;
  VECTOR_3D local_b8;
  VECTOR_3D local_ac;
  float local_a0;
  float fStack_9c;
  float fStack_98;
  VECTOR_3D local_94;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  int local_40;
  float local_3c;
  float local_38;
  float local_34;
  VECTOR_3D local_30;
  int local_24;
  FACE *local_20;
  FACE *local_1c;
  int local_18;
  char *local_14;
  float *local_10;
  FACE *local_c;
  char local_5;
  
  iVar13 = 0;
  local_24 = 0;
  if (*(int *)param_1 == 0x2e47454f) {
    local_1c = (FACE *)(param_1 + *(int *)(param_1 + 0x18) * 0xc + 0x24);
    local_c = (FACE *)((int)local_1c + *(int *)(param_1 + 0x18) * 0xc);
    iVar6 = *(int *)(param_1 + 0x1c);
    pcVar11 = (char *)local_c;
    iVar12 = iVar6;
    if (0 < iVar6) {
      do {
        iVar13 = iVar13 + *(int *)(pcVar11 + 4);
        iVar12 = iVar12 + -1;
        pcVar11 = pcVar11 + *(int *)(pcVar11 + 4) * 0x10 + 0x37;
      } while (iVar12 != 0);
    }
    uVar14 = (iVar13 + iVar6 * 4) * 0x10 + (*(int *)(param_1 + 0x18) + 1) * 0x18;
    p_Var5 = operator_new__(uVar14);
    iVar13 = 0;
    memset(p_Var5,0,uVar14);
    if (p_Var5 == (_GEOMETRY *)0x0) {
      p_Var5 = (_GEOMETRY *)0x0;
    }
    else {
      p_Var5->cache_info = (_CACHE_INFO *)0x0;
      p_Var5->vertex_count = *(long *)(param_1 + 0x18);
      p_Var5->normal_count = *(long *)(param_1 + 0x18);
      p_Var5->vertex_table = (VECTOR_3D *)(p_Var5 + 1);
      p_Var5->normal_table = (VECTOR_3D *)(&p_Var5[1].cache_info + p_Var5->vertex_count * 3);
      p_Var5->faces =
           (FACE *)((VECTOR_3D *)(&p_Var5[1].cache_info + p_Var5->vertex_count * 3) +
                   p_Var5->vertex_count);
      local_5 = '\0';
      local_18 = 0;
      if (0 < *(int *)(param_1 + 0x18)) {
        local_10 = (float *)(param_1 + 0x2c);
        do {
          *(float *)((int)&p_Var5->vertex_table->x + iVar13) = local_10[-2] + xshift;
          *(float *)((int)&p_Var5->vertex_table->y + iVar13) = local_10[-1] + yshift;
          *(float *)((int)&p_Var5->vertex_table->z + iVar13) = *local_10 + zshift;
          iVar6 = _isnan((double)*(float *)((int)&p_Var5->vertex_table->x + iVar13));
          if (((iVar6 != 0) ||
              (iVar6 = _isnan((double)*(float *)((int)&p_Var5->vertex_table->y + iVar13)),
              iVar6 != 0)) ||
             (iVar6 = _isnan((double)*(float *)((int)&p_Var5->vertex_table->z + iVar13)), iVar6 != 0
             )) {
            *(undefined4 *)((int)&p_Var5->vertex_table->z + iVar13) = 0;
            *(undefined4 *)((int)&p_Var5->vertex_table->y + iVar13) = 0;
            *(undefined4 *)((int)&p_Var5->vertex_table->x + iVar13) = 0;
            if (local_5 == '\0') {
              TraceWarning("repaired geom \"%.16s\" vertices:");
              local_5 = '\x01';
            }
            TraceWarning(" %d");
          }
          local_18 = local_18 + 1;
          local_10 = local_10 + 3;
          iVar13 = iVar13 + 0xc;
        } while (local_18 < *(int *)(param_1 + 0x18));
        if (local_5 != '\0') {
          TraceWarning("\n");
        }
      }
      iVar13 = 0;
      local_18 = 0;
      if (0 < *(int *)(param_1 + 0x18)) {
        local_10 = (float *)((int)local_1c + 8);
        do {
          *(float *)((int)&p_Var5->normal_table->x + iVar13) = local_10[-2] + xshift;
          *(float *)((int)&p_Var5->normal_table->y + iVar13) = local_10[-1] + yshift;
          *(float *)((int)&p_Var5->normal_table->z + iVar13) = *local_10 + zshift;
          iVar6 = _isnan((double)*(float *)((int)&p_Var5->normal_table->x + iVar13));
          if (((iVar6 != 0) ||
              (iVar6 = _isnan((double)*(float *)((int)&p_Var5->normal_table->y + iVar13)),
              iVar6 != 0)) ||
             (iVar6 = _isnan((double)*(float *)((int)&p_Var5->normal_table->z + iVar13)), iVar6 != 0
             )) {
            *(undefined4 *)((int)&p_Var5->normal_table->z + iVar13) = 0;
            local_24 = 1;
            *(undefined4 *)((int)&p_Var5->normal_table->y + iVar13) = 0;
            *(undefined4 *)((int)&p_Var5->normal_table->x + iVar13) = 0;
          }
          local_18 = local_18 + 1;
          local_10 = local_10 + 3;
          iVar13 = iVar13 + 0xc;
        } while (local_18 < *(int *)(param_1 + 0x18));
      }
      pFVar15 = p_Var5->faces;
      local_10 = (float *)local_c;
      local_c = (FACE *)0x0;
      local_5 = '\0';
      local_18 = 0;
      if (0 < *(int *)(param_1 + 0x1c)) {
        do {
          pFVar15->vertex_count = *(long *)((int)local_10 + 4);
          (pFVar15->color).red = *(uchar *)((int)local_10 + 8);
          (pFVar15->color).green = *(uchar *)((int)local_10 + 9);
          (pFVar15->color).blue = *(uchar *)((int)local_10 + 10);
          local_1c = (FACE *)(uint)*(byte *)((int)local_10 + 8);
          local_20 = pFVar15;
          lVar7 = Get_Closest_RGB_Entry
                            ((float)(int)local_1c * 0.003921569,
                             (float)*(byte *)((int)local_10 + 9) * 0.003921569,
                             (float)*(byte *)((int)local_10 + 10) * 0.003921569);
          pfVar16 = local_10;
          (pFVar15->color).index = (uchar)lVar7;
          pFVar15->ShadeType = *(uchar *)((int)local_10 + 0x1f);
          pFVar15->TextureType = *(uchar *)((int)local_10 + 0x20);
          pFVar15->XluscentType = *(uchar *)((int)local_10 + 0x21);
          strncpy(pFVar15->texture_name,(char *)((int)local_10 + 0x22),0xf);
          _strlwr(pFVar15->texture_name);
          if (pFVar15->texture_name[0] != '\0') {
            local_14 = strchr(pFVar15->texture_name,0x2e);
            if (local_14 == (char *)0x0) {
              pcVar11 = pFVar15->texture_name;
              do {
                local_14 = pcVar11;
                pcVar11 = local_14 + 1;
              } while (*local_14 != '\0');
            }
            builtin_strncpy(local_14,".tmt",5);
            iVar13 = ItemExists(local_20->texture_name);
            pFVar15 = local_20;
            pfVar16 = local_10;
            if (iVar13 == 0) {
              builtin_strncpy(local_14,".map",5);
              iVar13 = ItemExists(local_20->texture_name);
              pFVar15 = local_20;
              pfVar16 = local_10;
              if (iVar13 == 0) {
                TraceError("geom \"%.16s\" face %d missing texture \"%.16s\"\n");
                pFVar15 = local_20;
                pfVar16 = local_10;
              }
            }
          }
          if (local_c != (FACE *)0x0) {
            local_c->front_facet = pFVar15;
          }
          fVar1 = 0.0;
          local_c = (FACE *)pFVar15->vertex_count;
          pFVar15->front_facet = (FACE *)0x0;
          local_14 = (char *)0x0;
          local_1c = pFVar15 + 1;
          fVar4 = 1.0 / (float)(int)local_c;
          fVar2 = fVar1;
          fVar3 = fVar1;
          if (0 < (int)local_c) {
            local_c = (FACE *)((int)pfVar16 + (0x37 - (int)local_1c));
            pfVar16 = (float *)((int)pfVar16 + 0x43);
            pfVar8 = (float *)&pFVar15[1].vertex_count;
            do {
              ((FACE *)(pfVar8 + -1))->index = (long)pfVar16[-3];
              *pfVar8 = (float)*(long *)((int)local_c + (int)pfVar8);
              iVar13 = ((FACE *)(pfVar8 + -1))->index;
              *(COLOR *)(pfVar8 + 1) = *(COLOR *)(pfVar16 + -1);
              (((PLANE *)(pfVar8 + 2))->surf_normal).x = *pfVar16;
              pVVar9 = p_Var5->vertex_table + iVar13;
              local_14 = (char *)((int)local_14 + 1);
              pfVar16 = pfVar16 + 4;
              pfVar8 = pfVar8 + 4;
              fVar1 = pVVar9->x + fVar1;
              fVar3 = pVVar9->y + fVar3;
              fVar2 = pVVar9->z + fVar2;
            } while ((int)local_14 < pFVar15->vertex_count);
          }
          (pFVar15->Test_Point).x = fVar4 * fVar1;
          (pFVar15->Test_Point).y = fVar4 * fVar3;
          (pFVar15->Test_Point).z = fVar2 * fVar4;
          local_30.x = 0.0;
          local_30.y = 0.0;
          local_30.z = 0.0;
          pVVar9 = p_Var5->vertex_table + local_1c->index;
          local_3c = pVVar9->x;
          local_38 = pVVar9->y;
          local_34 = pVVar9->z;
          if (2 < local_20->vertex_count) {
            local_c = (FACE *)pFVar15[1].texture_name;
            local_14 = (char *)(local_20->vertex_count + -2);
            do {
              pVVar9 = p_Var5->vertex_table + *(int *)((int)local_c + -0x10);
              local_70 = pVVar9->x;
              local_6c = pVVar9->y;
              local_68 = pVVar9->z;
              local_ac.x = local_70 - local_3c;
              local_ac.y = local_6c - local_38;
              local_ac.z = local_68 - local_34;
              pVVar9 = p_Var5->vertex_table + local_c->index;
              local_7c = pVVar9->x;
              local_78 = pVVar9->y;
              local_74 = pVVar9->z;
              local_94.x = local_7c - local_3c;
              local_94.y = local_78 - local_38;
              local_94.z = local_74 - local_34;
              local_88 = local_ac.x;
              local_84 = local_ac.y;
              local_80 = local_ac.z;
              local_64 = local_94.x;
              local_60 = local_94.y;
              local_5c = local_94.z;
              pVVar9 = Cross_Product(&local_b8,&local_ac,&local_94);
              local_4c = pVVar9->x;
              local_48 = pVVar9->y;
              local_44 = pVVar9->z;
              local_58 = local_4c + local_30.x;
              local_c = (FACE *)((int)local_c + 0x10);
              local_14 = (char *)((int)local_14 + -1);
              local_54 = local_48 + local_30.y;
              local_50 = local_44 + local_30.z;
              local_30.x = local_58;
              local_30.y = local_54;
              local_30.z = local_50;
            } while (local_14 != (char *)0x0);
          }
          pVVar9 = Normalize_Vector(&local_c4,&local_30);
          local_a0 = pVVar9->x;
          fStack_9c = pVVar9->y;
          fStack_98 = pVVar9->z;
          (local_20->plane).surf_normal.x = local_a0;
          (local_20->plane).surf_normal.y = fStack_9c;
          (local_20->plane).surf_normal.z = fStack_98;
          (local_20->plane).dist =
               -((local_20->Test_Point).x * (local_20->plane).surf_normal.x +
                (local_20->plane).surf_normal.y * (local_20->Test_Point).y +
                (local_20->plane).surf_normal.z * (local_20->Test_Point).z);
          pFVar10 = local_20;
          if ((local_24 != 0) && (local_14 = (char *)0x0, 0 < local_20->vertex_count)) {
            local_c = local_1c;
            do {
              local_40 = local_c->index;
              pVVar9 = p_Var5->normal_table + local_40;
              if (((pVVar9->x == 0.0) && (pVVar9->y == 0.0)) && (pVVar9->z == 0.0)) {
                pVVar9->x = (pFVar10->plane).surf_normal.x;
                pVVar9->y = (pFVar10->plane).surf_normal.y;
                pVVar9->z = (pFVar10->plane).surf_normal.z;
                if (local_5 == '\0') {
                  TraceWarning("repaired geom \"%.16s\" normals:");
                  local_5 = '\x01';
                }
                TraceWarning(" %d");
                pFVar10 = local_20;
              }
              local_14 = (char *)((int)local_14 + 1);
              local_c = (FACE *)&(local_c->plane).surf_normal.y;
            } while ((int)local_14 < pFVar10->vertex_count);
          }
          pFVar15 = (FACE *)(local_1c->texture_name + pFVar10->vertex_count * 0x10 + -0x20);
          local_18 = local_18 + 1;
          local_10 = (float *)((int)local_10 + *(int *)((int)local_10 + 4) * 0x10 + 0x37);
          local_c = pFVar10;
        } while (local_18 < *(int *)(param_1 + 0x1c));
        if (local_5 != '\0') {
          local_20 = pFVar15;
          TraceWarning("\n");
        }
      }
    }
  }
  else {
    p_Var5 = (_GEOMETRY *)0x0;
  }
  return p_Var5;
}
