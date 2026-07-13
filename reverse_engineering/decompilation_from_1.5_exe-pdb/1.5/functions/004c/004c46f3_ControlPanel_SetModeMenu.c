/*
 * Entry: 004c46f3
 * Name: ControlPanel::SetModeMenu
 * Namespace: ControlPanel
 * Signature: void SetModeMenu(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SetModeMenu(ControlPanel *this)

{
  uint uVar1;
  long *plVar2;
  ModeButton_u_0 MVar3;
  long lVar4;
  ModeButton_u_0 *pMVar5;
  bool bVar6;
  
  uVar1 = 1;
  pMVar5 = (ModeButton_u_0 *)(this->currentModes).modeList;
  plVar2 = &this->modeButton[0].color;
  bVar6 = false;
  do {
    pMVar5 = pMVar5 + 1;
    if (uVar1 < 10 || bVar6) {
      MVar3 = *pMVar5;
    }
    else {
      MVar3.type = 0;
    }
    ((ModeButton *)(plVar2 + -1))->field0_0x0 = MVar3;
    if (((this->currentModes).enabledMask & 1 << ((byte)uVar1 & 0x1f)) == 0) {
      lVar4 = DisplayInterface::colorWhite;
      if (uVar1 != (this->currentModes).activeSlot) {
        lVar4 = DisplayInterface::colorGrey;
      }
    }
    else {
      lVar4 = DisplayInterface::colorGreen;
      if (uVar1 == (this->currentModes).activeSlot) {
        lVar4 = DisplayInterface::colorYellow;
      }
    }
    *plVar2 = lVar4;
    uVar1 = uVar1 + 1;
    plVar2 = plVar2 + 6;
    bVar6 = uVar1 == 10;
  } while ((int)uVar1 < 0xb);
  return;
}
