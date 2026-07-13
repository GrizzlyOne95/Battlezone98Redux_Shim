/*
 * Entry: 004cabba
 * Name: EditTerrain::ProcessMenu
 * Namespace: EditTerrain
 * Signature: int ProcessMenu(EditTerrain * this, tagIconMenu * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall EditTerrain::ProcessMenu(EditTerrain *this,tagIconMenu *param_1)

{
  int *piVar1;
  tagPOINT tVar2;
  tagPOINT tVar3;
  tagIconMenu *ptVar4;
  int iVar5;
  int iVar6;
  tagRECT *ptVar7;
  bool bVar8;
  
  ptVar4 = param_1;
  tVar3.y = DisplayInterface::mousePos.y;
  tVar3.x = DisplayInterface::mousePos.x;
  iVar5 = InsideRect(tVar3,&param_1->rect);
  iVar6 = 0;
  if (iVar5 != 0) {
    if (edit_controls.edit_lmouse == '\0') {
      this->lastLButton = 0;
    }
    else {
      if ((this->lastLButton == 0) &&
         (piVar1 = &param_1->icons, param_1 = (tagIconMenu *)0x0, 0 < *piVar1)) {
        ptVar7 = &ptVar4->icon->rect;
        do {
          tVar2.y = DisplayInterface::mousePos.y;
          tVar2.x = DisplayInterface::mousePos.x;
          iVar6 = InsideRect(tVar2,ptVar7);
          if (iVar6 != 0) {
            ptVar4->down = (int)param_1;
            break;
          }
          param_1 = (tagIconMenu *)((int)&param_1->icon + 1);
          ptVar7 = (tagRECT *)&ptVar7[2].top;
        } while ((int)param_1 < ptVar4->icons);
      }
      this->lastLButton = 1;
    }
    bVar8 = edit_controls.edit_rmouse != '\0';
    this->currCursor = &arrowCursor;
    this->lastRButton = (uint)bVar8;
    iVar6 = 1;
  }
  return iVar6;
}
