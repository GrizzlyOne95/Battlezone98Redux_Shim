/*
 * Entry: 004b30ab
 * Name: Tug::SetActiveMode
 * Namespace: Tug
 * Signature: bool SetActiveMode(Tug * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Tug::SetActiveMode(Tug *this,int param_1)

{
  bool bVar1;
  VECTOR_3D *pVVar2;
  long lVar3;
  
  if (param_1 == 4) {
    lVar3 = 0;
    pVVar2 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    GameObject::SetCommand((GameObject *)this,CMD_DROPOFF,pVVar2,lVar3);
    bVar1 = true;
  }
  else {
    bVar1 = Craft::SetActiveMode((Craft *)this,param_1);
  }
  return bVar1;
}
