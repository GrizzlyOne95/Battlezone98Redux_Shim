/*
 * Entry: 00509aa8
 * Name: AI_Team_Debug_Change_AIP_Param
 * Namespace: Global
 * Signature: void AI_Team_Debug_Change_AIP_Param(tag_team * param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AI_Team_Debug_Change_AIP_Param(tag_team *param_1,char *param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  bool bVar3;
  char *pcVar4;
  double dVar5;
  char local_d0 [96];
  undefined1 local_70 [104];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_70;
  tlog_ild("CHANGING %s %d");
  iVar1 = 7;
  bVar3 = true;
  pcVar4 = param_2;
  pcVar2 = "threat";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar3 = *pcVar4 == *pcVar2;
    pcVar4 = pcVar4 + 1;
    pcVar2 = pcVar2 + 1;
  } while (bVar3);
  if (bVar3) {
    sprintf(local_d0,"Old Threat:              %d");
    DebCons_PutString(local_d0);
    param_1->AIP->threat_priority = param_3;
    iVar1 = param_1->AIP->threat_priority;
    pcVar4 = "New Threat:              %d";
  }
  else {
    iVar1 = 9;
    bVar3 = true;
    pcVar4 = param_2;
    pcVar2 = "distance";
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar3 = *pcVar4 == *pcVar2;
      pcVar4 = pcVar4 + 1;
      pcVar2 = pcVar2 + 1;
    } while (bVar3);
    if (bVar3) {
      sprintf(local_d0,"Old Distance:            %d");
      DebCons_PutString(local_d0);
      param_1->AIP->distance_priority = param_3;
      iVar1 = param_1->AIP->distance_priority;
      pcVar4 = "New Distance:            %d";
    }
    else {
      iVar1 = 7;
      bVar3 = true;
      pcVar4 = param_2;
      pcVar2 = "defend";
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar3 = *pcVar4 == *pcVar2;
        pcVar4 = pcVar4 + 1;
        pcVar2 = pcVar2 + 1;
      } while (bVar3);
      if (bVar3) {
        sprintf(local_d0,"Old Defend Base:         %d");
        DebCons_PutString(local_d0);
        param_1->AIP->defend_buildings_priority = param_3;
        iVar1 = param_1->AIP->defend_buildings_priority;
        pcVar4 = "New Defend Base:         %d";
      }
      else {
        iVar1 = 7;
        bVar3 = true;
        pcVar4 = param_2;
        pcVar2 = "attack";
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar3 = *pcVar4 == *pcVar2;
          pcVar4 = pcVar4 + 1;
          pcVar2 = pcVar2 + 1;
        } while (bVar3);
        if (bVar3) {
          sprintf(local_d0,"Old Attack Enemy Base:   %d");
          DebCons_PutString(local_d0);
          param_1->AIP->attack_enemy_base_priority = param_3;
          iVar1 = param_1->AIP->attack_enemy_base_priority;
          pcVar4 = "New Attack Enemy Base:   %d";
        }
        else {
          iVar1 = 8;
          bVar3 = true;
          pcVar4 = param_2;
          pcVar2 = "persist";
          do {
            if (iVar1 == 0) break;
            iVar1 = iVar1 + -1;
            bVar3 = *pcVar4 == *pcVar2;
            pcVar4 = pcVar4 + 1;
            pcVar2 = pcVar2 + 1;
          } while (bVar3);
          if (bVar3) {
            sprintf(local_d0,"Old Persistence:         %d");
            DebCons_PutString(local_d0);
            param_1->AIP->persistence_priority = param_3;
            iVar1 = param_1->AIP->persistence_priority;
            pcVar4 = "New Persistence:         %d";
          }
          else {
            iVar1 = 8;
            bVar3 = true;
            pcVar4 = param_2;
            pcVar2 = "explore";
            do {
              if (iVar1 == 0) break;
              iVar1 = iVar1 + -1;
              bVar3 = *pcVar4 == *pcVar2;
              pcVar4 = pcVar4 + 1;
              pcVar2 = pcVar2 + 1;
            } while (bVar3);
            if (bVar3) {
              sprintf(local_d0,"Old Exploration:         %d");
              DebCons_PutString(local_d0);
              param_1->AIP->exploration_priority = param_3;
              iVar1 = param_1->AIP->exploration_priority;
              pcVar4 = "New Exploration:         %d";
            }
            else {
              iVar1 = 9;
              bVar3 = true;
              pcVar4 = param_2;
              pcVar2 = "scripted";
              do {
                if (iVar1 == 0) break;
                iVar1 = iVar1 + -1;
                bVar3 = *pcVar4 == *pcVar2;
                pcVar4 = pcVar4 + 1;
                pcVar2 = pcVar2 + 1;
              } while (bVar3);
              if (!bVar3) {
                iVar1 = 10;
                bVar3 = true;
                pcVar4 = param_2;
                pcVar2 = "min_match";
                do {
                  if (iVar1 == 0) break;
                  iVar1 = iVar1 + -1;
                  bVar3 = *pcVar4 == *pcVar2;
                  pcVar4 = pcVar4 + 1;
                  pcVar2 = pcVar2 + 1;
                } while (bVar3);
                if (bVar3) {
                  sprintf(local_d0,"Old Min Match:           %lf",
                          param_1->AIP->min_matching_force_ratio);
                  DebCons_PutString(local_d0);
                  param_1->AIP->min_matching_force_ratio = (double)((float)param_3 * 0.1);
                  dVar5 = param_1->AIP->min_matching_force_ratio;
                  pcVar4 = "New Min Match:           %lf";
                }
                else {
                  iVar1 = 10;
                  bVar3 = true;
                  pcVar4 = param_2;
                  pcVar2 = "max_match";
                  do {
                    if (iVar1 == 0) break;
                    iVar1 = iVar1 + -1;
                    bVar3 = *pcVar4 == *pcVar2;
                    pcVar4 = pcVar4 + 1;
                    pcVar2 = pcVar2 + 1;
                  } while (bVar3);
                  if (!bVar3) {
                    iVar1 = 0xb;
                    bVar3 = true;
                    pcVar4 = param_2;
                    pcVar2 = "min_defend";
                    do {
                      if (iVar1 == 0) break;
                      iVar1 = iVar1 + -1;
                      bVar3 = *pcVar4 == *pcVar2;
                      pcVar4 = pcVar4 + 1;
                      pcVar2 = pcVar2 + 1;
                    } while (bVar3);
                    if (bVar3) {
                      sprintf(local_d0,"Old Min Defend:          %d");
                      DebCons_PutString(local_d0);
                      param_1->AIP->min_building_defense_force = param_3;
                      iVar1 = param_1->AIP->min_building_defense_force;
                      pcVar4 = "New Min Defend:          %d";
                    }
                    else {
                      iVar1 = 0xb;
                      bVar3 = true;
                      pcVar4 = param_2;
                      pcVar2 = "max_defend";
                      do {
                        if (iVar1 == 0) break;
                        iVar1 = iVar1 + -1;
                        bVar3 = *pcVar4 == *pcVar2;
                        pcVar4 = pcVar4 + 1;
                        pcVar2 = pcVar2 + 1;
                      } while (bVar3);
                      if (bVar3) {
                        sprintf(local_d0,"Max Defend:          %d");
                        DebCons_PutString(local_d0);
                        param_1->AIP->max_building_defense_force = param_3;
                        iVar1 = param_1->AIP->max_building_defense_force;
                        pcVar4 = "Max Defend:          %d";
                      }
                      else {
                        iVar1 = 7;
                        bVar3 = true;
                        pcVar4 = param_2;
                        pcVar2 = "cycles";
                        do {
                          if (iVar1 == 0) break;
                          iVar1 = iVar1 + -1;
                          bVar3 = *pcVar4 == *pcVar2;
                          pcVar4 = pcVar4 + 1;
                          pcVar2 = pcVar2 + 1;
                        } while (bVar3);
                        if (bVar3) {
                          sprintf(local_d0,"Old Relax Cycles:        %d");
                          DebCons_PutString(local_d0);
                          param_1->AIP->relaxation_cycles = param_3;
                          iVar1 = param_1->AIP->relaxation_cycles;
                          pcVar4 = "New Relax Cycles:        %d";
                        }
                        else {
                          iVar1 = 6;
                          bVar3 = true;
                          pcVar4 = param_2;
                          pcVar2 = "coeff";
                          do {
                            if (iVar1 == 0) break;
                            iVar1 = iVar1 + -1;
                            bVar3 = *pcVar4 == *pcVar2;
                            pcVar4 = pcVar4 + 1;
                            pcVar2 = pcVar2 + 1;
                          } while (bVar3);
                          if (bVar3) {
                            sprintf(local_d0,"Old Relax Coefficient:   %f",
                                    (double)param_1->AIP->relaxation_coefficient);
                            DebCons_PutString(local_d0);
                            param_1->AIP->relaxation_coefficient = (float)param_3 * 0.1;
                            dVar5 = (double)param_1->AIP->relaxation_coefficient;
                            pcVar4 = "New Relax Coefficient:   %f";
                            goto LAB_00509ebb;
                          }
                          iVar1 = 7;
                          bVar3 = true;
                          pcVar4 = "period";
                          do {
                            if (iVar1 == 0) break;
                            iVar1 = iVar1 + -1;
                            bVar3 = *param_2 == *pcVar4;
                            param_2 = param_2 + 1;
                            pcVar4 = pcVar4 + 1;
                          } while (bVar3);
                          if (!bVar3) {
                            return;
                          }
                          sprintf(local_d0,"Old Recompute Period:   %d cycles");
                          DebCons_PutString(local_d0);
                          param_1->AIP->recompute_strategy_period = param_3;
                          iVar1 = param_1->AIP->recompute_strategy_period;
                          pcVar4 = "New Recompute Period:   %d cycles";
                        }
                      }
                    }
                    goto LAB_00509f1c;
                  }
                  sprintf(local_d0,"Old Max Match:           %lf",
                          param_1->AIP->max_matching_force_ratio);
                  DebCons_PutString(local_d0);
                  param_1->AIP->max_matching_force_ratio = (double)((float)param_3 * 0.1);
                  dVar5 = param_1->AIP->max_matching_force_ratio;
                  pcVar4 = "New Max Match:           %lf";
                }
LAB_00509ebb:
                sprintf(local_d0,pcVar4,dVar5);
                DebCons_PutString(local_d0);
                return;
              }
              sprintf(local_d0,"Old Scripted:            %d");
              DebCons_PutString(local_d0);
              param_1->AIP->scripted_priority = param_3;
              iVar1 = param_1->AIP->scripted_priority;
              pcVar4 = "New Scripted:            %d";
            }
          }
        }
      }
    }
  }
LAB_00509f1c:
  sprintf(local_d0,pcVar4,iVar1);
  DebCons_PutString(local_d0);
  return;
}
