/*
 * Entry: 004cb44f
 * Name: EditTerrain::ProcessBrushShape
 * Namespace: EditTerrain
 * Signature: int ProcessBrushShape(EditTerrain * this, tagIconMenu * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall EditTerrain::ProcessBrushShape(EditTerrain *this,tagIconMenu *param_1)

{
  tagPOINT tVar1;
  tagPOINT tVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  int extraout_EAX;
  int *piVar6;
  float fVar7;
  int local_4;
  
  lVar4 = DisplayInterface::mousePos.y;
  lVar3 = DisplayInterface::mousePos.x;
  if ((TerrainWireFrame == 0) ||
     (tVar1.y = DisplayInterface::mousePos.y, tVar1.x = DisplayInterface::mousePos.x,
     iVar5 = InsideRect(tVar1,&param_1->rect), iVar5 == 0)) {
LAB_004cb590:
    this->brushState = 0;
    return 0;
  }
  local_4 = -1;
  if (param_1->icons < 1) goto LAB_004cb590;
  piVar6 = &param_1->icon->cmd;
  param_1 = (tagIconMenu *)param_1->icons;
  do {
    tVar2.y = lVar4;
    tVar2.x = lVar3;
    iVar5 = InsideRect(tVar2,(tagRECT *)(piVar6 + 2));
    if (iVar5 != 0) {
      local_4 = *piVar6;
    }
    piVar6 = piVar6 + 9;
    param_1 = (tagIconMenu *)((int)&param_1[-1].down + 3);
  } while (param_1 != (tagIconMenu *)0x0);
  if ((((local_4 != 0xd) && (local_4 != 0x13)) && (local_4 != 0xe)) &&
     ((local_4 != 0xf && (local_4 != 0x14)))) goto LAB_004cb590;
  if (this->brushState == 0) {
    this->brushState = 1;
  }
  if (edit_controls.edit_lmouse == '\0') {
    if (edit_controls.edit_rmouse == '\0') {
      this->brushState = 1;
      goto LAB_004cb57d;
    }
  }
  else if (edit_controls.edit_rmouse != '\0') goto LAB_004cb57d;
  if (this->brushState == 1) {
    ProcessBrushShapeCmd(this,local_4);
    this->brushState = 2;
    Get_Time();
    _ftol2_sse();
    this->brushTime = extraout_EAX;
  }
  else if ((this->brushState == 2) && (fVar7 = Get_Time(), 1.0 < fVar7 - (float)this->brushTime)) {
    this->brushState = 3;
  }
  if (this->brushState == 3) {
    ProcessBrushShapeCmd(this,local_4);
  }
LAB_004cb57d:
  DrawBrushShape(this,local_4);
  this->currCursor = &arrowCursor;
  return 1;
}
