/*
 * Entry: 004c9cab
 * Name: EditTerrain::MoveCamera
 * Namespace: EditTerrain
 * Signature: void MoveCamera(EditTerrain * this, tagPOINT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::MoveCamera(EditTerrain *this,tagPOINT param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar4 = TimeStepLocal();
  fVar2 = 0.0;
  fVar5 = (SCROLL_SPEED / this->viewZoom) * fVar4;
  fVar1 = fVar5;
  if ((9 < param_1.y) &&
     (fVar1 = fVar2,
     ((DisplayInterface::currentBuffer->Pane).y1 - (DisplayInterface::currentBuffer->Pane).y0) + -10
     <= param_1.y)) {
    fVar1 = -fVar5;
  }
  if (param_1.x < 10) {
    fVar2 = -fVar5;
  }
  else if (((DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0)
           + -10 <= param_1.x) {
    fVar2 = fVar5;
  }
  if (edit_controls.edit_left != '\0') {
    fVar2 = -fVar5;
  }
  if (edit_controls.edit_right != '\0') {
    fVar2 = fVar5;
  }
  if (edit_controls.edit_up != '\0') {
    fVar1 = fVar5;
  }
  if (edit_controls.edit_down != '\0') {
    fVar1 = -fVar5;
  }
  if ((fVar2 != 0.0) || (fVar1 != 0.0)) {
    fVar3 = (this->viewUp).z * fVar2 + (this->viewUp).x * fVar1 + (this->viewCenter).x;
    (this->viewCenter).x = fVar3;
    fVar5 = ((this->viewUp).z * fVar1 - (this->viewUp).x * fVar2) + (this->viewCenter).z;
    (this->viewCenter).z = fVar5;
    fVar5 = Terrain_FindFloor((double)fVar3,(double)fVar5);
    (this->viewCenter).y = fVar5;
  }
  if (eye_controls.zoom_factor_reset == '\0') {
    if (eye_controls.zoom_factor_plus == '\0') {
      if (eye_controls.zoom_factor_minus == '\0') {
        return;
      }
      fVar1 = this->viewZoom - this->viewZoom * fVar4 * 0.5;
      this->viewZoom = fVar1;
      fVar5 = 1.7;
      if (1.7 <= fVar1) {
        return;
      }
    }
    else {
      fVar1 = (fVar4 * 0.5 + 1.0) * this->viewZoom;
      this->viewZoom = fVar1;
      fVar5 = 16.0;
      if (fVar1 <= 16.0) {
        return;
      }
    }
  }
  else {
    fVar5 = 8.0;
  }
  this->viewZoom = fVar5;
  return;
}
