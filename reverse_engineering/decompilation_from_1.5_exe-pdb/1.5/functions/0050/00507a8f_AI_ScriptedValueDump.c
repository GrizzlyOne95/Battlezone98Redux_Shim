/*
 * Entry: 00507a8f
 * Name: AI_ScriptedValueDump
 * Namespace: Global
 * Signature: void AI_ScriptedValueDump(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AI_ScriptedValueDump(int param_1)

{
  char cVar1;
  tag_team *ptVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int local_107c;
  undefined4 local_1078;
  char local_1074 [120];
  undefined1 local_ffc [4072];
  char local_14 [12];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_ffc;
  tlog_gdm("\n");
  tlog_gdm("\n");
  local_1078 = 0;
  ptVar2 = AI_map->team[param_1];
  if (0 < (ptVar2->strategic_targets).grid_rows) {
    do {
      local_107c = 0;
      local_1074[0] = 0;
      if (0 < (ptVar2->strategic_targets).grid_columns) {
        do {
          sprintf(local_14," %4d",
                  *(undefined4 *)
                   ((int)(ptVar2->strategic_targets).grid[local_1078][local_107c] + 0x68));
          pcVar3 = local_14;
          do {
            cVar1 = *pcVar3;
            pcVar3 = pcVar3 + 1;
          } while (cVar1 != '\0');
          uVar4 = (int)pcVar3 - (int)local_14;
          pcVar3 = (char *)((int)&local_1078 + 3);
          do {
            pcVar6 = pcVar3 + 1;
            pcVar3 = pcVar3 + 1;
          } while (*pcVar6 != '\0');
          pcVar6 = local_14;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar3 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar3 = pcVar3 + 4;
          }
          local_107c = local_107c + 1;
          for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
            *pcVar3 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar3 = pcVar3 + 1;
          }
        } while (local_107c < (ptVar2->strategic_targets).grid_columns);
      }
      tlog_gdm("  %s\n");
      local_1078 = local_1078 + 1;
    } while (local_1078 < (ptVar2->strategic_targets).grid_rows);
  }
  return;
}
