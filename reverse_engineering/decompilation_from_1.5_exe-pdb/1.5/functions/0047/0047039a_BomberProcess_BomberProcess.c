/*
 * Entry: 0047039a
 * Name: BomberProcess::BomberProcess
 * Namespace: BomberProcess
 * Signature: BomberProcess * BomberProcess(BomberProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BomberProcess * __thiscall BomberProcess::BomberProcess(BomberProcess *this)

{
  WingmanProcess::WingmanProcess((WingmanProcess *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
