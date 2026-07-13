/*
 * Entry: 004b06b4
 * Name: ScrapSilo::ScrapSilo
 * Namespace: ScrapSilo
 * Signature: ScrapSilo * ScrapSilo(ScrapSilo * this, _OBJ76 * param_1, ScrapSiloClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapSilo * __thiscall ScrapSilo::ScrapSilo(ScrapSilo *this,_OBJ76 *param_1,ScrapSiloClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->dropoff = -1;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  return this;
}
