/*
 * Entry: 004d3167
 * Name: OverView::SetObject
 * Namespace: OverView
 * Signature: void SetObject(OverView * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::SetObject(OverView *this,GameObject *param_1)

{
  GameObject *pGVar1;
  float *pfVar2;
  
  pGVar1 = (GameObject *)(**(code **)(param_1->_padding_ + 0x2c))();
  this->viewObj = pGVar1;
  this->viewZoom = (float)param_1;
  pfVar2 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  (this->viewCenter).y = *pfVar2;
  (this->viewCenter).z = pfVar2[1];
  (this->viewUp).x = pfVar2[2];
  return;
}
