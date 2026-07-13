/*
 * Entry: 0048ed50
 * Name: DistributedObject::DistributedObject
 * Namespace: DistributedObject
 * Signature: DistributedObject * DistributedObject(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject * __thiscall DistributedObject::DistributedObject(DistributedObject *this)

{
  DistributedObject *local_8;
  
  this->last_send_time = 0.0;
  this->flast_received_time = 0.0;
  this->recycle = false;
  this->create_new_craft = false;
  this->last_health_ratio = 1.0;
  this->object_type = '\0';
  this->dirty = false;
  this->net_user = false;
  this->net_dt = 0.0;
  this->activnet_id = 0xfa01;
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::push_back
            (&allDistributedObjectList,&local_8);
  return this;
}
