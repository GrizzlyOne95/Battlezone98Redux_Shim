/*
 * Entry: 00484d29
 * Name: CommTower::~CommTower
 * Namespace: CommTower
 * Signature: void ~CommTower(CommTower * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CommTower::~CommTower(CommTower *this)

{
  Scanner *this_00;
  
  this_00 = this->saveScanner;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  if (this_00 != (Scanner *)0x0) {
    Scanner::~Scanner(this_00);
    operator_delete(this_00);
  }
  Building::~Building((Building *)this);
  return;
}
