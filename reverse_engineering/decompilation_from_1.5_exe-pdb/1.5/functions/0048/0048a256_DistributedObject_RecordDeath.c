/*
 * Entry: 0048a256
 * Name: DistributedObject::RecordDeath
 * Namespace: DistributedObject
 * Signature: void RecordDeath(DistributedObject * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::RecordDeath(DistributedObject *this,GameObject *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == (GameObject *)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (**(code **)(param_1->_padding_ + 4))();
  }
  iVar2 = (**(code **)(this->_padding_ + 4))();
  NetPlayer::RecordDeath(iVar2,iVar1);
  return;
}
