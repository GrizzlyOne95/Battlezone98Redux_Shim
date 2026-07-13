/*
 * Entry: 00470196
 * Name: WingmanProcess::WingmanProcess
 * Namespace: WingmanProcess
 * Signature: WingmanProcess * WingmanProcess(WingmanProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WingmanProcess * __thiscall WingmanProcess::WingmanProcess(WingmanProcess *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
