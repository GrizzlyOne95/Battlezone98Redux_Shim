/*
 * Entry: 00467964
 * Name: TurretBlastAttack::~TurretBlastAttack
 * Namespace: TurretBlastAttack
 * Signature: void ~TurretBlastAttack(TurretBlastAttack * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretBlastAttack::~TurretBlastAttack(TurretBlastAttack *this)

{
  *(undefined ***)this = &_vftable_;
  CleanState(this);
  *(undefined4 *)&this->field_0xc = 0xd;
  UnitTask::~UnitTask((UnitTask *)this);
  return;
}
