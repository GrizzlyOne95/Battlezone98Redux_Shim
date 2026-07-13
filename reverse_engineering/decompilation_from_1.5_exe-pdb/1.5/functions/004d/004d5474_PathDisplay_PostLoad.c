/*
 * Entry: 004d5474
 * Name: PathDisplay::PostLoad
 * Namespace: PathDisplay
 * Signature: void PostLoad(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::PostLoad(PathDisplay *this)

{
  int iVar1;
  long extraout_EAX;
  long lVar2;
  int *piVar3;
  
  this->worldX0 = (float)(grid_rect.right + grid_rect.left) * 0.5;
  this->worldZ0 = (float)(grid_rect.bottom + grid_rect.top) * 0.5;
  this->worldDx = (float)(grid_rect.right - grid_rect.left);
  iVar1 = grid_rect.bottom - grid_rect.top;
  this->colorMode = 1;
  this->menuMode = MENU_NONE;
  this->controlMode = CONTROL_PLAN;
  this->worldDz = (float)iVar1;
  InitControlPlan(this);
  this->nextControlMode = ~CONTROL_PLAN;
  (this->editRect).left = extraout_EAX;
  iVar1 = 0xe;
  piVar3 = this->cellColorMap + 2;
  do {
    *piVar3 = DisplayInterface::colorDkGrey;
    piVar3 = piVar3 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this->cellColorMap[2] = DisplayInterface::colorDkCyan;
  this->cellColorMap[3] = DisplayInterface::colorGrey;
  lVar2 = Get_Closest_RGB_Entry(0.8,0.8,0.6);
  this->cellColorMap[4] = lVar2;
  this->cellColorMap[5] = DisplayInterface::colorRed;
  this->cellColorMap[6] = DisplayInterface::colorCyan;
  this->cellColorMap[7] = DisplayInterface::colorWhite;
  this->cellColorMap[8] = DisplayInterface::colorYellow;
  this->cellColorMap[10] = DisplayInterface::colorDkGreen;
  lVar2 = Get_Closest_RGB_Entry(0.4,0.8,0.4);
  this->cellColorMap[0xb] = lVar2;
  this->cellColorMap[0xc] = DisplayInterface::colorDkRed;
  lVar2 = Get_Closest_RGB_Entry(0.8,0.4,0.4);
  this->cellColorMap[0xd] = lVar2;
  this->goalColorMap[0] = DisplayInterface::colorDkYellow;
  lVar2 = Get_Closest_RGB_Entry(0.7,0.7,0.4);
  this->goalColorMap[2] = -1;
  this->goalColorMap[1] = lVar2;
  this->goalColorMap[3] = DisplayInterface::colorGreen;
  this->goalColorMap[4] = DisplayInterface::colorDkRed;
  this->goalColorMap[5] = DisplayInterface::colorRed;
  this->goalColorMap[6] = DisplayInterface::colorBlue;
  this->goalColorMap[7] = DisplayInterface::colorWhite;
  this->goalColorMap[8] = DisplayInterface::colorDkGreen;
  this->goalColorMap[9] = DisplayInterface::colorCyan;
  this->goalColorMap[10] = DisplayInterface::colorWhite;
  this->numKeyIndex = DisplayInterface::colorBlack;
  this->cancelKeyIndex = DisplayInterface::colorDkGrey;
  iVar1 = GetSpriteIndex("key_0");
  this[1]._padding_ = iVar1;
  iVar1 = GetSpriteIndex("key_TAB");
  this[1]._padding_ = iVar1;
  return;
}
