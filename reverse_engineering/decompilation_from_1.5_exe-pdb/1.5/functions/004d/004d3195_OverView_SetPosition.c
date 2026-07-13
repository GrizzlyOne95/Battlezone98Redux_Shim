/*
 * Entry: 004d3195
 * Name: OverView::SetPosition
 * Namespace: OverView
 * Signature: void SetPosition(OverView * this, VECTOR_2D param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::SetPosition(OverView *this,VECTOR_2D param_1)

{
  float fVar1;
  
  this->viewObj = (GameObject *)0x0;
  (this->viewCenter).y = param_1.x;
  this->viewZoom = 0.0;
  (this->viewUp).x = param_1.z;
  fVar1 = Terrain_FindFloor((double)param_1.x,(double)param_1.z);
  (this->viewCenter).z = fVar1;
  return;
}
