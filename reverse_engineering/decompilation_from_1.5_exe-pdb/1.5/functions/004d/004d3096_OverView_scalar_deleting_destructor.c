/*
 * Entry: 004d3096
 * Name: OverView::`scalar_deleting_destructor'
 * Namespace: OverView
 * Signature: void * `scalar_deleting_destructor'(OverView * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall OverView::_scalar_deleting_destructor_(OverView *this,uint param_1)

{
  DisplayInterface::~DisplayInterface((DisplayInterface *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
