/*
 * Entry: 004740ea
 * Name: ShotCollision
 * Namespace: Global
 * Signature: int ShotCollision(_OBJ76 * param_1, _OBJ76 * param_2, VECTOR_3D * param_3, _OBJ76 * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ShotCollision(_OBJ76 *param_1,_OBJ76 *param_2,VECTOR_3D *param_3,_OBJ76 **param_4)

{
  POINT_VEL PVar1;
  POINT_VEL PVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D *pVVar6;
  tagENTITY *ptVar7;
  int iVar8;
  POINT_VEL *pPVar9;
  VECTOR_3D *pVVar10;
  MAT_3D *pMVar11;
  float *pfVar12;
  MAT_3D *unaff_EDI;
  float *pfVar13;
  MAT_3D *pMVar14;
  float fVar15;
  undefined1 auVar16 [12];
  undefined1 in_stack_fffffeb0 [20];
  float fVar17;
  float in_stack_fffffec8;
  undefined4 in_stack_fffffecc;
  undefined4 in_stack_fffffed0;
  undefined4 in_stack_fffffed4;
  undefined4 uVar18;
  float fVar19;
  float *pfVar20;
  MAT_3D local_104;
  MAT_3D local_c4;
  VECTOR_3D local_84;
  float local_78 [4];
  float local_68;
  float local_64;
  POINT_VEL local_60;
  float local_48;
  float local_44;
  POINT_VEL local_40;
  BBOX local_28;
  VECTOR_3D local_10;
  
  local_48 = TimeStep();
  fVar15 = TimeStepInv();
  local_78[0] = (float)(param_1->transform).posit_x;
  local_78[1] = (float)(param_1->transform).posit_y;
  local_78[2] = (float)(param_1->transform).posit_z;
  pVVar10 = &local_28.max;
  local_60.v.x = param_3->x;
  local_60.v.y = param_3->y;
  local_60.v.z = param_3->z;
  local_40.v.x = local_60.v.x - local_78[0];
  local_40.v.y = local_60.v.y - local_78[1];
  local_40.v.z = local_60.v.z - local_78[2];
  uVar18 = 0x47415f;
  VVar4.y = local_40.v.y;
  VVar4.x = local_40.v.x;
  VVar4.z = local_40.v.z;
  local_10.x = local_78[0];
  local_10.y = local_78[1];
  local_10.z = local_78[2];
  pVVar6 = ScaleVector(pVVar10,fVar15,VVar4);
  local_78[3] = pVVar6->x;
  local_68 = pVVar6->y;
  local_64 = pVVar6->z;
  if (local_10.x <= param_3->x) {
    local_28.min.x = local_10.x;
    local_28.max.x = param_3->x;
  }
  else {
    local_28.min.x = param_3->x;
    local_28.max.x = local_10.x;
  }
  if (local_10.y <= param_3->y) {
    local_28.min.y = local_10.y;
    local_28.max.y = param_3->y;
  }
  else {
    local_28.min.y = param_3->y;
    local_28.max.y = local_10.y;
  }
  if (param_3->z <= local_10.z) {
    local_28.min.z = param_3->z;
    local_28.max.z = local_10.z;
  }
  else {
    local_28.min.z = local_10.z;
    local_28.max.z = param_3->z;
  }
  ptVar7 = FirstCollidable();
  do {
    if (ptVar7 == (tagENTITY *)0x0) {
      return 0;
    }
    if ((ptVar7->obj76 != param_2) && (iVar8 = CheckBoxes(&local_28,ptVar7), iVar8 != 0)) {
      pPVar9 = PositionVelocity(&local_40,ptVar7);
      pVVar6 = &local_84;
      pfVar20 = &local_44;
      fVar15 = (ptVar7->bSphere).radius * 0.75;
      fVar17 = 8.40779e-45;
      pfVar12 = (float *)&stack0xfffffec8;
      fVar19 = local_48;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar12 = (pPVar9->p).x;
        pPVar9 = (POINT_VEL *)&(pPVar9->p).y;
        pfVar12 = pfVar12 + 1;
      }
      pfVar12 = local_78;
      pfVar13 = (float *)&stack0xfffffeb0;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar13 = *pfVar12;
        pfVar12 = pfVar12 + 1;
        pfVar13 = pfVar13 + 1;
      }
      PVar1.v.z = fVar17;
      auVar16 = in_stack_fffffeb0._0_12_;
      PVar1.p.x = (float)auVar16._0_4_;
      PVar1.p.y = (float)auVar16._4_4_;
      PVar1.p.z = (float)auVar16._8_4_;
      PVar1.v.x = (float)in_stack_fffffeb0._12_4_;
      PVar1.v.y = (float)in_stack_fffffeb0._16_4_;
      PVar2.p.y = (float)in_stack_fffffecc;
      PVar2.p.x = in_stack_fffffec8;
      PVar2.p.z = (float)in_stack_fffffed0;
      PVar2.v.x = (float)in_stack_fffffed4;
      PVar2.v.y = (float)uVar18;
      PVar2.v.z = (float)pVVar10;
      iVar8 = preclsn(PVar1,PVar2,fVar15,fVar19,pfVar20,pVVar6);
      if (iVar8 != 0) {
        *param_4 = ptVar7->obj76;
        VVar3.y = local_10.y;
        VVar3.x = local_10.x;
        VVar3.z = local_10.z;
        VVar5.y = local_68;
        VVar5.x = local_78[3];
        VVar5.z = local_64;
        pVVar10 = AddMultVectors(&local_28.max,VVar3,local_44,VVar5);
        param_3->x = pVVar10->x;
        param_3->y = pVVar10->y;
        param_3->z = pVVar10->z;
        pPVar9 = PositionVelocity(&local_60,ptVar7);
        local_40.v.x = (pPVar9->v).x;
        local_40.v.y = (pPVar9->v).y;
        local_40.v.z = (pPVar9->v).z;
        local_60.v.x = local_78[3] - local_40.v.x;
        local_60.v.y = local_68 - local_40.v.y;
        local_60.v.z = local_64 - local_40.v.z;
        local_28.max.x = local_60.v.x;
        local_28.max.y = local_60.v.y;
        local_28.max.z = local_60.v.z;
        if (*param_4 == (_OBJ76 *)0x0) {
          local_40.v.x = 0.0;
          local_40.v.y = 0.0;
          local_40.v.z = 0.0;
          local_10.x = 0.0;
          local_10.y = 0.0;
          local_10.z = 0.0;
        }
        else {
          pMVar11 = Matrix_Inverse(&local_104,unaff_EDI);
          pMVar14 = &local_c4;
          for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
            pMVar14->right_x = pMVar11->right_x;
            pMVar11 = (MAT_3D *)&pMVar11->right_y;
            pMVar14 = (MAT_3D *)&pMVar14->right_y;
          }
          Vector_Transform(&local_10,param_3,1,&local_c4);
        }
        Damage_Resolve(*param_4,param_1,&local_28.max,&local_84,&local_10);
        return 1;
      }
    }
    ptVar7 = NextCollidable();
  } while( true );
}
