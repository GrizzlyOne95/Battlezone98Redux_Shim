/*
 * Entry: 004d3079
 * Name: OverView::OverView
 * Namespace: OverView
 * Signature: OverView * OverView(OverView * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OverView * __thiscall OverView::OverView(OverView *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,3,0);
  return this;
}
