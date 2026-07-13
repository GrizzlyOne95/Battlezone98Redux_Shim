/*
 * Entry: 00482c56
 * Name: Building::Load
 * Namespace: Building
 * Signature: bool Load(Building * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Building::Load(Building *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  bool bVar3;
  float local_10;
  float local_c;
  int local_8;
  
  p_Var1 = param_1;
  bVar3 = false;
  bVar2 = true;
  if ((0x7d3 < version) && (*(int *)(this->_padding_ + 0x20) == 0x504f5254)) {
    bVar2 = ::in(param_1,&local_8,4);
    if ((bVar2) &&
       (((bVar2 = ::in(p_Var1,&local_c,4), bVar2 && (bVar2 = ::in(p_Var1,&local_10,4), bVar2)) &&
        (bVar2 = ::in(p_Var1,(bool *)((int)&param_1 + 3),1), bVar2)))) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  if (missionSave == false) {
    if (!bVar2) goto LAB_00482d11;
    bVar2 = ::in(p_Var1,&this->tempBuilding,1);
  }
  else {
    this->tempBuilding = false;
  }
  if ((bVar2) && (bVar2 = GameObject::Load((GameObject *)this,p_Var1), bVar2)) {
    bVar3 = true;
  }
LAB_00482d11:
  GameObject::UpdatePosition((GameObject *)this);
  return bVar3;
}
