/*
 * Entry: 00485633
 * Name: ConstructionRig::StartUnbuild
 * Namespace: ConstructionRig
 * Signature: bool StartUnbuild(ConstructionRig * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ConstructionRig::StartUnbuild(ConstructionRig *this,GameObject *param_1)

{
  int iVar1;
  GameObjectClass *pGVar2;
  
  if (param_1 != (GameObject *)0x0) {
    iVar1 = GameObject::GetHandle(param_1);
    this->unbuildHandle = iVar1;
    pGVar2 = (GameObjectClass *)(**(code **)param_1->_padding_)();
    this->dropClass = pGVar2;
    this->_padding_ = (int)pGVar2->buildTime;
  }
  return param_1 != (GameObject *)0x0;
}
