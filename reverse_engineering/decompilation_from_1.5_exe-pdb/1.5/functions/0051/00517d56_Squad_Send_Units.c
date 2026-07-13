/*
 * Entry: 00517d56
 * Name: Squad_Send_Units
 * Namespace: Global
 * Signature: void Squad_Send_Units(tag_strategy_map * param_1, tag_squad * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Squad_Send_Units(tag_strategy_map *param_1,tag_squad *param_2)

{
  int *piVar1;
  VECTOR_2D *pVVar2;
  float fVar3;
  float fVar4;
  tag_team *ptVar5;
  char cVar6;
  tagUNIT *ptVar7;
  GameObject *pGVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  AiPath *pAVar12;
  AOI *this;
  float *pfVar13;
  VECTOR_3D *pVVar14;
  byte bVar15;
  uint uVar16;
  Goal *pGVar17;
  char *pcVar18;
  uint uVar19;
  SquadUnitInfo *unaff_ESI;
  tag_c_linked_list *ptVar20;
  int unaff_EDI;
  AiCommand AVar21;
  char local_2ac [4];
  float local_2a8 [89];
  int local_144;
  char local_140 [236];
  VECTOR_3D local_54;
  VECTOR_3D local_48;
  float local_3c;
  float local_38;
  Goal *local_34;
  float local_30;
  float local_2c;
  Mapgrid_Goal *local_28;
  tag_c_linked_list *local_24;
  tag_team *local_20;
  uint local_1c;
  char local_15;
  VECTOR_3D local_14;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pGVar17 = param_2->my_strategic_goal;
  local_34 = pGVar17;
  if ((pGVar17 != (Goal *)0x0) && (iVar9 = (param_2->my_units).count, iVar9 != 0)) {
    local_1c = 0;
    local_20 = param_2->the_team;
    if (0 < iVar9) {
      do {
        ptVar7 = C_Linked_List_Return_Data_By_Number(&param_2->my_units,local_1c);
        pGVar8 = GameObjectHandle::GetObj(ptVar7->handle);
        if (((pGVar8 == (GameObject *)0x0) || (pGVar8->aiProcess == (AiProcess *)0x0)) ||
           (iVar9 = (**(code **)(pGVar8->_padding_ + 4))(), iVar9 != local_20->team_ID)) {
          Squad_Remove_Unit(param_2,ptVar7,local_20);
        }
        local_1c = local_1c + 1;
      } while ((int)local_1c < (param_2->my_units).count);
    }
    local_28 = (Mapgrid_Goal *)(param_2->my_units).count;
    if (local_28 != (Mapgrid_Goal *)0x0) {
      if (0x1e < (int)local_28) {
        Trace("Squad Send: unitCount(%d)\n");
        local_28 = (Mapgrid_Goal *)0x1e;
      }
      iVar9 = 0;
      if (0 < (int)local_28) {
        local_24 = &param_2->my_units;
        do {
          piVar10 = C_Linked_List_Return_Data_By_Number(local_24,iVar9);
          pGVar17 = local_34;
          iVar11 = piVar10[6];
          piVar1 = (int *)*piVar10;
          *(int **)(local_140 + iVar9 * 8 + -4) = piVar1;
          local_140[iVar9 * 8] = '\x01';
          if ((((int)(iVar11 + (iVar11 >> 0x1f & 7U)) >> 3 == pGVar17[1].the_troop_flow.strength) &&
              ((int)(piVar10[5] + (piVar10[5] >> 0x1f & 7U)) >> 3 ==
               local_34[1].the_troop_flow.max_strength)) &&
             ((iVar11 = (**(code **)piVar1[8])(), *(int *)(iVar11 + 0x20) != 0x54544e4b ||
              (cVar6 = (**(code **)(*piVar1 + 100))(), cVar6 != '\0')))) {
            local_140[iVar9 * 8] = '\0';
          }
          iVar9 = iVar9 + 1;
          pGVar17 = local_34;
        } while (iVar9 < (int)local_28);
      }
      if ((pGVar17->what_goal == ATTACK_TROOPS) || (pGVar17->what_goal == SEIGE)) {
        Squad_Send_Attack(local_28,unaff_ESI,unaff_EDI);
      }
      iVar9 = pGVar17[1].the_troop_flow.max_strength;
      iVar11 = pGVar17[1].the_troop_flow.strength;
      local_30 = (float)(aiGridX0 + iVar9 * 8) * 10.0;
      ptVar20 = (tag_c_linked_list *)sendPoints[iVar11 * grid_columns + iVar9];
      local_24 = ptVar20;
      local_2c = (float)(aiGridZ0 + iVar11 * 8) * 10.0;
      if (ptVar20 == (tag_c_linked_list *)0xffffffff) {
        Trace("gridLayout == -1\n");
      }
      if (ptVar20 == (tag_c_linked_list *)0x0) {
        sprintf((char *)&local_14,"bad_%d_%d",pGVar17[1].the_troop_flow.max_strength,
                pGVar17[1].the_troop_flow.strength);
        pAVar12 = operator_new(0x1c);
        if (pAVar12 == (AiPath *)0x0) {
          pAVar12 = (AiPath *)0x0;
        }
        else {
          pAVar12 = AiPath::AiPath(pAVar12,(char *)&local_14,2);
        }
        pVVar2 = pAVar12->points;
        pVVar2->x = local_30 + 2.0;
        pVVar2->z = local_2c + 2.0;
        pAVar12->points[1].x = local_30 + 6.0;
        pAVar12->points[1].z = local_2c + 6.0;
        this = operator_new(0x18);
        if (this != (AOI *)0x0) {
          AOI::AOI(this,pAVar12,local_20->team_ID,false,true,-1,0);
        }
      }
      else {
        uVar16 = 0;
        do {
          if (((uint)ptVar20 & 1 << ((byte)uVar16 & 0x1f)) != 0) break;
          uVar16 = uVar16 + 1;
        } while (uVar16 < 5);
        if (uVar16 != 5) {
          local_1c = 0;
          pcVar18 = local_2ac + 1;
          local_38 = layout[uVar16].rx * 8.0 + local_30;
          local_3c = layout[uVar16].rz * 8.0 + local_2c;
          do {
            uVar16 = local_1c;
            bVar15 = (byte)local_1c;
            fVar4 = layout[local_1c].rx * 8.0 + local_30;
            *(float *)(pcVar18 + 3) = fVar4;
            fVar3 = layout[uVar16].rz * 8.0 + local_2c;
            *(float *)(pcVar18 + 7) = fVar3;
            if (((uint)ptVar20 & 1 << (bVar15 & 0x1f)) == 0) {
              pcVar18[-1] = '\x01';
            }
            else {
              local_14.x = fVar4;
              pcVar18[-1] = '\0';
              *pcVar18 = '\0';
              local_14.z = fVar3;
              local_20 = (tag_team *)0x0;
              local_38 = local_14.x;
              local_3c = fVar3;
              do {
                if ((int)local_28 <= (int)local_20) break;
                iVar9 = *(int *)(local_140 + (int)local_20 * 8 + -4);
                iVar11 = (*(code *)**(undefined4 **)(iVar9 + 0x20))();
                if (*(int *)(iVar11 + 0x20) == 0x54544e4b) {
                  pfVar13 = (float *)(**(code **)(*(int *)(iVar9 + 0x20) + 0xc))();
                  ptVar5 = local_20;
                  ptVar20 = local_24;
                  local_48.x = *pfVar13;
                  local_48.y = pfVar13[1];
                  local_48.z = pfVar13[2];
                  fVar3 = *pfVar13 - local_14.x;
                  fVar4 = pfVar13[2] - local_14.z;
                  fVar3 = fVar4 * fVar4 + fVar3 * fVar3;
                  if (fVar3 < 625.0 != (fVar3 == 625.0)) {
                    *pcVar18 = '\x01';
                    local_140[(int)ptVar5 * 8] = '\0';
                  }
                }
                local_20 = (tag_team *)((int)&local_20->team_ID + 1);
              } while (*pcVar18 == '\0');
            }
            local_1c = local_1c + 1;
            pcVar18 = pcVar18 + 0xc;
          } while (local_1c < 5);
          uVar16 = 0;
          pcVar18 = local_2ac + 1;
          do {
            if ((pcVar18[-1] == '\0') && (uVar19 = uVar16, *pcVar18 == '\0')) break;
            uVar16 = uVar16 + 1;
            pcVar18 = pcVar18 + 0xc;
            uVar19 = 0;
          } while (uVar16 < 5);
          local_15 = '\x01';
          local_1c = 0;
          if (0 < (int)local_28) {
            do {
              if (local_140[local_1c * 8] != '\0') {
                pGVar8 = *(GameObject **)(local_140 + local_1c * 8 + -4);
                piVar1 = &pGVar8->_padding_;
                iVar9 = (**(code **)*piVar1)();
                uVar16 = uVar19;
                if (*(int *)(iVar9 + 0x20) == 0x54544e4b) {
                  while ((local_2ac[uVar16 * 0xc] != '\0' ||
                         ((local_2ac[uVar16 * 0xc + 1] != '\0' && (local_15 != '\0'))))) {
                    uVar16 = uVar16 + 1;
                    if (4 < uVar16) {
                      uVar16 = 0;
                      local_15 = '\0';
                    }
                  }
                  uVar19 = uVar16 + 1;
                  local_2ac[uVar16 * 0xc + 1] = '\x01';
                  local_48.x = local_2a8[uVar16 * 3];
                  local_48.y = 0.0;
                  local_48.z = local_2a8[uVar16 * 3 + 1];
                  if (4 < uVar19) {
                    uVar19 = 0;
                    local_15 = '\0';
                  }
                  pVVar14 = &local_48;
LAB_005181e8:
                  AVar21 = CMD_GO;
                }
                else {
                  if ((local_34->what_goal != PERIMETER) &&
                     ((local_34->what_goal != DEFEND_BASE ||
                      ((iVar9 = (**(code **)*piVar1)(), *(int *)(iVar9 + 0x20) != 0x57494e47 &&
                       (iVar9 = (**(code **)*piVar1)(), *(int *)(iVar9 + 0x20) != 0x4d4c5952)))))) {
                    pVVar14 = &local_14;
                    local_14.x = local_38;
                    local_14.y = 0.0;
                    local_14.z = local_3c;
                    goto LAB_005181e8;
                  }
                  local_54.x = local_38;
                  pVVar14 = &local_54;
                  local_54.y = 0.0;
                  AVar21 = CMD_PATROL;
                  local_54.z = local_3c;
                }
                GameObject::SetCommand(pGVar8,AVar21,pVVar14,0);
              }
              local_1c = local_1c + 1;
            } while ((int)local_1c < (int)local_28);
          }
        }
      }
    }
  }
  return;
}
