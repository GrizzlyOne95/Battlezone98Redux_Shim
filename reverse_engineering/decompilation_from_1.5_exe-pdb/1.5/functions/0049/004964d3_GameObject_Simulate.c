/*
 * Entry: 004964d3
 * Name: GameObject_Simulate
 * Namespace: Global
 * Signature: void GameObject_Simulate(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GameObject_Simulate(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  bool bVar2;
  int iVar3;
  QUAT *pQVar4;
  QUAT *pQVar5;
  MAT_3D *pMVar6;
  float *pfVar7;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar8;
  float fVar9;
  MAT_3D local_c4;
  float local_84 [10];
  double local_5c;
  double local_54;
  double local_4c;
  float local_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined1 local_34 [16];
  undefined1 local_24 [12];
  float fStack_18;
  undefined1 local_14 [12];
  float fStack_8;
  
  p_Var1 = param_1;
  if (param_1 == (_OBJ76 *)0x0) {
    param_1 = (_OBJ76 *)0x0;
  }
  else {
    param_1 = param_1->gameObj;
  }
  if (param_1 != (_OBJ76 *)0x0) {
    iVar3 = Net_IsNetGame();
    if (iVar3 == 0) {
      fVar9 = TimeStep();
      fVar9 = fVar9 + *(float *)((param_1->tex_info).group + 4);
      *(float *)((param_1->tex_info).group + 4) = fVar9;
      if (0.0 < fVar9) {
        (**(code **)((param_1->objHandle).handle + 0x3c))(fVar9);
        (param_1->tex_info).group[4] = '\0';
        (param_1->tex_info).group[5] = '\0';
        (param_1->tex_info).group[6] = '\0';
        (param_1->tex_info).group[7] = '\0';
      }
    }
    else {
      bVar2 = DistributedObject::IsRemote((DistributedObject *)&param_1->transform);
      if (bVar2) {
        pMVar6 = &p_Var1->transform;
        pfVar7 = local_84;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar7 = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pfVar7 = pfVar7 + 1;
        }
        if (*(double *)&param_1->NavGroup != -1.0) {
          pfVar7 = &(param_1->transform).up_y;
          pMVar6 = &p_Var1->transform;
          for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
            pMVar6->right_x = *pfVar7;
            pfVar7 = pfVar7 + 1;
            pMVar6 = (MAT_3D *)&pMVar6->right_y;
          }
        }
      }
      fVar9 = TimeStep();
      fStack_18 = 0.0;
      *(float *)((param_1->tex_info).group + 4) = fVar9 + *(float *)((param_1->tex_info).group + 4);
      do {
        fVar9 = Clamp(*(float *)((param_1->tex_info).group + 4),0.001,0.1);
        iVar3 = (param_1->objHandle).handle;
        *(float *)((param_1->tex_info).group + 4) =
             *(float *)((param_1->tex_info).group + 4) - fVar9;
        (**(code **)(iVar3 + 0x3c))(fVar9);
        if ((p_Var1->flags & 0x200) != 0) {
          return;
        }
        fStack_18 = (float)((int)fStack_18 + 1);
      } while ((0.0 < *(float *)((param_1->tex_info).group + 4)) && ((int)fStack_18 < 5));
      if (((p_Var1->flags & 0x200) == 0) &&
         (bVar2 = DistributedObject::IsRemote((DistributedObject *)&param_1->transform), bVar2)) {
        pMVar6 = (MAT_3D *)local_14;
        pQVar4 = Matrix_to_Quaternion((QUAT *)pMVar6,unaff_EDI);
        local_34._0_4_ = (pQVar4->n).x;
        local_34._4_4_ = (pQVar4->n).y;
        local_34._8_8_ = *(undefined8 *)&(pQVar4->n).z;
        NormalizeQuat((QUAT *)local_34);
        pQVar4 = (QUAT *)local_24;
        pQVar5 = Matrix_to_Quaternion(pQVar4,pMVar6);
        local_14._0_4_ = (pQVar5->n).x;
        local_14._4_4_ = (pQVar5->n).y;
        unique0x1000035a = *(double *)&(pQVar5->n).z;
        NormalizeQuat((QUAT *)local_14);
        pQVar5 = MySlerp((QUAT *)local_24,(QUAT *)local_34,(QUAT *)local_14,0.5);
        local_14._0_4_ = (pQVar5->n).x;
        local_14._4_4_ = (pQVar5->n).y;
        local_14._8_4_ = (pQVar5->n).z;
        fStack_8 = pQVar5->w;
        NormalizeQuat((QUAT *)local_14);
        local_44 = (float)local_14._0_4_;
        fStack_40 = (float)local_14._4_4_;
        fStack_3c = (float)local_14._8_4_;
        fStack_38 = fStack_8;
        pMVar6 = &p_Var1->transform;
        pfVar7 = &(param_1->transform).up_y;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar7 = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pfVar7 = pfVar7 + 1;
        }
        unique0x0000aa00 = (p_Var1->transform).posit_x;
        local_34._8_8_ = (p_Var1->transform).posit_y;
        unique0x0000aa00 = (p_Var1->transform).posit_z;
        pMVar6 = Quaternion_to_Matrix(&local_c4,pQVar4);
        pMVar8 = &p_Var1->transform;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          pMVar8->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        (p_Var1->transform).posit_x = (stack0xffffffe4 - local_5c) * 0.30000001192092896 + local_5c;
        (p_Var1->transform).posit_y =
             ((double)local_34._8_8_ - local_54) * 0.30000001192092896 + local_54;
        (p_Var1->transform).posit_z = (stack0xfffffff4 - local_4c) * 0.30000001192092896 + local_4c;
        GameObject::UpdatePosition((GameObject *)param_1);
      }
    }
  }
  return;
}
