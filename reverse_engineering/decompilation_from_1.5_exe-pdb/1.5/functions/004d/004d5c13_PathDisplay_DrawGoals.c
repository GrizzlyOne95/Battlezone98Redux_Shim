/*
 * Entry: 004d5c13
 * Name: PathDisplay::DrawGoals
 * Namespace: PathDisplay
 * Signature: void DrawGoals(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawGoals(PathDisplay *this)

{
  tag_team *ptVar1;
  int iVar2;
  void *pvVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (AI_map != (tag_strategy_map *)0x0) {
    iVar7 = this->buildTeam;
    if (iVar7 < 0) {
      iVar7 = 0;
    }
    ptVar1 = AI_map->team[iVar7];
    if (ptVar1 != (tag_team *)0x0) {
      iVar7 = (ptVar1->strategic_targets).grid_rows;
      iVar2 = (ptVar1->strategic_targets).grid_columns;
      local_c = 0;
      if (0 < iVar7) {
        do {
          local_8 = 0;
          if (0 < iVar2) {
            fVar4 = (float)local_c;
            do {
              pvVar3 = (ptVar1->strategic_targets).grid[local_c][local_8];
              fVar6 = (float)local_8 * 80.0 + (float)aiGridX0 * 10.0;
              fVar5 = (float)aiGridZ0 * 10.0 + fVar4 * 80.0;
              (**(code **)(this->_padding_ + 0x20))(fVar6,fVar5,&local_1c,&local_10);
              (**(code **)(this->_padding_ + 0x20))(fVar6 + 80.0,fVar5 + 80.0,&local_14,&local_18);
              iVar8 = *(int *)((int)pvVar3 + 4);
              if (iVar8 < 0) {
                iVar8 = 0;
              }
              else if (10 < iVar8) {
                iVar8 = 10;
              }
              iVar8 = this->goalColorMap[iVar8 + 2];
              if (-1 < iVar8) {
                Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_1c + 3,local_18 + 3,
                                   local_14 + -3,local_10 + -3,iVar8,SOLID_PIXELS);
                Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_1c + 2,local_18 + 2,
                                   local_14 + -2,local_10 + -2,iVar8,SOLID_PIXELS);
                Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_1c + 1,local_18 + 1,
                                   local_14 + -1,local_10 + -1,iVar8,SOLID_PIXELS);
              }
              Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_1c,local_18,local_14,local_10
                                 ,DisplayInterface::colorBlack,SOLID_PIXELS);
              local_8 = local_8 + 1;
            } while (local_8 < iVar2);
          }
          local_c = local_c + 1;
        } while (local_c < iVar7);
      }
    }
  }
  return;
}
