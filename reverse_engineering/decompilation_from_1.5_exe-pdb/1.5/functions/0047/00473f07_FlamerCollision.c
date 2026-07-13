/*
 * Entry: 00473f07
 * Name: FlamerCollision
 * Namespace: Global
 * Signature: int FlamerCollision(SPHERE param_1, SPHERE param_2, DAMAGE param_3, _OBJ76 * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl FlamerCollision(SPHERE param_1,SPHERE param_2,DAMAGE param_3,_OBJ76 **param_4)

{
  POINT_VEL PVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D *pVVar5;
  tagENTITY *ptVar6;
  SPHERE *pSVar7;
  MAT_3D *pMVar8;
  int iVar9;
  float *pfVar10;
  MAT_3D *unaff_EDI;
  float *pfVar11;
  MAT_3D *pMVar12;
  float fVar13;
  float fVar14;
  undefined1 auVar15 [12];
  undefined1 in_stack_fffffeb0 [16];
  undefined4 in_stack_fffffec0;
  VECTOR_3D *in_stack_fffffec4;
  _OBJ76 **pp_Var16;
  float *pfVar17;
  float fVar18;
  float fVar19;
  int iVar20;
  MAT_3D local_110;
  MAT_3D local_d0;
  SPHERE local_90;
  VECTOR_3D local_80;
  VECTOR_3D local_74;
  float local_68 [4];
  float fStack_58;
  float fStack_54;
  VECTOR_3D local_50;
  float local_44;
  float fStack_40;
  float fStack_3c;
  float local_38;
  float local_34;
  float fStack_30;
  float fStack_2c;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  float local_8;
  
  fVar14 = param_1.origin.x - param_2.origin.x;
  fVar18 = param_1.origin.y - param_2.origin.y;
  fVar19 = param_1.origin.z - param_2.origin.z;
  local_18 = fVar14;
  local_14 = fVar18;
  local_10 = fVar19;
  fVar13 = TimeStepInv();
  VVar3.y = fVar18;
  VVar3.x = fVar14;
  VVar3.z = fVar19;
  pVVar5 = ScaleVector(&local_28,fVar13,VVar3);
  local_c = 0;
  local_34 = pVVar5->x;
  fStack_30 = pVVar5->y;
  fStack_2c = pVVar5->z;
  ptVar6 = FirstCollidable();
  while (ptVar6 != (tagENTITY *)0x0) {
    if (ptVar6->obj76 != param_3.damager) {
      pSVar7 = Entity_WorldSphere(&local_90,ptVar6);
      local_44 = (pSVar7->origin).x;
      fStack_40 = (pSVar7->origin).y;
      fStack_3c = (pSVar7->origin).z;
      local_38 = pSVar7->radius;
      local_8 = local_38 + param_1.radius;
      local_68[0] = param_1.origin.x;
      local_68[1] = param_1.origin.y;
      local_68[2] = param_1.origin.z;
      local_68[3] = local_34;
      fStack_58 = fStack_30;
      fStack_54 = fStack_2c;
      fVar14 = Dist3D_Squared(param_1.origin,pSVar7->origin);
      if (fVar14 < local_8 * local_8) {
        iVar20 = 1;
        fVar18 = 0.0;
        pVVar5 = &local_74;
        pfVar17 = &local_1c;
        pp_Var16 = param_4;
        fVar14 = TimeStep();
        pfVar10 = local_68;
        pfVar11 = (float *)&stack0xfffffeb0;
        for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
          *pfVar11 = *pfVar10;
          pfVar10 = pfVar10 + 1;
          pfVar11 = pfVar11 + 1;
        }
        PVar1.v.y = (float)in_stack_fffffec0;
        auVar15 = in_stack_fffffeb0._0_12_;
        PVar1.p.x = (float)auVar15._0_4_;
        PVar1.p.y = (float)auVar15._4_4_;
        PVar1.p.z = (float)auVar15._8_4_;
        PVar1.v.x = (float)in_stack_fffffeb0._12_4_;
        PVar1.v.z = (float)in_stack_fffffec4;
        iVar9 = PointEntityCheck(PVar1,ptVar6,fVar14,pp_Var16,pfVar17,pVVar5,fVar18,iVar20);
        if (iVar9 != 0) {
          in_stack_fffffec4 = &local_80;
          in_stack_fffffec0 = 0x47402e;
          VVar2.y = local_68[1];
          VVar2.x = local_68[0];
          VVar2.z = local_68[2];
          VVar4.y = fStack_30;
          VVar4.x = local_34;
          VVar4.z = fStack_2c;
          pVVar5 = AddMultVectors(in_stack_fffffec4,VVar2,local_1c,VVar4);
          local_50.x = pVVar5->x;
          local_50.y = pVVar5->y;
          local_50.z = pVVar5->z;
          if (*param_4 == (_OBJ76 *)0x0) {
            local_18 = 0.0;
            local_14 = 0.0;
            local_10 = 0.0;
            local_28.x = 0.0;
            local_28.y = 0.0;
            local_28.z = 0.0;
          }
          else {
            pMVar8 = obj_rel_parent_matrix(&local_110,*param_4,(_OBJ76 *)0x0);
            pMVar12 = &local_d0;
            for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
              pMVar12->right_x = pMVar8->right_x;
              pMVar8 = (MAT_3D *)&pMVar8->right_y;
              pMVar12 = (MAT_3D *)&pMVar12->right_y;
            }
            pMVar8 = Matrix_Inverse(&local_110,unaff_EDI);
            pMVar12 = &local_d0;
            for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
              pMVar12->right_x = pMVar8->right_x;
              pMVar8 = (MAT_3D *)&pMVar8->right_y;
              pMVar12 = (MAT_3D *)&pMVar12->right_y;
            }
            Vector_Transform(&local_28,&local_50,1,&local_d0);
          }
          Flame_Damage_Resolve(*param_4,param_3,&local_28);
          local_c = 1;
        }
      }
    }
    ptVar6 = NextCollidable();
  }
  return local_c;
}
