/*
 * Entry: 004a8156
 * Name: PowerPlant::Simulate
 * Namespace: PowerPlant
 * Signature: void Simulate(PowerPlant * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerPlant::Simulate(PowerPlant *this,float param_1)

{
  long lVar1;
  float fVar2;
  PowerPlant *local_8;
  
  local_8 = this;
  if (-1 < this->animHandle) {
    lVar1 = AnimObj_Status(this->animHandle,(tagANIMOBJ_ACTIVE_LIST **)&local_8);
    if ((lVar1 != 0) || (local_8->_padding_ != 1)) {
      AnimObj_Stop(this->animHandle);
      this->animHandle = -1;
      fVar2 = get_obj_radius((_OBJ76 *)this->_padding_,*(VECTOR_3D *)(this->_padding_ + 8));
      *(float *)(this->_padding_ + 0x14) = fVar2;
      GameObject::UpdatePosition((GameObject *)this);
    }
  }
  Building::Simulate((Building *)this,param_1);
  return;
}
