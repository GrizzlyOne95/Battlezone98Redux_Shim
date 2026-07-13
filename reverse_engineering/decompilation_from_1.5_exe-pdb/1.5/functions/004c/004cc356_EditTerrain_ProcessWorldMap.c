/*
 * Entry: 004cc356
 * Name: EditTerrain::ProcessWorldMap
 * Namespace: EditTerrain
 * Signature: int ProcessWorldMap(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall EditTerrain::ProcessWorldMap(EditTerrain *this)

{
  _GRAPHIC_BUFFER *p_Var1;
  tagPOINT tVar2;
  tagPOINT tVar3;
  int iVar4;
  float fVar5;
  tagPOINT local_34 [4];
  VECTOR_3D local_14;
  int local_8;
  
  p_Var1 = DisplayInterface::currentCamera->Buffer;
  local_34[0].x = (p_Var1->Pane).x1 - (p_Var1->Pane).x0 >> 1;
  local_34[0].y = (p_Var1->Pane).y1 - (p_Var1->Pane).y0 >> 1;
  iVar4 = ScreenToWorld(this,&local_14,local_34,DisplayInterface::currentCamera);
  if (iVar4 != 0) {
    tVar3.y = DisplayInterface::mousePos.y;
    tVar3.x = DisplayInterface::mousePos.x;
    iVar4 = InsideRect(tVar3,&this->mapRect);
    if (iVar4 != 0) {
      if (this->mapState == 0) {
        this->mapState = 1;
      }
      if ((this->mapState == 4) && (edit_controls.edit_lmouse == '\0')) {
        this->mapState = 1;
      }
      tVar2.y = DisplayInterface::mousePos.y;
      tVar2.x = DisplayInterface::mousePos.x;
      iVar4 = InsideRect(tVar2,&this->dragRect);
      if (iVar4 == 0) {
        if (this->mapState == 2) {
          this->mapState = 1;
        }
      }
      else if ((this->mapState == 1) && (edit_controls.edit_lmouse == '\0')) {
        this->mapState = 2;
      }
      else if ((this->mapState == 2) && (edit_controls.edit_lmouse != '\0')) {
        this->mapState = 4;
      }
      if (this->mapState == 4) {
        local_8 = (this->mapRect).bottom;
        (this->viewCenter).x =
             ((float)(DisplayInterface::mousePos.x - (this->mapRect).left) * this->worldDX) /
             (float)this->mapDX + this->worldExtents[0].x;
        local_8 = local_8 - DisplayInterface::mousePos.y;
        fVar5 = ((float)local_8 * this->worldDZ) / (float)this->mapDY + this->worldExtents[0].z;
        (this->viewCenter).z = fVar5;
        fVar5 = Terrain_FindFloor((double)(this->viewCenter).x,(double)fVar5);
        (this->viewCenter).y = fVar5;
      }
      this->currCursor = &arrowCursor;
      return 1;
    }
    this->mapState = 0;
  }
  return 0;
}
