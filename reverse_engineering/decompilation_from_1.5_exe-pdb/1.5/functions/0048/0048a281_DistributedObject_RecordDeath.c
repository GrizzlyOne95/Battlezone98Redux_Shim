/*
 * Entry: 0048a281
 * Name: DistributedObject::RecordDeath
 * Namespace: DistributedObject
 * Signature: void RecordDeath(DistributedObject * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::RecordDeath(DistributedObject *this,int param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(this->_padding_ + 4))();
  NetPlayer::RecordDeath(iVar1,param_1);
  return;
}
