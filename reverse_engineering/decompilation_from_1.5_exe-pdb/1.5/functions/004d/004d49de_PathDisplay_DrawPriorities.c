/*
 * Entry: 004d49de
 * Name: PathDisplay::DrawPriorities
 * Namespace: PathDisplay
 * Signature: void DrawPriorities(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::DrawPriorities(PathDisplay *this)

{
  tag_team *ptVar1;
  float fVar2;
  int extraout_EAX;
  int iVar3;
  long local_ac;
  float local_a8;
  long local_a4;
  float local_a0;
  int local_9c;
  long local_98;
  long local_94;
  int local_90;
  int local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  if (AI_map != (tag_strategy_map *)0x0) {
    iVar3 = this->buildTeam;
    if (iVar3 < 0) {
      iVar3 = 2;
    }
    ptVar1 = AI_map->team[iVar3];
    if (ptVar1 != (tag_team *)0x0) {
      iVar3 = (ptVar1->strategic_targets).grid_rows;
      local_9c = (ptVar1->strategic_targets).grid_columns;
      local_8c = 0;
      if (0 < iVar3) {
        do {
          local_90 = 0;
          if (0 < local_9c) {
            fVar2 = (float)local_8c;
            do {
              local_a8 = (float)local_90 * 80.0 + (float)aiGridX0 * 10.0;
              local_a0 = (float)aiGridZ0 * 10.0 + fVar2 * 80.0;
              (**(code **)(this->_padding_ + 0x20))(local_a8,local_a0,&local_98,&local_ac);
              (**(code **)(this->_padding_ + 0x20))
                        (local_a8 + 80.0,local_a0 + 80.0,&local_94,&local_a4);
              _ftol2_sse();
              if (-100000 < extraout_EAX) {
                sprintf(local_88," %ld",extraout_EAX);
                Graphic_Rect_Empty(DisplayInterface::currentBuffer,local_98,local_a4,local_94,
                                   local_ac,DisplayInterface::colorBlack,SOLID_PIXELS);
                Graphic_Text(DisplayInterface::currentBuffer,local_98,local_a4,&local_94,&local_ac,
                             local_88,DisplayInterface::textFont,DisplayInterface::colorWhite,
                             DisplayInterface::colorDkGrey,0,0,0);
              }
              local_90 = local_90 + 1;
            } while (local_90 < local_9c);
          }
          local_8c = local_8c + 1;
        } while (local_8c < iVar3);
      }
    }
  }
  return;
}
