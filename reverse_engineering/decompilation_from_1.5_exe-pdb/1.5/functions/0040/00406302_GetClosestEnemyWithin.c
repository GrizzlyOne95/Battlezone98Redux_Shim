/*
 * Entry: 00406302
 * Name: GetClosestEnemyWithin
 * Namespace: Global
 * Signature: GameObject * GetClosestEnemyWithin(GameObject * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl GetClosestEnemyWithin(GameObject *param_1,float *param_2)

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
  Range_Search_Results local_7c;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  GameObject *local_2c;
  GameObject *local_28;
  GameObject *local_24;
  GameObject *local_20;
  int *local_1c;
  _OBJ76 *local_18;
  GameObject *local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_8 = *param_2;
  local_10 = *param_2;
  local_44 = *pfVar4;
  local_c = *param_2;
  local_40 = pfVar4[1];
  local_20 = (GameObject *)0x0;
  local_28 = (GameObject *)0x0;
  local_24 = (GameObject *)0x0;
  local_3c = pfVar4[2];
  local_2c = GameObjectHandle::GetObj(param_1->who_shot_JR);
  Range::Search(collision_range_search,(double)local_44,(double)local_3c,(double)SQRT(*param_2),
                &local_7c);
  bVar3 = Range_Search_Results::Get_Next_Object(&local_7c,&local_1c);
  pGVar5 = local_28;
  fVar2 = local_10;
  if (bVar3) {
    do {
      pGVar5 = GameObjectHandle::GetObj(*local_1c);
      local_14 = pGVar5;
      if (pGVar5 != (GameObject *)0x0) {
        piVar1 = &pGVar5->_padding_;
        iVar6 = (**(code **)(*piVar1 + 4))();
        bVar3 = GameObject::EnemyP(param_1,iVar6);
        if ((((bVar3) && (bVar3 = GameObject::EnemyP(param_1,pGVar5->perceivedTeam), bVar3)) &&
            (pGVar5->maxHealth != 0.0)) && (pGVar5->isCargo == false)) {
          p_Var7 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
          local_18 = p_Var7;
          iVar6 = IsCraft(p_Var7);
          if ((iVar6 != 0) || (p_Var7->class_id == CLASS_ID_PERSON)) {
            pfVar4 = (float *)(**(code **)(*piVar1 + 0xc))();
            local_50 = *pfVar4;
            local_4c = pfVar4[1];
            local_48 = pfVar4[2];
            local_38 = local_50 - local_44;
            local_34 = local_4c - local_40;
            local_30 = local_48 - local_3c;
            fVar2 = local_38 * local_38 + local_30 * local_30;
            iVar6 = IsCraft(local_18);
            pGVar5 = local_14;
            if (iVar6 == 0) {
              if (local_14 != local_2c) {
                pGVar8 = GameObjectHandle::GetObj(local_14->who_i_shot);
                if (pGVar8 != (GameObject *)0x0) {
                  local_14 = (GameObject *)pGVar5->when_i_shot;
                  fVar9 = Get_Time();
                  if (fVar9 - (float)local_14 <= 10.0) {
                    iVar6 = (**(code **)(pGVar8->_padding_ + 4))();
                    bVar3 = GameObject::FriendP(param_1,iVar6);
                    if (bVar3) goto LAB_00406548;
                  }
                }
                if (((4900.0 < fVar2) ||
                    (p_Var7 = param_1->obj,
                    (p_Var7->transform).front_x * local_38 +
                    (p_Var7->transform).front_y * local_34 + (p_Var7->transform).front_z * local_30
                    < 0.0)) || ((*(byte *)((int)local_18->class_ptr + 0x10c) & 0x80) == 0))
                goto LAB_0040655e;
              }
LAB_00406548:
              if (fVar2 < local_c) {
                local_24 = pGVar5;
                local_c = fVar2;
              }
            }
            else if (local_14->aiProcess == (AiProcess *)0x0) {
              if (fVar2 < local_10) {
                local_28 = local_14;
                local_10 = fVar2;
              }
            }
            else if (fVar2 < local_8) {
              local_20 = local_14;
              local_8 = fVar2;
            }
          }
        }
      }
LAB_0040655e:
      bVar3 = Range_Search_Results::Get_Next_Object(&local_7c,&local_1c);
    } while (bVar3);
    pGVar5 = local_20;
    fVar2 = local_8;
    if ((local_20 == (GameObject *)0x0) &&
       (pGVar5 = local_28, fVar2 = local_10, local_24 != (GameObject *)0x0)) {
      pGVar5 = local_24;
      fVar2 = local_c;
    }
  }
  *param_2 = fVar2;
  return pGVar5;
}
