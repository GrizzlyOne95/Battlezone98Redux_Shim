/*
 * Entry: 0051b547
 * Name: Scheduler::Fill_Last_Priorities
 * Namespace: Scheduler
 * Signature: void Fill_Last_Priorities(Scheduler * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scheduler::Fill_Last_Priorities(Scheduler *this)

{
  float fVar1;
  void *pvVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  
  fVar3 = 1e+09;
  fVar4 = -1e+09;
  iVar6 = 0;
  if (0 < this->the_map->AI_map_rows) {
    do {
      iVar5 = 0;
      if (0 < this->the_map->AI_map_columns) {
        do {
          pvVar2 = (this->the_team->strategic_targets).grid[iVar6][iVar5];
          fVar1 = *(float *)((int)pvVar2 + 0x20);
          *(float *)((int)pvVar2 + 0x24) = fVar1;
          if (-5e+08 < fVar1) {
            if (fVar1 < fVar3) {
              fVar3 = fVar1;
            }
            if (fVar4 < fVar1) {
              fVar4 = fVar1;
            }
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < this->the_map->AI_map_columns);
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < this->the_map->AI_map_rows);
  }
  this->max_last_priority = (double)fVar4;
  this->min_last_priority = (double)fVar3;
  return;
}
