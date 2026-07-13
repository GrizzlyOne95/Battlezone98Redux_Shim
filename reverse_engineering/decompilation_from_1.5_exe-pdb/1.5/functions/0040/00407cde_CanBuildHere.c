/*
 * Entry: 00407cde
 * Name: CanBuildHere
 * Namespace: Global
 * Signature: bool CanBuildHere(BBOX * param_1, MAT_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CanBuildHere(BBOX *param_1,MAT_3D *param_2)

{
  float fVar1;
  BBOX *pBVar2;
  bool bVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar4;
  MAT_3D *pMVar5;
  GameObject *this;
  int iVar6;
  SPHERE *pSVar7;
  float *pfVar8;
  int iVar9;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar10;
  MAT_3D local_104;
  MAT_3D local_c4;
  Range_Search_Results local_84;
  VECTOR_3D local_58;
  float local_4c;
  undefined4 local_48;
  float local_44;
  float local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  VECTOR_3D local_28;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  float local_8;
  
  pBVar2 = param_1;
  local_58.x = (param_1->min).x;
  local_58.y = 0.0;
  local_58.z = (param_1->min).z;
  local_4c = (param_1->min).x;
  local_48 = 0;
  local_44 = (param_1->max).z;
  local_40 = (param_1->max).x;
  local_3c = 0;
  local_38 = (param_1->max).z;
  local_34 = (param_1->max).x;
  local_30 = 0;
  local_2c = (param_1->min).z;
  Vector_Transform(&local_58,&local_58,4,param_2);
  local_18 = 0x7fffffff;
  local_14 = 0x7fffffff;
  local_10 = -0x80000000;
  local_c = -0x80000000;
  pfVar8 = &local_58.z;
  param_1 = (BBOX *)0x4;
  do {
    floor((double)(((VECTOR_3D *)(pfVar8 + -2))->x * Terrain.Grid_Scale));
    _ftol2_sse();
    floor((double)(*pfVar8 * Terrain.Grid_Scale));
    _ftol2_sse();
    if (extraout_EAX < local_18) {
      local_18 = extraout_EAX;
    }
    if (local_10 < extraout_EAX) {
      local_10 = extraout_EAX;
    }
    if (extraout_EAX_00 < local_14) {
      local_14 = extraout_EAX_00;
    }
    if (local_c < extraout_EAX_00) {
      local_c = extraout_EAX_00;
    }
    pfVar8 = pfVar8 + 3;
    param_1 = (BBOX *)((int)&param_1[-1].max.z + 3);
  } while (param_1 != (BBOX *)0x0);
  local_1c = 0;
  local_8 = 0.0;
  param_1 = (BBOX *)0x0;
  for (iVar9 = local_14; iVar6 = local_18, iVar9 <= local_c; iVar9 = iVar9 + 1) {
    for (; iVar6 <= local_10; iVar6 = iVar6 + 1) {
      bVar3 = CellIsBlocked(iVar6,iVar9);
      if (bVar3) {
        return false;
      }
      iVar4 = GetTerY(iVar6,iVar9);
      local_1c = local_1c + iVar4;
      local_8 = (float)((int)local_8 + iVar4 * iVar4);
      param_1 = (BBOX *)((int)&(param_1->min).x + 1);
    }
  }
  if ((int)param_1 * (int)local_8 - local_1c * local_1c <=
      ((int)param_1 * 100 + -100) * (int)param_1) {
    pMVar5 = Matrix_Inverse(&local_104,unaff_EDI);
    fVar1 = (float)local_c;
    pMVar10 = &local_c4;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar10->right_x = pMVar5->right_x;
      pMVar5 = (MAT_3D *)&pMVar5->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    Range::Search(GameObject::objectRange,(double)(Terrain.Grid_Size * (float)local_18 - 20.0),
                  (double)((float)local_14 * Terrain.Grid_Size - 20.0),
                  (double)((float)local_10 * Terrain.Grid_Size + 20.0),
                  (double)(fVar1 * Terrain.Grid_Size + 20.0),&local_84);
    do {
      do {
        do {
          bVar3 = Range_Search_Results::Get_Next_Object(&local_84,(int **)&param_1);
          if (!bVar3) {
            return true;
          }
          this = GameObjectHandle::GetObj((int)(param_1->min).x);
        } while (this == (GameObject *)0x0);
        iVar6 = (**(code **)this->_padding_)();
        iVar9 = *(int *)(iVar6 + 0x28);
      } while (((((iVar9 != 2) && (iVar9 != 10)) && (iVar9 != 5)) && ((iVar9 != 7 && (iVar9 != 3))))
              && (*(int *)(iVar6 + 0x20) != 0x54555252));
      pSVar7 = GameObject::GetSphere(this);
      local_8 = pSVar7->radius;
      pfVar8 = (float *)(**(code **)(this->_padding_ + 0xc))();
      local_28.x = *pfVar8;
      local_28.y = pfVar8[1];
      local_28.z = pfVar8[2];
      Vector_Transform(&local_28,&local_28,1,&local_c4);
    } while (((local_28.x <= (pBVar2->min).x - local_8) || (local_8 + (pBVar2->max).x <= local_28.x)
             ) || ((local_28.z <= (pBVar2->min).z - local_8 ||
                   (local_8 + (pBVar2->max).z <= local_28.z))));
  }
  return false;
}
