/*
 * Entry: 00536d2e
 * Name: ProximityMine::Save
 * Namespace: ProximityMine
 * Signature: bool Save(ProximityMine * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ProximityMine::Save(ProximityMine *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (((missionSave) || (bVar1 = ::out(param_1,&this->searchTimer,4,"searchTimer"), bVar1)) &&
     (bVar1 = Mine::Save((Mine *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
