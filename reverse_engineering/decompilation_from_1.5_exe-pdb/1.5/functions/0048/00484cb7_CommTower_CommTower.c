/*
 * Entry: 00484cb7
 * Name: CommTower::CommTower
 * Namespace: CommTower
 * Signature: CommTower * CommTower(CommTower * this, _OBJ76 * param_1, CommTowerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CommTower * __thiscall CommTower::CommTower(CommTower *this,_OBJ76 *param_1,CommTowerClass *param_2)

{
  Scanner *pSVar1;
  
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->powerSource = 0;
  this->_padding_ = 0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  pSVar1 = operator_new(0x14);
  if (pSVar1 == (Scanner *)0x0) {
    pSVar1 = (Scanner *)0x0;
  }
  else {
    pSVar1 = Scanner::Scanner(pSVar1,(GameObject *)this);
  }
  this->saveScanner = pSVar1;
  pSVar1->range = param_2->rangeScan;
  this->saveScanner->period = param_2->periodScan;
  StopSpinners(this,param_1);
  return this;
}
