/*
 * Entry: 00406597
 * Name: GetClosestEnemyOrMineWithin
 * Namespace: Global
 * Signature: GameObject * GetClosestEnemyOrMineWithin(GameObject * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestEnemyOrMineWithin(GameObject *param_1,float *param_2)

{
  int *piVar1;
  float fVar2;
  bool bVar3;
  float *pfVar4;
  GameObject *pGVar5;
  int iVar6;
  _OBJ76 *p_Var7;
  GameObject *pGVar8;
  float fVar9;
  Range_Search_Results local_88;
  float local_5c;
  float fStack_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  GameObject *local_44;
  float local_40;
  float local_3c;
  float local_38;
  _OBJ76 *local_34;
  GameObject *local_30;
  int *local_2c;
  GameObject *local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  GameObject *local_10;
  GameObject *local_c;
  float local_8;
  
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_8 = *param_2;
  local_14 = *param_2;
  local_40 = *pfVar4;
  local_18 = *param_2;
  local_3c = pfVar4[1];
  local_10 = (GameObject *)0x0;
  local_30 = (GameObject *)0x0;
  local_28 = (GameObject *)0x0;
  local_38 = pfVar4[2];
  local_44 = GameObjectHandle::GetObj(param_1->who_shot_JR);
  Range::Search(GameObject::objectRange,(double)local_40,(double)local_38,(double)SQRT(*param_2),
                &local_88);
  bVar3 = Range_Search_Results::Get_Next_Object(&local_88,&local_2c);
  if (bVar3) {
    do {
      pGVar5 = GameObjectHandle::GetObj(*local_2c);
      local_c = pGVar5;
      if (pGVar5 != (GameObject *)0x0) {
        piVar1 = &pGVar5->_padding_;
        iVar6 = (**(code **)(*piVar1 + 4))();
        bVar3 = GameObject::EnemyP(param_1,iVar6);
        if ((((bVar3) && (bVar3 = GameObject::EnemyP(param_1,pGVar5->perceivedTeam), bVar3)) &&
            (pGVar5->maxHealth != 0.0)) && (pGVar5->isCargo == false)) {
          bVar3 = IsMine(pGVar5);
          if (bVar3) {
            pfVar4 = (float *)(**(code **)(*piVar1 + 0xc))();
            local_5c = *pfVar4;
            fStack_58 = pfVar4[1];
            local_54 = pfVar4[2];
            fVar2 = (local_54 - local_38) * (local_54 - local_38) +
                    (local_5c - local_40) * (local_5c - local_40);
            if (fVar2 < local_8) {
              local_10 = local_c;
              local_8 = fVar2;
            }
          }
          else {
            p_Var7 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
            local_34 = p_Var7;
            iVar6 = IsCraft(p_Var7);
            if ((iVar6 != 0) || (p_Var7->class_id == CLASS_ID_PERSON)) {
              pfVar4 = (float *)(**(code **)(*piVar1 + 0xc))();
              local_50 = *pfVar4;
              local_4c = pfVar4[1];
              local_48 = pfVar4[2];
              local_24 = local_50 - local_40;
              local_20 = local_4c - local_3c;
              local_1c = local_48 - local_38;
              fVar2 = local_24 * local_24 + local_1c * local_1c;
              iVar6 = IsCraft(local_34);
              pGVar5 = local_c;
              if (iVar6 == 0) {
                if (local_c != local_44) {
                  pGVar8 = GameObjectHandle::GetObj(local_c->who_i_shot);
                  if (pGVar8 != (GameObject *)0x0) {
                    local_c = (GameObject *)pGVar5->when_i_shot;
                    fVar9 = Get_Time();
                    if (fVar9 - (float)local_c <= 10.0) {
                      iVar6 = (**(code **)(pGVar8->_padding_ + 4))();
                      bVar3 = GameObject::FriendP(param_1,iVar6);
                      if (bVar3) goto LAB_00406830;
                    }
                  }
                  if (((4900.0 < fVar2) ||
                      (p_Var7 = param_1->obj,
                      (p_Var7->transform).front_x * local_24 +
                      (p_Var7->transform).front_y * local_20 +
                      (p_Var7->transform).front_z * local_1c < 0.0)) ||
                     ((*(byte *)((int)local_34->class_ptr + 0x10c) & 0x80) == 0)) goto LAB_0040684a;
                }
LAB_00406830:
                if (fVar2 < local_18) {
                  local_28 = pGVar5;
                  local_18 = fVar2;
                }
              }
              else if (local_c->aiProcess == (AiProcess *)0x0) {
                if (fVar2 < local_14) {
                  local_30 = local_c;
                  local_14 = fVar2;
                }
              }
              else if (fVar2 < local_8) {
                local_10 = local_c;
                local_8 = fVar2;
              }
            }
          }
        }
      }
LAB_0040684a:
      bVar3 = Range_Search_Results::Get_Next_Object(&local_88,&local_2c);
    } while (bVar3);
    if ((local_10 != (GameObject *)0x0) ||
       (local_10 = local_28, local_8 = local_18, local_28 != (GameObject *)0x0)) goto LAB_0040687f;
  }
  local_10 = local_30;
  local_8 = local_14;
LAB_0040687f:
  *param_2 = local_8;
  return local_10;
}
