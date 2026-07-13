/*
 * Entry: 004c17bf
 * Name: BoundingBox::Show
 * Namespace: BoundingBox
 * Signature: void Show(BoundingBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BoundingBox::Show(BoundingBox *this)

{
  DisplayInterface::AddViewRender((DisplayInterface *)this,0,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,2,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,1,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,7,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,3,0);
  return;
}
