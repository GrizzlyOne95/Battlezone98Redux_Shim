/*
 * Entry: 004153fe
 * Name: HuntTask::Choose_Next_Spot
 * Namespace: HuntTask
 * Signature: int Choose_Next_Spot(HuntTask * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall HuntTask::Choose_Next_Spot(HuntTask *this,VECTOR_3D *param_1)

{
  int *piVar1;
  float fVar2;
  bool bVar3;
  float *pfVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  float *pfVar7;
  float *pfVar8;
  float fVar9;
  float local_d0 [15];
  float local_94 [6];
  float fStack_7c;
  float local_78;
  float local_74 [6];
  float fStack_5c;
  float local_58;
  float local_54;
  float fStack_50;
  float fStack_4c;
  float local_48;
  float fStack_44;
  float local_40;
  GameObject *local_3c;
  Team *local_38;
  float local_34;
  int local_30;
  float local_2c;
  HuntTask *local_28;
  float local_24;
  float local_20;
  int iVar10;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar10 = 0;
  local_14 = 0;
  local_c = 0;
  local_28 = this;
  fVar9 = Get_Time();
  if ((5.0 < fVar9 - this->time_of_Mth_last_try[0]) || (this->total_tries < 5)) {
    local_74[0] = 0.0;
    local_74[1] = 0.0;
    local_74[2] = 0.0;
    local_74[3] = 0.0;
    local_74[4] = 0.0;
    local_94[0] = -1.0;
    local_94[1] = -1.0;
    local_94[2] = -1.0;
    local_94[3] = -1.0;
    local_94[4] = -1.0;
    local_30 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
    pfVar4 = (float *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0xc))();
    local_8 = 0;
    local_74[5] = *pfVar4;
    fStack_5c = pfVar4[1];
    local_58 = pfVar4[2];
    do {
      if ((local_8 != local_30) &&
         (bVar3 = GameObject::FriendP((GameObject *)this->_padding_,local_8), !bVar3)) {
        local_38 = Team::GetTeam(local_8);
        local_10 = 0;
        do {
          local_3c = Team::GetSlot(local_38,local_10);
          if ((local_3c != (GameObject *)0x0) &&
             ((local_3c->isVisible >> ((byte)local_30 & 0x1f) & 1) != 0)) {
            piVar1 = &local_3c->_padding_;
            pfVar4 = (float *)(**(code **)(*piVar1 + 0xc))();
            local_48 = *pfVar4;
            fStack_44 = pfVar4[1];
            local_40 = pfVar4[2];
            fVar9 = pfVar4[2] - local_58;
            fVar2 = *pfVar4 - local_74[5];
            local_20 = fVar2 * fVar2 + fVar9 * fVar9;
            if (local_20 < 22500.0) {
              p_Var5 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
              iVar6 = IsBuilding(p_Var5);
              if (iVar6 != 0) goto LAB_004155cc;
            }
            local_c = local_c + 1;
            bVar3 = false;
            pfVar4 = local_d0;
            iVar6 = 0;
            do {
              if (bVar3) {
                local_94[5] = *pfVar4;
                fStack_7c = pfVar4[1];
                local_78 = pfVar4[2];
                fVar2 = *(float *)((int)local_74 + iVar6);
                *(float *)((int)local_74 + iVar6) = local_2c;
                *pfVar4 = local_54;
                local_24 = fVar2;
                pfVar4[1] = fStack_50;
                fVar9 = *(float *)((int)local_94 + iVar6);
                *(float *)((int)local_94 + iVar6) = local_34;
                pfVar4[2] = fStack_4c;
                local_34 = fVar9;
                local_2c = fVar2;
                pfVar7 = local_94 + 5;
                pfVar8 = &local_54;
LAB_004155b7:
                *pfVar8 = *pfVar7;
                pfVar8[1] = pfVar7[1];
                pfVar8[2] = pfVar7[2];
              }
              else {
                pfVar7 = (float *)((int)local_94 + iVar6);
                if ((local_20 < *pfVar7) || (*(int *)((int)local_74 + iVar6) == 0)) {
                  local_34 = *pfVar7;
                  local_2c = *(float *)((int)local_74 + iVar6);
                  *pfVar7 = local_20;
                  local_54 = *pfVar4;
                  fStack_50 = pfVar4[1];
                  fStack_4c = pfVar4[2];
                  *(float *)((int)local_74 + iVar6) = (float)local_3c;
                  pfVar7 = &local_48;
                  bVar3 = true;
                  pfVar8 = pfVar4;
                  goto LAB_004155b7;
                }
              }
              iVar6 = iVar6 + 4;
              pfVar4 = pfVar4 + 3;
              this = local_28;
            } while (iVar6 < 0x14);
          }
LAB_004155cc:
          local_10 = local_10 + 1;
        } while (local_10 < 0x5a);
      }
      local_8 = local_8 + 1;
    } while (local_8 < 0x10);
    if (5 < local_c) {
      local_c = 5;
    }
    if (0 < local_c) {
      iVar10 = rand();
      param_1->x = local_d0[(iVar10 % local_c) * 3];
      param_1->y = 0.0;
      param_1->z = local_d0[(iVar10 % local_c) * 3 + 2];
      return 1;
    }
  }
  do {
    if (7 < local_14) break;
    iVar10 = Try_New_Hunt(this,(float *)&local_28,&local_24,local_14);
    local_14 = local_14 + 1;
  } while (iVar10 == 0);
  if (iVar10 != 0) {
    param_1->x = (float)local_28;
    param_1->y = 0.0;
    param_1->z = local_24;
  }
  return iVar10;
}
