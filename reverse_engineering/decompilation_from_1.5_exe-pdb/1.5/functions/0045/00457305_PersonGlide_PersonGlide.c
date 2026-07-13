/*
 * Entry: 00457305
 * Name: PersonGlide::PersonGlide
 * Namespace: PersonGlide
 * Signature: PersonGlide * PersonGlide(PersonGlide * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonGlide * __thiscall
PersonGlide::PersonGlide(PersonGlide *this,Craft *param_1,GameObject *param_2)

{
  undefined4 *puVar1;
  
  UnitTask::UnitTask((UnitTask *)this,param_1,param_2);
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0xc = 2;
  if (param_2 != (GameObject *)0x0) {
    puVar1 = (undefined4 *)(**(code **)(param_2->_padding_ + 0xc))();
    *(undefined4 *)&this->field_0x2c = *puVar1;
    *(undefined4 *)&this->field_0x30 = puVar1[1];
    *(undefined4 *)&this->field_0x34 = puVar1[2];
  }
  return this;
}
