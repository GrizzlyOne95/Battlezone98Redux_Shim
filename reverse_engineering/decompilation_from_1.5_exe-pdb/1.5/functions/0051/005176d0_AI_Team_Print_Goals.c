/*
 * Entry: 005176d0
 * Name: AI_Team_Print_Goals
 * Namespace: Global
 * Signature: void AI_Team_Print_Goals(tag_team * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl AI_Team_Print_Goals(tag_team *param_1)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  int local_d4;
  char local_d0 [88];
  undefined1 local_78 [112];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  if (((uint)log_mode >> 0xe & 1) != 0) {
    local_d4 = 0;
    if (0 < (param_1->strategic_targets).grid_rows) {
      do {
        iVar3 = 0;
        if (0 < (param_1->strategic_targets).grid_columns) {
          do {
            pvVar1 = (param_1->strategic_targets).grid[local_d4][iVar3];
            if (*(int *)((int)pvVar1 + 4) != 0) {
              sprintf(local_d0,"%d %d %c %f min %d max %d",iVar3,local_d4,
                      (int)goalstr[*(int *)((int)pvVar1 + 4)],(double)*(float *)((int)pvVar1 + 0x1c)
                      ,*(undefined4 *)((int)pvVar1 + 0x10),*(undefined4 *)((int)pvVar1 + 0xc));
            }
            iVar3 = iVar3 + 1;
          } while (iVar3 < (param_1->strategic_targets).grid_columns);
        }
        local_d4 = local_d4 + 1;
      } while (local_d4 < (param_1->strategic_targets).grid_rows);
    }
    if (userUnit != (tagUNIT *)0x0) {
      iVar3 = (userUnit->tilepos).y;
      iVar2 = (userUnit->tilepos).x;
      sprintf(local_d0,"user at: %d %d",(int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3,
              (int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
    }
  }
  return;
}
