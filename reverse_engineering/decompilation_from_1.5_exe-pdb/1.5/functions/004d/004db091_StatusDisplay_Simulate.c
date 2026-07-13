/*
 * Entry: 004db091
 * Name: StatusDisplay::Simulate
 * Namespace: StatusDisplay
 * Signature: void Simulate(StatusDisplay * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall StatusDisplay::Simulate(StatusDisplay *this,float param_1)

{
  int iVar1;
  GameObject *pGVar2;
  float10 fVar3;
  float fVar4;
  float fVar5;
  
  pGVar2 = GameObject::userObject;
  if (GameObject::userObject != (GameObject *)0x0) {
    fVar5 = param_1 + param_1;
    fVar4 = fVar5;
    fVar3 = (float10)(**(code **)(GameObject::userObject->_padding_ + 0x1c))();
    fVar4 = lpfilter(this->hullRatio,(float)fVar3,fVar4);
    iVar1 = pGVar2->_padding_;
    this->hullRatio = fVar4;
    fVar3 = (float10)(**(code **)(iVar1 + 0x1c))();
    fVar5 = lpfilter(this->ammoRatio,(float)fVar3,fVar5);
    this->ammoRatio = fVar5;
  }
  return;
}
