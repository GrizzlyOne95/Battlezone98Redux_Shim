/*
 * Entry: 00536b98
 * Name: ProximityMine::ProximityMine
 * Namespace: ProximityMine
 * Signature: ProximityMine * ProximityMine(ProximityMine * this, _OBJ76 * param_1, ProximityMineClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ProximityMine * __thiscall
ProximityMine::ProximityMine(ProximityMine *this,_OBJ76 *param_1,ProximityMineClass *param_2)

{
  Mine::Mine((Mine *)this,param_1,(MineClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->searchTimer = param_2->searchPeriod;
  return this;
}
