/*
 * Entry: 004d3066
 * Name: OverView::SetZoom
 * Namespace: OverView
 * Signature: void SetZoom(OverView * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::SetZoom(OverView *this,float param_1)

{
  (this->viewCenter).x = param_1;
  return;
}
