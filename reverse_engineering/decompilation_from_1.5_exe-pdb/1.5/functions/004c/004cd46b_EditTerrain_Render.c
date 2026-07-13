/*
 * Entry: 004cd46b
 * Name: EditTerrain::Render
 * Namespace: EditTerrain
 * Signature: void Render(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::Render(EditTerrain *this)

{
  tagIconMenu *ptVar1;
  tagIcon *ptVar2;
  tagPOINT tVar3;
  int iVar4;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar5;
  int iVar6;
  EditTerrain *this_00;
  int unaff_EDI;
  tagIconMenu *ptVar7;
  float fVar8;
  int iVar9;
  VECTOR_3D local_14;
  int local_8;
  
  if (TerrainEditMode != 0) {
    local_8 = Set_Rounding(unaff_EDI);
    if (((edit_controls.edit_undo != '\0') &&
        ((TerrainWireFrame != 0 ||
         ((this->undoCount != 0 && (PopUndoTile(this), TerrainWireFrame != 0)))))) &&
       (this->undoGCount != 0)) {
      PopUndoGrid(this);
    }
    ptVar7 = &tileMenu;
    if (edit_controls.edit_wireframe != '\0') {
      TerrainWireFrame = (int)(TerrainWireFrame == 0);
      if (TerrainWireFrame == 0) {
        this->lastMenu = &tileMenu;
      }
      else {
        this->lastMenu = &gridMenu;
      }
    }
    if (edit_controls.edit_wirecolor != '\0') {
      TerrainWireColor = (int)(TerrainWireColor == 0);
    }
    if (edit_controls.edit_maptype != '\0') {
      this->mapMaterials = (uint)(this->mapMaterials == 0);
      CreateWorldMap(this);
    }
    if (TerrainWireFrame != 0) {
      ptVar7 = &gridMenu;
    }
    ptVar1 = this->lastMenu;
    this->commandMenu = ptVar1;
    iVar4 = ptVar1->down;
    this->commandDown = iVar4;
    this->currCursor = ptVar1->icon + iVar4;
    tVar3.y = DisplayInterface::mousePos.y;
    tVar3.x = DisplayInterface::mousePos.x;
    MoveCamera(this,tVar3);
    iVar4 = ProcessWorldMap(this);
    if ((((iVar4 == 0) && (iVar4 = ProcessBrushShape(this,ptVar7), iVar4 == 0)) &&
        (iVar4 = ProcessMenu(this,ptVar7), iVar4 == 0)) &&
       (iVar4 = ScreenToWorld(this,&local_14,&DisplayInterface::mousePos,
                              DisplayInterface::currentCamera), iVar4 != 0)) {
      _ftol2_sse();
      this->currentX = extraout_EAX;
      _ftol2_sse();
      this->currentZ = extraout_EAX_00;
      if (edit_controls.edit_copy != '\0') {
        Copy(this,&local_14);
      }
      if (edit_controls.edit_paste != '\0') {
        Paste(this,&local_14);
      }
      if (TerrainWireFrame == 0) {
        DrawTileOutline(this,&local_14);
      }
      else {
        fVar8 = DrawGridVertex(this,&local_14);
        this->currentY = fVar8;
        UpdateStatusLine(this);
      }
      ProcessShortcutKeys(this);
      ProcessCommand(this_00,&local_14);
    }
    DrawMenu(this,ptVar7);
    DrawWorldMap(this);
    ptVar2 = this->currCursor;
    iVar4 = ptVar2->index;
    iVar9 = 0x200001;
    iVar5 = GetSpriteHeight(iVar4);
    iVar5 = (iVar5 * (ptVar2->align).y) / 2 + DisplayInterface::mousePos.y;
    iVar6 = GetSpriteWidth(iVar4);
    DrawSprite(DisplayInterface::currentBuffer,iVar4,
               (iVar6 * (ptVar2->align).x) / 2 + DisplayInterface::mousePos.x,iVar5,iVar9);
    Set_Rounding(unaff_EDI);
    return;
  }
  return;
}
