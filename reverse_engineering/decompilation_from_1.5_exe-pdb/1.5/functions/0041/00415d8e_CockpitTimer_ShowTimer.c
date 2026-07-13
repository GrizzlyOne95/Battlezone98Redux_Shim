/*
 * Entry: 00415d8e
 * Name: CockpitTimer::ShowTimer
 * Namespace: CockpitTimer
 * Signature: void ShowTimer(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::ShowTimer(CockpitTimer *this)

{
  if (this->show == false) {
    this->show = true;
    DisplayInterface::AddViewRender((DisplayInterface *)this,0,0);
    DisplayInterface::AddViewRender((DisplayInterface *)this,2,0);
    DisplayInterface::AddViewRender((DisplayInterface *)this,1,0);
    DisplayInterface::AddViewRender((DisplayInterface *)this,7,0);
    DisplayInterface::AddViewRender((DisplayInterface *)this,3,0);
  }
  return;
}
