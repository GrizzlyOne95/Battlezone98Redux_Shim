/*
 * Entry: 0048a0d4
 * Name: DistributedObject::SendCommand
 * Namespace: DistributedObject
 * Signature: void SendCommand(DistributedObject * this, AiCommand param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
DistributedObject::SendCommand(DistributedObject *this,AiCommand param_1,VECTOR_3D *param_2)

{
  if (((this->object_type == '\x02') && (dp != (dp_s *)0x0)) && (this->activnet_id != 0xfa01)) {
    packet_buffer[0] = 'C';
    packet_buffer[1] = 'O';
    packet_buffer._2_4_ = this->dwLocalID;
    packet_buffer._6_4_ = param_1;
    packet_buffer._10_4_ = param_2->x;
    packet_buffer._14_4_ = param_2->y;
    packet_buffer._18_4_ = param_2->z;
    Net::Send(dp,global_activnet_id,this->activnet_id,1,packet_buffer,0x16);
  }
  return;
}
