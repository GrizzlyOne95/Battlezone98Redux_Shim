/*
 * Entry: 00531c7b
 * Name: Mine::Load
 * Namespace: Mine
 * Signature: bool Load(Mine * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Mine::Load(Mine *this,_iobuf *param_1)

{
  bool bVar1;
  
  if ((((version < 0x40e) || (missionSave)) || (bVar1 = ::in(param_1,&this->lifeTimer,4), bVar1)) &&
     (bVar1 = Building::Load((Building *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
