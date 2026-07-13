/*
 * Entry: 0051658b
 * Name: UpdateAOI
 * Namespace: Global
 * Signature: void UpdateAOI(tag_team * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateAOI(tag_team *param_1,bool param_2)

{
  void *pvVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *local_c;
  int local_8;
  
  piVar2 = AOI::GetValues(param_1->team_ID,param_2);
  if (piVar2 != (int *)0x0) {
    if (param_2) {
      piVar3 = AOI::GetForces(param_1->team_ID);
    }
    else {
      piVar3 = (int *)0x0;
    }
    local_8 = 0;
    iVar5 = grid_columns;
    local_c = piVar3;
    if (0 < grid_rows) {
      do {
        iVar4 = 0;
        if (0 < iVar5) {
          piVar6 = local_c;
          do {
            pvVar1 = (param_1->strategic_targets).grid[local_8][iVar4];
            iVar5 = *(int *)(((int)piVar2 - (int)piVar3) + (int)piVar6);
            if (param_2) {
              *(int *)((int)pvVar1 + 0x68) = *(int *)((int)pvVar1 + 0x68) + iVar5;
              *(int *)((int)pvVar1 + 0x6c) = *piVar6;
              *(int *)((int)pvVar1 + 0x70) = *piVar6;
            }
            else if (iVar5 != 0) {
              *(undefined4 *)((int)pvVar1 + 0x6c) = 0;
              *(undefined4 *)((int)pvVar1 + 100) = 0;
              *(undefined4 *)((int)pvVar1 + 0x70) = 0;
              *(undefined4 *)((int)pvVar1 + 0x60) = 0;
              *(undefined4 *)((int)pvVar1 + 0x50) = 0;
              *(undefined4 *)((int)pvVar1 + 0x54) = 0;
              *(undefined4 *)((int)pvVar1 + 0x48) = 0;
              *(undefined4 *)((int)pvVar1 + 0x68) = 0xc4653600;
            }
            iVar4 = iVar4 + 1;
            piVar6 = piVar6 + 1;
            iVar5 = grid_columns;
          } while (iVar4 < grid_columns);
        }
        local_8 = local_8 + 1;
        local_c = local_c + iVar5;
      } while (local_8 < grid_rows);
    }
  }
  return;
}
