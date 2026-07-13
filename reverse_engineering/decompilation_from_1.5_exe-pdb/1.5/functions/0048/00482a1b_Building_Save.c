/*
 * Entry: 00482a1b
 * Name: Building::Save
 * Namespace: Building
 * Signature: bool Save(Building * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Building::Save(Building *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (((missionSave) || (bVar1 = ::out(param_1,&this->tempBuilding,1,"tempBuilding"), bVar1)) &&
     (bVar1 = GameObject::Save((GameObject *)this,param_1), bVar1)) {
    return true;
  }
  return false;
}
