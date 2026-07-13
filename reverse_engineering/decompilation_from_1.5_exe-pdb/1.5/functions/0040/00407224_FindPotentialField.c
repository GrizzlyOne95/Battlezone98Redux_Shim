/*
 * Entry: 00407224
 * Name: FindPotentialField
 * Namespace: Global
 * Signature: void FindPotentialField(GameObject * param_1, GameObject * param_2, float param_3, VECTOR_3D param_4, VECTOR_3D * param_5, bool param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
FindPotentialField(GameObject *param_1,GameObject *param_2,float param_3,VECTOR_3D param_4,
                  VECTOR_3D *param_5,bool param_6)

{
  int *piVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  bool bVar7;
  float *pfVar8;
  GameObject *pGVar9;
  GameObject *pGVar10;
  int iVar11;
  _OBJ76 *p_Var12;
  VECTOR_3D *pVVar13;
  VECTOR_3D *pVVar14;
  int *piVar15;
  int unaff_EDI;
  long lVar16;
  Range_Search_Results local_12c;
  VECTOR_3D local_100;
  VECTOR_3D local_f4;
  VECTOR_3D local_e8;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  int *local_58;
  float local_54;
  float local_50;
  float local_4c;
  VECTOR_3D *local_48;
  int local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  int *local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D local_1c;
  uint local_10;
  GameObject *local_c;
  bool local_5;
  
  pfVar8 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_64 = *pfVar8;
  local_60 = pfVar8[1];
  local_5c = pfVar8[2];
  local_44 = param_1->seqNo;
  local_28 = *pfVar8;
  local_24 = pfVar8[1];
  local_20 = pfVar8[2];
  local_3c = param_4.x - local_28;
  local_38 = param_4.y - local_24;
  local_10 = (uint)(COLLISION_REAL_COLLISIONS == 0);
  local_34 = param_4.z - local_20;
  Range::Search(collision_range_search,(double)local_64,(double)local_5c,(double)param_3,&local_12c)
  ;
LAB_0040776f:
  do {
    bVar7 = Range_Search_Results::Get_Next_Object(&local_12c,&local_30);
    if (!bVar7) {
      return;
    }
    pGVar9 = GameObjectHandle::GetObj(*local_30);
    local_c = pGVar9;
  } while ((((pGVar9 == (GameObject *)0x0) || (pGVar9 == param_1)) || (pGVar9 == param_2)) ||
          (((5.0 < (pGVar9->euler).v_mag &&
            (pGVar10 = Team::GetSlot(param_1->teamList,0), pGVar9 != pGVar10)) &&
           (local_44 < pGVar9->seqNo))));
  iVar11 = (**(code **)param_1->_padding_)();
  if (*(int *)(iVar11 + 0x20) == 0x54554700) goto code_r0x00407319;
  goto LAB_00407364;
code_r0x00407319:
  pGVar10 = Tug::GetCargo((Tug *)param_1);
  if (pGVar9 == pGVar10) goto LAB_0040776f;
  piVar1 = &pGVar9->_padding_;
  iVar11 = (**(code **)*piVar1)();
  if (((*(int *)(iVar11 + 0x20) == 0x52435943) ||
      (iVar11 = (**(code **)*piVar1)(), *(int *)(iVar11 + 0x20) == 0x41524d52)) ||
     (iVar11 = (**(code **)*piVar1)(), *(int *)(iVar11 + 0x20) == 0x46414354)) goto LAB_0040776f;
LAB_00407364:
  iVar11 = (**(code **)param_1->_padding_)();
  if ((*(int *)(iVar11 + 0x20) == 0x52435943) &&
     (iVar11 = (**(code **)pGVar9->_padding_)(), *(int *)(iVar11 + 0x20) == 0x54554700))
  goto LAB_0040776f;
  piVar1 = &pGVar9->_padding_;
  iVar11 = (**(code **)*piVar1)();
  piVar15 = (int *)(iVar11 + 0x28);
  iVar11 = *piVar15;
  local_58 = piVar15;
  if ((iVar11 == 2) || (((iVar11 == 10 || (iVar11 == 7)) || (iVar11 == 3)))) goto LAB_0040776f;
  iVar11 = (**(code **)(*piVar1 + 4))();
  bVar7 = GameObject::EnemyP(param_1,iVar11);
  if (bVar7) {
    if (*piVar15 == 4) goto LAB_0040776f;
    bVar7 = *piVar15 == 1;
  }
  else {
    iVar11 = (**(code **)(*piVar1 + 4))();
    bVar7 = GameObject::FriendP(param_1,iVar11);
    if (!bVar7) goto LAB_0040740a;
    iVar11 = (**(code **)*piVar1)();
    bVar7 = *(int *)(iVar11 + 0x20) == 0x50524f58;
  }
  if (bVar7) goto LAB_0040776f;
LAB_0040740a:
  pfVar8 = (float *)(**(code **)(*piVar1 + 0xc))();
  pGVar9 = local_c;
  local_d0 = *pfVar8;
  local_cc = pfVar8[1];
  local_c8 = pfVar8[2];
  local_28 = local_64 - local_d0;
  local_24 = local_60 - local_cc;
  local_20 = local_5c - local_c8;
  local_2c = local_28 * local_28 + local_24 * local_24 + local_20 * local_20;
  if (local_2c < param_3 * param_3) {
    local_1c.x = 0.0;
    local_1c.y = 0.0;
    local_1c.z = 0.0;
    local_40 = local_c->collisionRadius + param_1->collisionRadius;
    if (COLLISION_REAL_COLLISIONS != 0) {
      local_10 = 1;
      p_Var12 = (_OBJ76 *)(**(code **)(*piVar1 + 0x30))();
      iVar11 = IsCraft(p_Var12);
      if ((iVar11 != 0) && (cVar6 = (**(code **)(pGVar9->_padding_ + 100))(), cVar6 != '\0')) {
        if (COLLISION_CHEAP_2D_COLLIDE == 0) {
          local_10 = AIUtil_Detect_2D_Collision(param_1,pGVar9,COLLISION_LOOK_AHEAD_TIME);
        }
        else {
          local_10 = AIUtil_Detect_2D_Collision_With_NonMoving_Object
                               (param_1,local_c,COLLISION_LOOK_AHEAD_TIME,param_4);
          pGVar9 = local_c;
        }
      }
    }
    if ((COLLISION_LATERAL_REPULSION != 0) && (local_10 != 0)) {
      local_54 = param_1->collisionRadius;
      local_4c = pGVar9->collisionRadius;
      local_50 = (param_1->euler).v_mag;
      local_48 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
      pVVar13 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
      VVar2.y = local_38;
      VVar2.x = local_3c;
      VVar2.z = local_34;
      Add_Lateral_Repulsion
                (*pVVar13,*local_48,VVar2,local_50,param_3,&local_1c,local_4c + local_54,unaff_EDI);
      pGVar9 = local_c;
      if (param_6) {
        pfVar8 = (float *)(**(code **)(*piVar1 + 0xc))();
        local_88 = *pfVar8;
        local_84 = pfVar8[1];
        local_80 = pfVar8[2];
        local_e8.x = local_88 + local_1c.x;
        pVVar13 = &local_e8;
        local_e8.y = local_84 + local_1c.y;
        local_e8.z = local_80 + local_1c.z;
        lVar16 = DisplayInterface::colorCyan;
        local_70 = local_e8.x;
        local_6c = local_e8.y;
        local_68 = local_e8.z;
        pVVar14 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
        WorldLine(pVVar14,pVVar13,lVar16);
        pGVar9 = local_c;
      }
    }
    if (((*local_58 == 6) || (*local_58 == 1)) &&
       (cVar6 = (**(code **)(pGVar9->_padding_ + 100))(), cVar6 != '\0')) {
      local_10 = 0;
    }
    if ((COLLISION_DIRECT_REPULSION != 0) && (local_10 != 0)) {
      fVar4 = SQRT(local_2c) - local_40;
      if (fVar4 < 0.1) {
        fVar4 = 0.1;
      }
      fVar5 = 1.0 / fVar4 - 1.0 / DISTANCE_OF_INFLUENCE;
      VVar3.y = local_24;
      VVar3.x = local_28;
      VVar3.z = local_20;
      pVVar13 = ScaleVector(&local_100,fVar5 * fVar5 * REPULSIVE_COEFFICIENT * (1.0 / fVar4),VVar3);
      local_a0 = pVVar13->x;
      local_9c = pVVar13->y;
      local_98 = pVVar13->z;
      local_c4 = local_a0 + local_1c.x;
      local_c0 = local_9c + local_1c.y;
      local_bc = local_98 + local_1c.z;
      pGVar9 = local_c;
      local_1c.x = local_c4;
      local_1c.y = local_c0;
      local_1c.z = local_bc;
      if (param_6) {
        local_b8 = pVVar13->x;
        local_b4 = pVVar13->y;
        local_b0 = pVVar13->z;
        pfVar8 = (float *)(**(code **)(*piVar1 + 0xc))();
        local_dc = *pfVar8;
        local_d8 = pfVar8[1];
        local_d4 = pfVar8[2];
        local_f4.x = local_b8 + local_dc;
        local_f4.y = local_b4 + local_d8;
        pVVar13 = &local_f4;
        local_f4.z = local_b0 + local_d4;
        lVar16 = DisplayInterface::colorYellow;
        local_7c = local_f4.x;
        local_78 = local_f4.y;
        local_74 = local_f4.z;
        pVVar14 = (VECTOR_3D *)(**(code **)(*piVar1 + 0xc))();
        WorldLine(pVVar14,pVVar13,lVar16);
        pGVar9 = local_c;
      }
    }
    local_5 = false;
    if (((1.0 <= (pGVar9->euler).v_mag) ||
        (0.0 <= local_3c * local_1c.x + local_38 * local_1c.y + local_34 * local_1c.z)) ||
       (Blocking(param_1,pGVar9,&local_5), local_5 == false)) {
      local_94 = param_5->x;
      local_90 = param_5->y;
      local_8c = param_5->z;
      local_ac = local_94 + local_1c.x;
      local_a8 = local_90 + local_1c.y;
      local_a4 = local_8c + local_1c.z;
      param_5->x = local_ac;
      param_5->y = local_a8;
      param_5->z = local_a4;
    }
  }
  goto LAB_0040776f;
}
