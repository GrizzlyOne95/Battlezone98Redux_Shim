/*
 * Entry: 004d34a1
 * Name: OverView::MoveCamera
 * Namespace: OverView
 * Signature: void MoveCamera(OverView * this, tagPOINT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::MoveCamera(OverView *this,tagPOINT param_1)

{
  int iVar1;
  float fVar2;
  float *pfVar3;
  VECTOR_3D *pVVar4;
  float fVar5;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  local_10 = TimeStepLocal();
  local_c = 0.0;
  local_8 = 0.0;
  fVar5 = (SCROLL_SPEED / (this->viewCenter).x) * local_10;
  fVar2 = fVar5;
  if ((9 < param_1.y) &&
     (fVar2 = local_8,
     ((DisplayInterface::currentBuffer->Pane).y1 - (DisplayInterface::currentBuffer->Pane).y0) + -10
     <= param_1.y)) {
    fVar2 = -fVar5;
  }
  local_8 = fVar2;
  if (param_1.x < 10) {
    fVar5 = -fVar5;
LAB_004d3506:
    local_c = fVar5;
    if (local_c == 0.0) goto LAB_004d3599;
  }
  else {
    if (((DisplayInterface::currentBuffer->Pane).x1 - (DisplayInterface::currentBuffer->Pane).x0) +
        -10 <= param_1.x) goto LAB_004d3506;
LAB_004d3599:
    if (local_8 == 0.0) {
      if (this->viewZoom != 0.0) {
        pfVar3 = (float *)(**(code **)(*(int *)((int)this->viewZoom + 0x20) + 0xc))();
        fVar5 = this->viewZoom;
        (this->viewCenter).y = *pfVar3;
        (this->viewCenter).z = pfVar3[1];
        (this->viewUp).x = pfVar3[2];
        iVar1 = *(int *)((int)fVar5 + 0xe8);
        pfVar3 = &(this->viewUp).y;
        *pfVar3 = *(float *)(iVar1 + 0x38);
        (this->viewUp).z = *(float *)(iVar1 + 0x3c);
        this[1]._padding_ = *(int *)(iVar1 + 0x40);
        (this->viewUp).z = 0.0;
        pVVar4 = Normalize_Vector(&local_1c,(VECTOR_3D *)pfVar3);
        (this->viewUp).y = pVVar4->x;
        (this->viewUp).z = pVVar4->y;
        this[1]._padding_ = (int)pVVar4->z;
      }
      goto LAB_004d3583;
    }
  }
  this->viewZoom = 0.0;
  fVar5 = Clamp((float)this[1]._padding_ * local_c + (this->viewUp).y * local_8 +
                (this->viewCenter).y,edgeMinX,edgeMaxX);
  (this->viewCenter).y = fVar5;
  fVar5 = Clamp(((float)this[1]._padding_ * local_8 + (this->viewUp).x) - (this->viewUp).y * local_c
                ,edgeMinZ,edgeMaxZ);
  (this->viewUp).x = fVar5;
LAB_004d3583:
  if (eye_controls.zoom_factor_reset == '\0') {
    if (eye_controls.zoom_factor_plus == '\0') {
      if (eye_controls.zoom_factor_minus == '\0') {
        return;
      }
      fVar2 = (this->viewCenter).x - (this->viewCenter).x * local_10 * 0.5;
      (this->viewCenter).x = fVar2;
      fVar5 = 2.0;
      if (2.0 <= fVar2) {
        return;
      }
    }
    else {
      fVar2 = (local_10 * 0.5 + 1.0) * (this->viewCenter).x;
      (this->viewCenter).x = fVar2;
      fVar5 = 8.0;
      if (fVar2 <= 8.0) {
        return;
      }
    }
  }
  else {
    fVar5 = 4.0;
  }
  (this->viewCenter).x = fVar5;
  return;
}
