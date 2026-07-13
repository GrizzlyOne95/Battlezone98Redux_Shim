/*
 * Entry: 0046753a
 * Name: TurretBlastAttack::TurretBlastAttack
 * Namespace: TurretBlastAttack
 * Signature: TurretBlastAttack * TurretBlastAttack(TurretBlastAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TurretBlastAttack * __thiscall
TurretBlastAttack::TurretBlastAttack(TurretBlastAttack *this,Craft *param_1,GameObject *param_2)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined4 *)&this->field_0xf8 = 0x3ca3d70a;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 5;
  *(undefined4 *)&this->field_0xfc = 0;
  *(undefined4 *)&this->field_0x74 = 0;
  return this;
}
