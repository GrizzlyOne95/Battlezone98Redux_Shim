/*
 * Entry: 004afb65
 * Name: ScrapField::ScrapField
 * Namespace: ScrapField
 * Signature: ScrapField * ScrapField(ScrapField * this, _OBJ76 * param_1, ScrapFieldClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapField * __thiscall
ScrapField::ScrapField(ScrapField *this,_OBJ76 *param_1,ScrapFieldClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  DeleteCollisionEntity(*(tagENTITY **)&this->field_0xe4);
  return this;
}
