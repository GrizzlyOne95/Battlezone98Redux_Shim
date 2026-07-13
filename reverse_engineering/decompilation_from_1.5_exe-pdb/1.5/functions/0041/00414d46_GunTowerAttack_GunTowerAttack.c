/*
 * Entry: 00414d46
 * Name: GunTowerAttack::GunTowerAttack
 * Namespace: GunTowerAttack
 * Signature: GunTowerAttack * GunTowerAttack(GunTowerAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GunTowerAttack * __thiscall
GunTowerAttack::GunTowerAttack(GunTowerAttack *this,Craft *param_1,GameObject *param_2)

{
  GunTowerAttack *local_c;
  GunTowerAttack *local_8;
  
  local_c = this;
  local_8 = this;
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined4 *)&this->field_0x74 = 0;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 5;
  CalcRange(param_1,(float *)&param_2,(float *)&local_8,(float *)&local_c,
            (Weapon **)&this->field_0xb8);
  *(float *)&this->field_0xa0 = (float)param_2 * (float)param_2;
  *(float *)&this->field_0xa4 = (float)local_8 * (float)local_8;
  return this;
}
