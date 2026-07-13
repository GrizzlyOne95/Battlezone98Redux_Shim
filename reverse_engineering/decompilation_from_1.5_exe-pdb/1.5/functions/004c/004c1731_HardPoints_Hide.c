/*
 * Entry: 004c1731
 * Name: HardPoints::Hide
 * Namespace: HardPoints
 * Signature: void Hide(HardPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HardPoints::Hide(HardPoints *this)

{
  DisplayInterface::RemViewRender((DisplayInterface *)this,0);
  DisplayInterface::RemViewRender((DisplayInterface *)this,2);
  DisplayInterface::RemViewRender((DisplayInterface *)this,1);
  DisplayInterface::RemViewRender((DisplayInterface *)this,7);
  DisplayInterface::RemViewRender((DisplayInterface *)this,3);
  return;
}
