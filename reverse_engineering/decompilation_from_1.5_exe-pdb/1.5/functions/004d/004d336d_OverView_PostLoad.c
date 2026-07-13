/*
 * Entry: 004d336d
 * Name: OverView::PostLoad
 * Namespace: OverView
 * Signature: void PostLoad(OverView * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::PostLoad(OverView *this)

{
  float fVar1;
  
  (this->viewCenter).x = 4.0;
  this->wasDown = 0;
  this->startCommand = CMD_NONE;
  this->viewObj = (GameObject *)0x0;
  this->viewZoom = 0.0;
  (this->viewCenter).y = (edgeMaxX + edgeMinX) * 0.5;
  fVar1 = (edgeMaxZ + edgeMinZ) * 0.5;
  (this->viewUp).x = fVar1;
  fVar1 = Terrain_FindFloor((double)(this->viewCenter).y,(double)fVar1);
  (this->viewCenter).z = fVar1;
  (this->viewUp).y = 0.0;
  (this->viewUp).z = 0.0;
  this[1]._padding_ = 0x3f800000;
  return;
}
