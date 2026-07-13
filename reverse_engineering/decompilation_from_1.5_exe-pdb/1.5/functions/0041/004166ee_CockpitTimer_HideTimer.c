/*
 * Entry: 004166ee
 * Name: CockpitTimer::HideTimer
 * Namespace: CockpitTimer
 * Signature: void HideTimer(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::HideTimer(CockpitTimer *this)

{
  if (this->show != false) {
    this->show = false;
    DisplayInterface::RemViewRender((DisplayInterface *)this,0);
    DisplayInterface::RemViewRender((DisplayInterface *)this,2);
    DisplayInterface::RemViewRender((DisplayInterface *)this,1);
    DisplayInterface::RemViewRender((DisplayInterface *)this,7);
    DisplayInterface::RemViewRender((DisplayInterface *)this,3);
  }
  return;
}
