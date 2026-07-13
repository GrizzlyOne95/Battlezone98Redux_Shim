/*
 * Entry: 004c3afe
 * Name: ControlPanel::Init
 * Namespace: ControlPanel
 * Signature: void Init(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::Init(ControlPanel *this)

{
  int iVar1;
  uint uVar2;
  long *plVar3;
  
  AdjustPositions();
  this->selectNum = 0;
  this->scanTimer = -1e+30;
  plVar3 = this->groupNum;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *plVar3 = 0;
    plVar3 = plVar3 + 1;
  }
  memset(this->groupList,0,0xe10);
  this->targetNum = 0;
  TITLE_TEXT.index = GetSpriteIndex(TITLE_TEXT.name);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&MODE_TEXT[0].name + uVar2));
    *(int *)((int)&MODE_TEXT[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0xc0);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&COMMAND_TEXT[0].name + uVar2));
    *(int *)((int)&COMMAND_TEXT[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0xd8);
  BUILD_LABEL.index = GetSpriteIndex(BUILD_LABEL.name);
  CANCEL_LABEL.index = GetSpriteIndex(CANCEL_LABEL.name);
  CMD_KEY.index = GetSpriteIndex(CMD_KEY.name);
  ALT_KEY.index = GetSpriteIndex(ALT_KEY.name);
  CANCEL_KEY.index = GetSpriteIndex(CANCEL_KEY.name);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&NUM_KEY[0].name + uVar2));
    *(int *)((int)&NUM_KEY[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0x50);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&MENU_ITEM[0].name + uVar2));
    *(int *)((int)&MENU_ITEM[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 0x10;
  } while (uVar2 < 0x90);
  return;
}
