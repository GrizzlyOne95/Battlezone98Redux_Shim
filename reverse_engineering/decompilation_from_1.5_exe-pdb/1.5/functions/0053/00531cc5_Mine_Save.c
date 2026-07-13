/*
 * Entry: 00531cc5
 * Name: Mine::Save
 * Namespace: Mine
 * Signature: bool Save(Mine * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Mine::Save(Mine *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (((missionSave) || (bVar1 = ::out(param_1,&this->lifeTimer,4,"lifeTimer"), bVar1)) &&
     (bVar1 = Building::Save((Building *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
