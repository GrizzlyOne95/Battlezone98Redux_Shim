/*
 * Entry: 00470417
 * Name: WingmanBlastAttack::WingmanBlastAttack
 * Namespace: WingmanBlastAttack
 * Signature: WingmanBlastAttack * WingmanBlastAttack(WingmanBlastAttack * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WingmanBlastAttack * __thiscall
WingmanBlastAttack::WingmanBlastAttack(WingmanBlastAttack *this,Craft *param_1,GameObject *param_2)

{
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined4 *)&this->field_0xf8 = 0x3ca3d70a;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 1;
  *(undefined4 *)&this->field_0xfc = 0;
  *(undefined4 *)&this->field_0x10 = 5;
  return this;
}
