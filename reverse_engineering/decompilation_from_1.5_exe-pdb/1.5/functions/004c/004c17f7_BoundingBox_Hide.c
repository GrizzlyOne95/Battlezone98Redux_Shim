/*
 * Entry: 004c17f7
 * Name: BoundingBox::Hide
 * Namespace: BoundingBox
 * Signature: void Hide(BoundingBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BoundingBox::Hide(BoundingBox *this)

{
  DisplayInterface::RemViewRender((DisplayInterface *)this,0);
  DisplayInterface::RemViewRender((DisplayInterface *)this,2);
  DisplayInterface::RemViewRender((DisplayInterface *)this,1);
  DisplayInterface::RemViewRender((DisplayInterface *)this,7);
  DisplayInterface::RemViewRender((DisplayInterface *)this,3);
  return;
}
