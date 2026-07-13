/*
 * Entry: 004cea9b
 * Name: FlagDisplay::Submit
 * Namespace: FlagDisplay
 * Signature: void Submit(FlagDisplay * this, CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Type propagation algorithm not settling */

void __thiscall FlagDisplay::Submit(FlagDisplay *this,CAMERA *param_1)

{
  int *piVar1;
  VECTOR_3D_LONG VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  float fVar5;
  float fVar6;
  bool bVar7;
  int iVar8;
  VECTOR_3D *pVVar9;
  SPHERE *pSVar10;
  long lVar11;
  int extraout_EAX;
  float fVar12;
  int iVar13;
  int iVar14;
  int local_e0 [16];
  Range_Search_Results local_a0;
  double local_74;
  double local_6c;
  double local_64;
  double local_5c;
  double local_54;
  float local_4c;
  float local_48;
  float local_44;
  VECTOR_3D local_40;
  float local_34;
  GameObject *local_30;
  int local_2c;
  VECTOR_3D local_28;
  GameObject *local_1c;
  float local_18;
  float local_14;
  float local_10;
  int *local_8;
  
  if (((View_Record.Current_View != EDIT_VIEW) && (View_Record.Current_View != TWO_D_VIEW)) &&
     (this->flagIndex != 0)) {
    if (this->makeTexture != false) {
      GenerateFlags(this);
      this->makeTexture = false;
    }
    local_30 = GameObject::userObject;
    if (GameObject::userObject != (GameObject *)0x0) {
      local_18 = (float)param_1->View_Pyramid[0].x;
      local_14 = (float)param_1->View_Pyramid[0].y;
      local_10 = (float)param_1->View_Pyramid[0].z;
      local_e0[0] = 0;
      memset(local_e0 + 1,0,0x3c);
      iVar8 = 0;
      do {
        iVar13 = *(int *)((int)NetPlayer::netPlayerByTeam + iVar8 + 4);
        if (iVar13 != 0) {
          *(undefined4 *)((int)local_e0 + iVar8 + 4U) = *(undefined4 *)(iVar13 + 0x128);
        }
        iVar8 = iVar8 + 4;
      } while (iVar8 < 0x3c);
      Range::Search(GameObject::objectRange,(double)local_18,(double)local_10,100.0,&local_a0);
LAB_004ced5c:
      bVar7 = Range_Search_Results::Get_Next_Object(&local_a0,&local_8);
      if (bVar7) {
        local_1c = GameObject::GetObj(*local_8);
        if (((local_1c != (GameObject *)0x0) && (local_1c != local_30)) &&
           ((local_1c->obj->flags & 0x600) == 0)) {
          piVar1 = &local_1c->_padding_;
          iVar8 = (**(code **)(*piVar1 + 4))();
          local_2c = local_e0[iVar8];
          if (0 < local_2c) {
            iVar8 = (**(code **)*piVar1)();
            if (*(int *)(iVar8 + 0x28) != 1) {
              iVar8 = (**(code **)*piVar1)();
              if (*(int *)(iVar8 + 0x28) != 6) {
                iVar8 = (**(code **)*piVar1)();
                if (*(int *)(iVar8 + 0x28) != 4) {
                  iVar8 = (**(code **)*piVar1)();
                  if (*(int *)(iVar8 + 0x28) != 2) goto LAB_004ced5c;
                }
              }
            }
            pVVar9 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
            local_40.x = pVVar9->x;
            local_40.y = pVVar9->y;
            local_40.z = pVVar9->z;
            VVar4.y = local_14;
            VVar4.x = local_18;
            VVar4.z = local_10;
            fVar12 = Dist3D_Squared(*pVVar9,VVar4);
            if (fVar12 <= 10000.0) {
              Vector_Transform(&local_28,&local_40,1,&param_1->Matrix);
              if (0.0001 <= local_28.z) {
                pSVar10 = GameObject::GetSphere(local_1c);
                lVar11 = Camera_Bounding_Sphere_Test(param_1,&local_28,pSVar10->radius);
                if (lVar11 < 1) {
                  local_34 = 1.0;
                  local_4c = local_40.x - local_18;
                  local_48 = local_40.y - local_14;
                  local_44 = local_40.z - local_10;
                  VVar2.y._0_4_ = SUB84((double)local_14,0);
                  VVar2.x = (double)local_18;
                  VVar2.y._4_4_ = (int)((ulonglong)(double)local_14 >> 0x20);
                  VVar2.z._0_4_ = SUB84((double)local_10,0);
                  VVar2.z._4_4_ = (int)((ulonglong)(double)local_10 >> 0x20);
                  VVar3.y = local_48;
                  VVar3.x = local_4c;
                  VVar3.z = local_44;
                  iVar8 = Terrain_GetIntersection(VVar2,VVar3,&local_34,(VECTOR_3D *)0x0);
                  if (iVar8 == 0) {
                    fVar12 = 1.0 / local_28.z;
                    local_64 = (double)(param_1->Const_x * local_28.x * fVar12 + param_1->Orig_x +
                                       (float)Float2Int);
                    local_54 = (double)(local_28.y * fVar12 * param_1->Const_y + param_1->Orig_y +
                                       (float)Float2Int);
                    pSVar10 = GameObject::GetSphere(local_1c);
                    iVar14 = 0x290000;
                    fVar5 = (float)Float2Int;
                    local_5c = (double)(pSVar10->radius * param_1->Const_x * fVar12 + fVar5);
                    fVar6 = param_1->Const_x * fVar12;
                    local_74 = (double)(fVar6 + fVar6 + fVar5);
                    local_6c = (double)(fVar5 - fVar12 * param_1->Const_y);
                    iVar8 = local_74._0_4_;
                    iVar13 = local_6c._0_4_;
                    _ftol2_sse();
                    DrawScaledSprite(param_1,local_2c,local_64._0_4_,local_54._0_4_ - local_5c._0_4_
                                     ,extraout_EAX,iVar8,iVar13,iVar14);
                  }
                }
              }
            }
          }
        }
        goto LAB_004ced5c;
      }
    }
  }
  return;
}
