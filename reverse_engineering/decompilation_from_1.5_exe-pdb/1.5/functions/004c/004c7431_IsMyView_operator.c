/*
 * Entry: 004c7431
 * Name: IsMyView::operator()
 * Namespace: IsMyView
 * Signature: bool operator()(IsMyView * this, DisplayViewInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall IsMyView::operator()(IsMyView *this,DisplayViewInfo *param_1)

{
  return (bool)('\x01' - (param_1->display != this->me));
}
