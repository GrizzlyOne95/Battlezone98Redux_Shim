/*
 * Entry: 004899b0
 * Name: CraftClass::CraftClass
 * Namespace: CraftClass
 * Signature: CraftClass * CraftClass(CraftClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CraftClass * __thiscall CraftClass::CraftClass(CraftClass *this)

{
  GameObjectClass::GameObjectClass((GameObjectClass *)this);
  this->rangeScan = 200.0;
  this->periodScan = 0.0;
  this->_padding_ = 1;
  this->_padding_ = 1;
  this->velocJam = 0.0;
  this->selectWaitMsg[0] = '\0';
  this->fPersonEjectRatio = 0.3;
  this->selectGoMsg[0] = '\0';
  this->selectFollowMsg[0] = '\0';
  this->selectAttackMsg[0] = '\0';
  this->selectUser1Msg[0] = '\0';
  this->selectUser2Msg[0] = '\0';
  this->selectOtherMsg[0] = '\0';
  this->goMsg[0] = '\0';
  this->goObjectMsg[0] = '\0';
  this->followMsg[0] = '\0';
  this->attackMsg[0] = '\0';
  this->repairMsg[0] = '\0';
  this->reloadMsg[0] = '\0';
  this->rescueMsg[0] = '\0';
  this->recycleMsg[0] = '\0';
  this->user1Msg[0] = '\0';
  this->user2Msg[0] = '\0';
  this->otherMsg[0] = '\0';
  this->deployedMsg[0] = '\0';
  this->packedMsg[0] = '\0';
  this->killedMsg[0] = '\0';
  this->diedMsg[0] = '\0';
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x43524654;
  this->_padding_ = (int)"craft";
  return this;
}
