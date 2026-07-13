/*
 * Entry: 0048b003
 * Name: DistributedObject::BroadCastGrabObject
 * Namespace: DistributedObject
 * Signature: void BroadCastGrabObject(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::BroadCastGrabObject(DistributedObject *this)

{
  DistributedObject *pDVar1;
  int iVar2;
  float fVar3;
  
  packet_buffer[0] = 'P';
  packet_buffer[1] = 'O';
  packet_buffer._2_4_ = Get_Time();
  packet_buffer[6] = '\x06';
  if (GameObject::userObject == (GameObject *)0x0) {
    pDVar1 = (DistributedObject *)0x0;
  }
  else {
    pDVar1 = (DistributedObject *)&GameObject::userObject->_padding_;
  }
  packet_buffer[7] = (this == pDVar1) << 7 | 2;
  packet_buffer._8_4_ = this->dwLocalID;
  if (dp != (dp_s *)0x0) {
    iVar2 = Net::Send(dp,global_activnet_id,0,1,packet_buffer,0xc);
    if (iVar2 == 0) {
      fVar3 = Get_TimeLocal();
      this->last_send_time = fVar3;
    }
  }
  return;
}
