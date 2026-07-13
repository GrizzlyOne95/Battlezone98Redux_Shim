/*
 * Entry: 0052d001
 * Name: DayWrecker::DayWrecker
 * Namespace: DayWrecker
 * Signature: DayWrecker * DayWrecker(DayWrecker * this, _OBJ76 * param_1, DayWreckerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DayWrecker * __thiscall
DayWrecker::DayWrecker(DayWrecker *this,_OBJ76 *param_1,DayWreckerClass *param_2)

{
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
