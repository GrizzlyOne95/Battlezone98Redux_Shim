/*
 * Entry: 004d30ed
 * Name: OverView::SelectionBox
 * Namespace: OverView
 * Signature: void SelectionBox(OverView * this, tagRECT param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OverView::SelectionBox(OverView *this,tagRECT param_1,long param_2)

{
  Graphic_Line(DisplayInterface::currentBuffer,param_1.left,param_1.top,param_1.right,param_1.top,
               param_2,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,param_1.right,param_1.top,param_1.right,
               param_1.bottom,param_2,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,param_1.right,param_1.bottom,param_1.left,
               param_1.bottom,param_2,SOLID_PIXELS);
  Graphic_Line(DisplayInterface::currentBuffer,param_1.left,param_1.bottom,param_1.left,param_1.top,
               param_2,SOLID_PIXELS);
  return;
}
