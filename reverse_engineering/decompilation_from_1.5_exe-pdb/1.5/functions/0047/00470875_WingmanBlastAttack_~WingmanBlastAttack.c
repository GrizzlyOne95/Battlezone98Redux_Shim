/*
 * Entry: 00470875
 * Name: WingmanBlastAttack::~WingmanBlastAttack
 * Namespace: WingmanBlastAttack
 * Signature: void ~WingmanBlastAttack(WingmanBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WingmanBlastAttack::~WingmanBlastAttack(WingmanBlastAttack *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
