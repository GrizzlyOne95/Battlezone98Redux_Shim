/*
 * Entry: 00473031
 * Name: CarRecurse
 * Namespace: Global
 * Signature: int CarRecurse(BOX_INFO * param_1, _OBJ76 * param_2, MAT_3D * param_3, float param_4, CLSN_INFO * param_5, CLSN_INFO * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
CarRecurse(BOX_INFO *param_1,_OBJ76 *param_2,MAT_3D *param_3,float param_4,CLSN_INFO *param_5,
          CLSN_INFO *param_6)

{
  _OBJ76 *p_Var1;
  POINT_VEL PVar2;
  POINT_VEL PVar3;
  MAT_3D *pMVar4;
  VECTOR_3D *pVVar5;
  int iVar6;
  VECTOR_3D *pVVar7;
  BOX_INFO *pBVar8;
  VECTOR_3D *pVVar9;
  BBOX *pBVar10;
  CLSN_INFO *pCVar11;
  CLSN_INFO *unaff_EDI;
  float *pfVar12;
  BOX_INFO *pBVar13;
  BBOX *pBVar14;
  MAT_3D *pMVar15;
  CLSN_INFO *pCVar16;
  undefined1 auVar17 [12];
  undefined1 in_stack_fffffd8c [20];
  float fVar18;
  undefined1 in_stack_fffffda4 [12];
  undefined4 in_stack_fffffdb0;
  undefined4 uVar19;
  float fVar20;
  float *pfVar21;
  MAT_3D local_228;
  BOX_INFO local_1e8;
  CLSN_INFO local_170;
  CLSN_INFO local_f8;
  VECTOR_3D local_80;
  VECTOR_3D local_74;
  MAT_3D local_68;
  VECTOR_3D local_28;
  float local_1c;
  float fStack_18;
  float fStack_14;
  float local_10;
  uint local_c;
  int local_8;
  
  local_8 = 0;
  do {
    if (param_2 == (_OBJ76 *)0x0) {
      return local_8;
    }
    pMVar4 = Matrix_Multiply(&local_228,&param_2->transform,param_3);
    pMVar15 = &local_68;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      pMVar15->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar15 = (MAT_3D *)&pMVar15->right_y;
    }
    local_c = param_2->flags & 0xf000;
    if (local_c != 0x1000) {
      Vector_Transform(&local_28,&(param_2->bSphere).origin,1,&local_68);
      pVVar9 = &local_80;
      uVar19 = 0x4730b4;
      pVVar5 = WorldVelocity(pVVar9,(param_2->bSphere).origin,param_2);
      local_1c = pVVar5->x;
      fStack_18 = pVVar5->y;
      fStack_14 = pVVar5->z;
      fVar20 = param_1->radius + (param_2->bSphere).radius;
      pVVar5 = &local_74;
      pfVar21 = &local_10;
      fVar18 = 8.40779e-45;
      pVVar7 = &local_28;
      pfVar12 = (float *)&stack0xfffffda4;
      pBVar13 = (BOX_INFO *)param_4;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar12 = pVVar7->x;
        pVVar7 = (VECTOR_3D *)&pVVar7->y;
        pfVar12 = pfVar12 + 1;
      }
      pBVar8 = param_1;
      pfVar12 = (float *)&stack0xfffffd8c;
      for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
        *pfVar12 = (pBVar8->pv).p.x;
        pBVar8 = (BOX_INFO *)&(pBVar8->pv).p.y;
        pfVar12 = pfVar12 + 1;
      }
      PVar2.v.z = fVar18;
      auVar17 = in_stack_fffffd8c._0_12_;
      PVar2.p.x = (float)auVar17._0_4_;
      PVar2.p.y = (float)auVar17._4_4_;
      PVar2.p.z = (float)auVar17._8_4_;
      PVar2.v.x = (float)in_stack_fffffd8c._12_4_;
      PVar2.v.y = (float)in_stack_fffffd8c._16_4_;
      PVar3.v.x = (float)in_stack_fffffdb0;
      PVar3.p.x = (float)in_stack_fffffda4._0_4_;
      PVar3.p.y = (float)in_stack_fffffda4._4_4_;
      PVar3.p.z = (float)in_stack_fffffda4._8_4_;
      PVar3.v.y = (float)uVar19;
      PVar3.v.z = (float)pVVar9;
      iVar6 = preclsn(PVar2,PVar3,fVar20,(float)pBVar13,pfVar21,pVVar5);
      if (iVar6 != 0) {
        local_170.collided = 0;
        local_f8.collided = 0;
        if (local_c == 0x2000) {
          pVVar9 = &local_28;
          pBVar13 = &local_1e8;
          for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
            (pBVar13->pv).p.x = pVVar9->x;
            pVVar9 = (VECTOR_3D *)&pVVar9->y;
            pBVar13 = (BOX_INFO *)&(pBVar13->pv).p.y;
          }
          local_1e8.radius = (param_2->bSphere).radius;
          pBVar10 = &param_2->bBox;
          pBVar14 = &local_1e8.box;
          for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
            (pBVar14->min).x = (pBVar10->min).x;
            pBVar10 = (BBOX *)&(pBVar10->min).y;
            pBVar14 = (BBOX *)&(pBVar14->min).y;
          }
          pMVar4 = &local_68;
          pMVar15 = &local_1e8.mat;
          for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
            pMVar15->right_x = pMVar4->right_x;
            pMVar4 = (MAT_3D *)&pMVar4->right_y;
            pMVar15 = (MAT_3D *)&pMVar15->right_y;
          }
          local_1e8.obj = param_2;
          iVar6 = BoxBox(&local_1e8,(BOX_INFO *)param_4,(float)&local_f8,&local_170,unaff_EDI);
          if (iVar6 == 0) {
            BoxBox(param_1,(BOX_INFO *)param_4,(float)&local_170,&local_f8,unaff_EDI);
          }
        }
        else if (local_c == 0x3000) {
          iVar6 = BoxGeom((BOX_INFO *)param_2,(_OBJ76 *)&local_68,(MAT_3D *)param_4,(float)&local_f8
                          ,&local_170,unaff_EDI);
          if ((iVar6 == 0) &&
             ((param_1->obj->class_id == CLASS_ID_VEHICLE ||
              (10.0 <= (param_1->box).max.y - (param_1->box).min.y)))) {
            GeomBox(param_2,&local_68,param_1,param_4,&local_f8,unaff_EDI);
          }
        }
        else {
          if (local_c == 0x4000) {
            p_Var1 = (_OBJ76 *)0x3f800000;
          }
          else {
            if (local_c != 0x5000) goto LAB_004732cb;
            p_Var1 = (_OBJ76 *)0x3f400000;
          }
          in_stack_fffffdb0 = 0x473168;
          BoxSphere((BOX_INFO *)param_2,p_Var1,(float)&local_68,(MAT_3D *)param_4,(float)&local_f8,
                    &local_170,unaff_EDI);
        }
        if (local_f8.collided != 0) {
          param_4 = local_f8.t;
          pCVar11 = &local_f8;
          pCVar16 = param_5;
          for (iVar6 = 0x1e; iVar6 != 0; iVar6 = iVar6 + -1) {
            pCVar16->collided = pCVar11->collided;
            pCVar11 = (CLSN_INFO *)&pCVar11->obj;
            pCVar16 = (CLSN_INFO *)&pCVar16->obj;
          }
          pCVar11 = &local_170;
          pCVar16 = param_6;
          for (iVar6 = 0x1e; iVar6 != 0; iVar6 = iVar6 + -1) {
            pCVar16->collided = pCVar11->collided;
            pCVar11 = (CLSN_INFO *)&pCVar11->obj;
            pCVar16 = (CLSN_INFO *)&pCVar16->obj;
          }
          local_8 = 1;
        }
      }
    }
LAB_004732cb:
    if (param_2->child != (_OBJ76 *)0x0) {
      in_stack_fffffdb0 = 0x4732ef;
      iVar6 = CarRecurse(param_1,param_2->child,&local_68,param_4,param_5,param_6);
      if (iVar6 != 0) {
        local_8 = 1;
      }
    }
    param_2 = param_2->sibling;
  } while( true );
}
