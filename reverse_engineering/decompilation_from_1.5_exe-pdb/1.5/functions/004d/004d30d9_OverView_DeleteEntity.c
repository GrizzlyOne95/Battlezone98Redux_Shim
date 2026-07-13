/*
 * Entry: 004d30d9
 * Name: OverView::DeleteEntity
 * Namespace: OverView
 * Signature: void DeleteEntity(OverView * this, tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::DeleteEntity(OverView *this,tagENTITY *param_1)

{
  if (this->viewObj == (GameObject *)param_1) {
    this->viewObj = (GameObject *)0x0;
    this->viewZoom = 0.0;
  }
  return;
}
