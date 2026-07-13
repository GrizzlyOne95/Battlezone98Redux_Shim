/*
 * Entry: 004703ac
 * Name: BomberProcess::~BomberProcess
 * Namespace: BomberProcess
 * Signature: void ~BomberProcess(BomberProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BomberProcess::~BomberProcess(BomberProcess *this)

{
  *(undefined ***)this = &WingmanProcess::_vftable_;
  UnitProcess::CleanState((UnitProcess *)this);
  *(undefined4 *)&this->field_0x18 = 0;
  OffensiveProcess::~OffensiveProcess((OffensiveProcess *)this);
  return;
}
