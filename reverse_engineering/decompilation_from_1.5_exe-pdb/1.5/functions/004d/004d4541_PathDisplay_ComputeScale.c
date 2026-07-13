/*
 * Entry: 004d4541
 * Name: PathDisplay::ComputeScale
 * Namespace: PathDisplay
 * Signature: void ComputeScale(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::ComputeScale(PathDisplay *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = TimeStep();
  fVar1 = (float)(((DisplayInterface::currentBuffer->Pane).x1 -
                  (DisplayInterface::currentBuffer->Pane).x0) + 1) / this->worldDx;
  fVar2 = (float)(((DisplayInterface::currentBuffer->Pane).y1 -
                  (DisplayInterface::currentBuffer->Pane).y0) + 1);
  if (fVar2 < this->worldDz * fVar1) {
    fVar1 = fVar2 / this->worldDz;
  }
  if (eye_controls.zoom_factor_reset == '\0') {
    if (eye_controls.zoom_factor_plus == '\0') {
      if (eye_controls.zoom_factor_minus == '\0') goto LAB_004d45cb;
      fVar2 = this->scale - fVar4 * this->scale * 0.5;
    }
    else {
      fVar2 = (fVar4 * 0.5 + 1.0) * this->scale;
    }
    this->scale = fVar2;
  }
  else {
    this->scale = fVar1;
  }
LAB_004d45cb:
  fVar2 = 100.0;
  if ((100.0 < this->scale) || (fVar2 = fVar1, this->scale < fVar1)) {
    this->scale = fVar2;
  }
  fVar3 = 1.0 / this->scale;
  fVar1 = (float)eye_controls.track_yaw * fVar3 * fVar4 * 50.0 + this->worldX0;
  this->worldX0 = fVar1;
  fVar2 = (float)grid_rect.left;
  if ((fVar1 < fVar2) || (fVar2 = (float)grid_rect.right, fVar2 < fVar1)) {
    this->worldX0 = fVar2;
  }
  fVar1 = (float)eye_controls.track_pitch * fVar3 * fVar4 * 50.0 + this->worldZ0;
  this->worldZ0 = fVar1;
  fVar2 = (float)grid_rect.top;
  if ((fVar1 < fVar2) || (fVar2 = (float)grid_rect.bottom, fVar2 < fVar1)) {
    this->worldZ0 = fVar2;
  }
  this->screenX0 =
       (((DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0) +
       1) / 2;
  this->screenY0 =
       (((DisplayInterface::currentBuffer->Pane).y1 - (DisplayInterface::currentBuffer->Pane).y0) +
       1) / 2;
  return;
}
