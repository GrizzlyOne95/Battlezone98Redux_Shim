/*
 * Entry: 00482b10
 * Name: Building::UnPackPermState
 * Namespace: Building
 * Signature: void UnPackPermState(Building * this, void * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Building::UnPackPermState(Building *this,void *param_1,uint param_2)

{
  float fVar1;
  
  fVar1 = *(float *)param_1;
  this->_padding_ = (int)fVar1;
  if (fVar1 < 0.0) {
    obj_set_flag((_OBJ76 *)this->_padding_,0x1000080);
    DistributedObject::SetLocal((DistributedObject *)this);
  }
  return;
}
