/*
 * Entry: 00475eb0
 * Name: PointRecurse
 * Namespace: Global
 * Signature: int PointRecurse(POINT_VEL param_1, _OBJ76 * param_2, MAT_3D * param_3, float param_4, _OBJ76 * * param_5, float * param_6, VECTOR_3D * param_7, float param_8, int param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
PointRecurse(POINT_VEL param_1,_OBJ76 *param_2,MAT_3D *param_3,float param_4,_OBJ76 **param_5,
            float *param_6,VECTOR_3D *param_7,float param_8,int param_9)

{
  POINT_VEL PVar1;
  POINT_VEL PVar2;
  POINT_VEL PVar3;
  POINT_VEL PVar4;
  POINT_VEL PVar5;
  POINT_VEL PVar6;
  POINT_VEL PVar7;
  BBOX BVar8;
  MAT_3D *pMVar9;
  VECTOR_3D *pVVar10;
  VECTOR_3D *pVVar11;
  int iVar12;
  _OBJ76 *p_Var13;
  VECTOR_3D *pVVar14;
  undefined4 *puVar15;
  float *pfVar16;
  BBOX *pBVar17;
  MAT_3D *pMVar18;
  undefined4 *puVar19;
  float *pfVar20;
  float in_stack_fffffe50;
  undefined4 in_stack_fffffe54;
  undefined1 in_stack_fffffe58 [12];
  float in_stack_fffffe64;
  undefined8 in_stack_fffffe68;
  _OBJ76 *in_stack_fffffe70;
  _OBJ76 *p_Var21;
  MAT_3D *in_stack_fffffe74;
  undefined4 uVar22;
  float fVar23;
  _OBJ76 **pp_Var24;
  CLSN_GEOM *pCVar25;
  _OBJ76 **pp_Var26;
  float fVar27;
  VECTOR_3D *pVVar28;
  int iVar29;
  MAT_3D local_164;
  VECTOR_3D local_124;
  VECTOR_3D local_118;
  VECTOR_3D local_10c;
  VECTOR_3D local_100;
  VECTOR_3D local_f4;
  VECTOR_3D local_e8;
  VECTOR_3D local_dc;
  MAT_3D local_d0;
  VECTOR_3D local_90;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48 [3];
  VECTOR_3D local_3c;
  float local_30;
  float fStack_2c;
  float fStack_28;
  _OBJ76 *local_24;
  VECTOR_3D *local_20;
  VECTOR_3D local_1c;
  uint local_10;
  _OBJ76 *local_c;
  int local_8;
  
  local_8 = 0;
  p_Var13 = param_2;
  if (param_2 != (_OBJ76 *)0x0) {
    do {
      pMVar9 = Matrix_Multiply(&local_164,&p_Var13->transform,param_3);
      pMVar18 = &local_d0;
      for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
        pMVar18->right_x = pMVar9->right_x;
        pMVar9 = (MAT_3D *)&pMVar9->right_y;
        pMVar18 = (MAT_3D *)&pMVar18->right_y;
      }
      local_10 = p_Var13->flags & 0xf000;
      if (local_10 != 0x1000) {
        Vector_Transform(&local_90,&(p_Var13->bSphere).origin,1,&local_d0);
        local_6c = 0;
        local_68 = 0;
        local_64 = 0;
        pVVar10 = &local_f4;
        uVar22 = 0x475f45;
        local_20 = WorldVelocity(pVVar10,(VECTOR_3D)ZEXT812(0),p_Var13);
        local_84 = local_20->x;
        local_80 = local_20->y;
        local_7c = local_20->z;
        fVar23 = (p_Var13->bSphere).radius;
        if (local_10 == 0x3000) {
          if ((param_9 == 0) || (p_Var13->clsnInfo == (void *)0x0)) {
            local_10 = 0x2000;
            goto LAB_00475f7d;
          }
LAB_00476008:
          pVVar28 = &local_1c;
          pp_Var26 = &param_2;
          fVar23 = fVar23 + param_8;
          in_stack_fffffe64 = 8.40779e-45;
          pVVar14 = &local_90;
          pfVar16 = (float *)&stack0xfffffe68;
          fVar27 = param_4;
          for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
            *pfVar16 = pVVar14->x;
            pVVar14 = (VECTOR_3D *)&pVVar14->y;
            pfVar16 = pfVar16 + 1;
          }
          puVar19 = (undefined4 *)&stack0xfffffe50;
          puVar15 = (undefined4 *)register0x00000010;
          for (iVar12 = 6; puVar15 = puVar15 + 1, iVar12 != 0; iVar12 = iVar12 + -1) {
            *puVar19 = *puVar15;
            puVar19 = puVar19 + 1;
          }
          PVar2.p.y = (float)in_stack_fffffe54;
          PVar2.p.x = in_stack_fffffe50;
          PVar2.p.z = (float)in_stack_fffffe58._0_4_;
          PVar2.v.x = (float)in_stack_fffffe58._4_4_;
          PVar2.v.y = (float)in_stack_fffffe58._8_4_;
          PVar2.v.z = in_stack_fffffe64;
          PVar6.p.z = (float)in_stack_fffffe70;
          PVar6.p.x = (float)(int)in_stack_fffffe68;
          PVar6.p.y = (float)(int)((ulonglong)in_stack_fffffe68 >> 0x20);
          PVar6.v.x = (float)in_stack_fffffe74;
          PVar6.v.y = (float)uVar22;
          PVar6.v.z = (float)pVVar10;
          iVar12 = preclsn(PVar2,PVar6,fVar23,fVar27,(float *)pp_Var26,pVVar28);
          if (iVar12 != 0) {
            pVVar10 = Vector_Untransform(&local_e8,&param_1.p,&local_d0);
            local_78 = param_1.v.x - local_84;
            local_48[0] = pVVar10->x;
            local_48[1] = pVVar10->y;
            local_74 = param_1.v.y - local_80;
            local_48[2] = pVVar10->z;
            local_70 = param_1.v.z - local_7c;
            pVVar10 = &local_3c;
            pVVar14 = &local_100;
            in_stack_fffffe74 = (MAT_3D *)0x4760a2;
            local_3c.x = local_78;
            local_3c.y = local_74;
            local_3c.z = local_70;
            pVVar11 = Vector_Unrotate(pVVar14,pVVar10,&local_d0);
            pVVar28 = &local_1c;
            pp_Var26 = &param_2;
            local_3c.x = pVVar11->x;
            pCVar25 = p_Var13->clsnInfo;
            local_3c.y = pVVar11->y;
            local_3c.z = pVVar11->z;
            pfVar16 = local_48;
            pfVar20 = (float *)&stack0xfffffe68;
            fVar23 = param_4;
            for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
              *pfVar20 = *pfVar16;
              pfVar16 = pfVar16 + 1;
              pfVar20 = pfVar20 + 1;
            }
            in_stack_fffffe64 = 6.555056e-39;
            PVar7.p.z = (float)in_stack_fffffe70;
            PVar7.p.x = (float)(int)in_stack_fffffe68;
            PVar7.p.y = (float)(int)((ulonglong)in_stack_fffffe68 >> 0x20);
            PVar7.v.x = (float)in_stack_fffffe74;
            PVar7.v.y = (float)pVVar14;
            PVar7.v.z = (float)pVVar10;
            iVar12 = Cgeom_PointTest(PVar7,pCVar25,fVar23,(float *)pp_Var26,pVVar28);
            if (iVar12 != 0) {
              pVVar10 = &local_118;
              goto LAB_004760f0;
            }
          }
        }
        else {
LAB_00475f7d:
          if (local_10 == 0x2000) {
            pVVar10 = Vector_Untransform(&local_dc,&param_1.p,&local_d0);
            local_48[0] = pVVar10->x;
            local_48[1] = pVVar10->y;
            local_48[2] = pVVar10->z;
            local_60 = local_20->x;
            local_5c = local_20->y;
            local_58 = local_20->z;
            local_54 = param_1.v.x - local_60;
            local_50 = param_1.v.y - local_5c;
            pVVar10 = &local_3c;
            pVVar14 = &local_124;
            local_4c = param_1.v.z - local_58;
            in_stack_fffffe74 = (MAT_3D *)0x476172;
            local_3c.x = local_54;
            local_3c.y = local_50;
            local_3c.z = local_4c;
            pVVar11 = Vector_Unrotate(pVVar14,pVVar10,&local_d0);
            pVVar28 = &local_1c;
            local_3c.x = pVVar11->x;
            local_3c.y = pVVar11->y;
            pp_Var26 = &param_2;
            local_3c.z = pVVar11->z;
            in_stack_fffffe64 = 8.40779e-45;
            pBVar17 = &p_Var13->bBox;
            pfVar16 = (float *)&stack0xfffffe68;
            fVar23 = param_4;
            fVar27 = param_8;
            for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
              *pfVar16 = (pBVar17->min).x;
              pBVar17 = (BBOX *)&(pBVar17->min).y;
              pfVar16 = pfVar16 + 1;
            }
            pfVar16 = local_48;
            pfVar20 = (float *)&stack0xfffffe50;
            for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
              *pfVar20 = *pfVar16;
              pfVar16 = pfVar16 + 1;
              pfVar20 = pfVar20 + 1;
            }
            PVar3.p.y = (float)in_stack_fffffe54;
            PVar3.p.x = in_stack_fffffe50;
            PVar3.p.z = (float)in_stack_fffffe58._0_4_;
            PVar3.v.x = (float)in_stack_fffffe58._4_4_;
            PVar3.v.y = (float)in_stack_fffffe58._8_4_;
            PVar3.v.z = in_stack_fffffe64;
            BVar8.min.z = (float)in_stack_fffffe70;
            BVar8.min.x = (float)(int)in_stack_fffffe68;
            BVar8.min.y = (float)(int)((ulonglong)in_stack_fffffe68 >> 0x20);
            BVar8.max.x = (float)in_stack_fffffe74;
            BVar8.max.y = (float)pVVar14;
            BVar8.max.z = (float)pVVar10;
            iVar12 = PointBox(PVar3,BVar8,fVar23,(float *)pp_Var26,pVVar28,fVar27);
            if (iVar12 == 0) goto LAB_004761d3;
            pVVar10 = &local_10c;
LAB_004760f0:
            param_4 = (float)param_2;
            local_8 = 1;
            pVVar10 = Vector_Rotate(pVVar10,&local_1c,&local_d0);
          }
          else {
            if (local_10 == 0x3000) goto LAB_00476008;
            if (local_10 != 0x4000) {
              if (local_10 != 0x5000) goto LAB_004761d3;
              fVar23 = fVar23 * 0.75;
            }
            pVVar28 = &local_1c;
            pp_Var26 = &param_2;
            fVar23 = fVar23 + param_8;
            in_stack_fffffe64 = 8.40779e-45;
            pVVar14 = &local_90;
            pfVar16 = (float *)&stack0xfffffe68;
            fVar27 = param_4;
            for (iVar12 = 6; iVar12 != 0; iVar12 = iVar12 + -1) {
              *pfVar16 = pVVar14->x;
              pVVar14 = (VECTOR_3D *)&pVVar14->y;
              pfVar16 = pfVar16 + 1;
            }
            puVar19 = (undefined4 *)&stack0xfffffe50;
            puVar15 = (undefined4 *)register0x00000010;
            for (iVar12 = 6; puVar15 = puVar15 + 1, iVar12 != 0; iVar12 = iVar12 + -1) {
              *puVar19 = *puVar15;
              puVar19 = puVar19 + 1;
            }
            PVar1.p.y = (float)in_stack_fffffe54;
            PVar1.p.x = in_stack_fffffe50;
            PVar1.p.z = (float)in_stack_fffffe58._0_4_;
            PVar1.v.x = (float)in_stack_fffffe58._4_4_;
            PVar1.v.y = (float)in_stack_fffffe58._8_4_;
            PVar1.v.z = in_stack_fffffe64;
            PVar5.p.z = (float)in_stack_fffffe70;
            PVar5.p.x = (float)(int)in_stack_fffffe68;
            PVar5.p.y = (float)(int)((ulonglong)in_stack_fffffe68 >> 0x20);
            PVar5.v.x = (float)in_stack_fffffe74;
            PVar5.v.y = (float)uVar22;
            PVar5.v.z = (float)pVVar10;
            iVar12 = preclsn(PVar1,PVar5,fVar23,fVar27,(float *)pp_Var26,pVVar28);
            if (iVar12 == 0) goto LAB_004761d3;
            local_8 = 1;
            param_4 = (float)param_2;
            pVVar10 = &local_1c;
          }
          local_30 = pVVar10->x;
          fStack_2c = pVVar10->y;
          fStack_28 = pVVar10->z;
          local_c = p_Var13;
        }
      }
LAB_004761d3:
      p_Var21 = p_Var13->child;
      if (p_Var21 != (_OBJ76 *)0x0) {
        pVVar10 = &local_1c;
        pp_Var26 = &param_2;
        pp_Var24 = &local_24;
        in_stack_fffffe74 = &local_d0;
        puVar19 = (undefined4 *)&stack0xfffffe58;
        puVar15 = (undefined4 *)register0x00000010;
        fVar23 = param_4;
        fVar27 = param_8;
        iVar29 = param_9;
        for (iVar12 = 6; puVar15 = puVar15 + 1, iVar12 != 0; iVar12 = iVar12 + -1) {
          *puVar19 = *puVar15;
          puVar19 = puVar19 + 1;
        }
        in_stack_fffffe54 = 0x476214;
        PVar4.v.x = in_stack_fffffe64;
        PVar4.p.x = (float)in_stack_fffffe58._0_4_;
        PVar4.p.y = (float)in_stack_fffffe58._4_4_;
        PVar4.p.z = (float)in_stack_fffffe58._8_4_;
        PVar4.v.y = (float)(int)in_stack_fffffe68;
        PVar4.v.z = (float)(int)((ulonglong)in_stack_fffffe68 >> 0x20);
        iVar12 = PointRecurse(PVar4,p_Var21,in_stack_fffffe74,fVar23,pp_Var24,(float *)pp_Var26,
                              pVVar10,fVar27,iVar29);
        in_stack_fffffe70 = p_Var21;
        if (iVar12 != 0) {
          param_4 = (float)param_2;
          local_30 = local_1c.x;
          fStack_2c = local_1c.y;
          local_8 = 1;
          fStack_28 = local_1c.z;
          local_c = local_24;
        }
      }
      p_Var13 = p_Var13->sibling;
    } while (p_Var13 != (_OBJ76 *)0x0);
    if (local_8 != 0) {
      *param_6 = param_4;
      param_7->x = local_30;
      param_7->y = fStack_2c;
      param_7->z = fStack_28;
      *param_5 = local_c;
    }
  }
  return local_8;
}
