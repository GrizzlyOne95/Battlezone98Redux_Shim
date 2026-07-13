/*
 * Entry: 004c9961
 * Name: EditTerrain::ProcessShortcutKeys
 * Namespace: EditTerrain
 * Signature: void ProcessShortcutKeys(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::ProcessShortcutKeys(EditTerrain *this)

{
  int iVar1;
  tagIconMenu *ptVar2;
  int iVar3;
  tagIconMenu **pptVar4;
  int *piVar5;
  int local_8;
  
  local_8 = 0;
  pptVar4 = &shortcutList[0].menu;
  do {
    if (*((tagShortcutKey *)(pptVar4 + -1))->key != '\0') {
      iVar1 = (*pptVar4)->icons;
      iVar3 = 0;
      if (0 < iVar1) {
        piVar5 = &(*pptVar4)->icon->cmd;
        do {
          if (pptVar4[1] == (tagIconMenu *)*piVar5) {
            ptVar2 = shortcutList[local_8].menu;
            this->commandDown = iVar3;
            this->commandMenu = ptVar2;
            this->currCursor = ptVar2->icon + iVar3;
            return;
          }
          iVar3 = iVar3 + 1;
          piVar5 = piVar5 + 9;
        } while (iVar3 < iVar1);
      }
    }
    local_8 = local_8 + 1;
    pptVar4 = pptVar4 + 3;
  } while ((int)pptVar4 < 0x62a0f0);
  return;
}
