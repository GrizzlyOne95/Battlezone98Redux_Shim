/*
 * Entry: 004824ea
 * Name: Barracks::Barracks
 * Namespace: Barracks
 * Signature: Barracks * Barracks(Barracks * this, _OBJ76 * param_1, BarracksClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Barracks * __thiscall Barracks::Barracks(Barracks *this,_OBJ76 *param_1,BarracksClass *param_2)

{
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->nextEmptyCheck = 0.0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  return this;
}
