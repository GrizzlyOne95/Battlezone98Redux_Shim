/*
 * Entry: 00509637
 * Name: AI_Team_Print_Debug_Map
 * Namespace: Global
 * Signature: void AI_Team_Print_Debug_Map(tag_team * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AI_Team_Print_Debug_Map(tag_team *param_1,char *param_2)

{
  double *pdVar1;
  char cVar2;
  char cVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  uint uVar8;
  code *pcVar9;
  char *pcVar10;
  char *pcVar11;
  int local_ec;
  int local_e8;
  undefined4 local_e0;
  char local_dc [104];
  undefined1 local_74 [96];
  char local_14 [12];
  uint local_8;
  
  pcVar9 = sprintf_exref;
  local_8 = __security_cookie ^ (uint)local_74;
  cVar2 = *param_2;
  sprintf(local_dc,"MAP for team %d",param_1->team_ID);
  DebCons_PutString(local_dc);
  local_ec = 0;
  if (0 < (param_1->strategic_targets).grid_rows) {
    do {
      local_e8 = 0;
      local_dc[0] = '\0';
      if (0 < (param_1->strategic_targets).grid_columns) {
        do {
          pvVar4 = (param_1->strategic_targets).grid[local_ec][local_e8];
          if (pvVar4 == (void *)0x0) {
            pcVar11 = "Invalid Cell: NULL Pointer";
            goto LAB_00509773;
          }
          if (cVar2 == 'b') {
            iVar6 = (param_1->strategic_targets).distance_from_base[local_ec][local_e8];
            if (9 < iVar6) {
              pcVar11 = "*";
              goto LAB_005098a5;
            }
LAB_00509707:
            pcVar11 = "%d";
LAB_0050970d:
            (*pcVar9)(local_14,pcVar11,iVar6);
          }
          else if (cVar2 == 'g') {
            iVar6 = *(int *)((int)pvVar4 + 4);
            if (iVar6 == 0) {
              pcVar11 = "_";
            }
            else if (iVar6 == 1) {
              pcVar11 = "D";
            }
            else if (iVar6 == 2) {
              pcVar11 = "A";
            }
            else if (iVar6 == 3) {
              pcVar11 = "S";
            }
            else if (iVar6 == 4) {
              pcVar11 = "E";
            }
            else if (iVar6 == 5) {
              pcVar11 = "M";
            }
            else if (iVar6 == 6) {
              pcVar11 = "P";
            }
            else {
              pcVar11 = "*";
            }
LAB_005098a5:
            (*pcVar9)(local_14,pcVar11);
          }
          else if (cVar2 == 'p') {
            _ftol2_sse();
            _ftol2_sse();
            local_e0 = extraout_EAX_00 - extraout_EAX;
            if (*(float *)((int)pvVar4 + 0x1c) < 0.0) {
              local_e0 = 0;
            }
            pdVar1 = &param_1->scheduler->max_priority;
            if (*pdVar1 < (double)local_e0) {
              _ftol2_sse();
              local_e0 = extraout_EAX_01;
            }
            if (*pdVar1 != 0.0) {
              local_e0 = local_e0 * 9;
              _ftol2_sse();
              local_e0 = extraout_EAX_02;
            }
            sprintf(local_14,"%d",local_e0);
          }
          else {
            if (cVar2 != 's') {
              if (cVar2 == 't') {
                iVar6 = *(int *)((int)pvVar4 + 0x48);
                if (iVar6 < 0) {
                  iVar6 = 0;
                }
                iVar5 = (param_1->strategic_targets).max_threat;
                if (iVar5 < iVar6) {
                  iVar6 = iVar5;
                }
                if (iVar5 != 0) {
                  iVar6 = (iVar6 * 9) / iVar5;
                }
                goto LAB_00509707;
              }
              pcVar11 = "*";
              iVar6 = local_e0;
              goto LAB_0050970d;
            }
            if (*(int *)((int)pvVar4 + 0x68) < 0) {
              local_14[0] = '-';
            }
            else {
              local_14[0] = ((*(int *)((int)pvVar4 + 0x68) < 1) - 1U & 0xee) + 0x3d;
            }
            local_14[1] = 0;
          }
          pcVar11 = local_14;
          do {
            cVar3 = *pcVar11;
            pcVar11 = pcVar11 + 1;
          } while (cVar3 != '\0');
          uVar7 = (int)pcVar11 - (int)local_14;
          pcVar11 = (char *)((int)&local_e0 + 3);
          do {
            pcVar10 = pcVar11 + 1;
            pcVar11 = pcVar11 + 1;
          } while (*pcVar10 != '\0');
          pcVar10 = local_14;
          for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
            pcVar10 = pcVar10 + 4;
            pcVar11 = pcVar11 + 4;
          }
          local_e8 = local_e8 + 1;
          iVar6 = (param_1->strategic_targets).grid_columns;
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *pcVar11 = *pcVar10;
            pcVar10 = pcVar10 + 1;
            pcVar11 = pcVar11 + 1;
          }
          pcVar9 = sprintf_exref;
        } while (local_e8 < iVar6);
      }
      DebCons_PutString(local_dc);
      local_ec = local_ec + 1;
    } while (local_ec < (param_1->strategic_targets).grid_rows);
  }
  pcVar11 = "";
LAB_00509773:
  DebCons_PutString(pcVar11);
  return;
}
