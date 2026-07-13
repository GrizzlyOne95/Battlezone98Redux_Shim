/*
 * Entry: 0048a144
 * Name: DistributedObject::PermStateRead
 * Namespace: DistributedObject
 * Signature: void PermStateRead(DistributedObject * this, ushort param_1, ushort param_2, void * param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
DistributedObject::PermStateRead
          (DistributedObject *this,ushort param_1,ushort param_2,void *param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  
  if (this->activnet_id == 0xfa01) {
    this->activnet_id = param_1;
  }
  if ((*(byte *)((int)param_3 + 0x14) & 0x80) == 0) {
    if ((*(byte *)((int)param_3 + 1) & 3) != 0) {
      return;
    }
    iVar2 = param_4 - 0x1c;
    iVar1 = (int)param_3 + 0x1c;
  }
  else {
    if ((*(byte *)((int)param_3 + 1) & 3) != 0) {
      return;
    }
    iVar2 = param_4 - 0x15;
    iVar1 = (int)param_3 + 0x15;
  }
  (**(code **)(this->_padding_ + 0x48))(iVar1,iVar2);
  return;
}
