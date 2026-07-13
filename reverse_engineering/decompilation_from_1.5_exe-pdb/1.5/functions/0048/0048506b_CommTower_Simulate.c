/*
 * Entry: 0048506b
 * Name: CommTower::Simulate
 * Namespace: CommTower
 * Signature: void Simulate(CommTower * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CommTower::Simulate(CommTower *this,float param_1)

{
  Scanner *pSVar1;
  int iVar2;
  GameObject *pGVar3;
  int extraout_EDX;
  
  iVar2 = ClosestPower(this);
  this->powerSource = iVar2;
  pGVar3 = GameObjectHandle::GetObj(iVar2);
  if (pGVar3 == (GameObject *)0x0) {
    pSVar1 = (Scanner *)this->_padding_;
    if (pSVar1 != (Scanner *)0x0) {
      this->saveScanner = pSVar1;
      this->_padding_ = 0;
      StopSpinners(this,(_OBJ76 *)this->_padding_);
      if ((GameObject::userTeamNumber == this->_padding_) &&
         (controlPanel.satelliteEnabled = controlPanel.satelliteEnabled + -1,
         controlPanel.satelliteEnabled == 0)) {
        BettyVoice::SatelliteDisabled(&bettyVoice);
      }
    }
  }
  else if (this->_padding_ == 0) {
    this->_padding_ = (int)this->saveScanner;
    this->saveScanner = (Scanner *)0x0;
    StartSpinners(this,(_OBJ76 *)this->_padding_);
    if (GameObject::userTeamNumber == this->_padding_) {
      if (controlPanel.satelliteEnabled == extraout_EDX) {
        BettyVoice::SatelliteEnabled(&bettyVoice);
      }
      controlPanel.satelliteEnabled = controlPanel.satelliteEnabled + 1;
    }
  }
  Building::Simulate((Building *)this,param_1);
  return;
}
