/*
 * Entry: 004c16f9
 * Name: HardPoints::Show
 * Namespace: HardPoints
 * Signature: void Show(HardPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HardPoints::Show(HardPoints *this)

{
  DisplayInterface::AddViewRender((DisplayInterface *)this,0,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,2,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,1,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,7,0);
  DisplayInterface::AddViewRender((DisplayInterface *)this,3,0);
  return;
}
