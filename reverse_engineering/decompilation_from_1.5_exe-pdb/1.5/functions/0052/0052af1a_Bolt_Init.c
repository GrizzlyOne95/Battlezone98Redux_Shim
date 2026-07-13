/*
 * Entry: 0052af1a
 * Name: Bolt::Init
 * Namespace: Bolt
 * Signature: void Init(Bolt * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Bolt::Init(Bolt *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  uint *puVar1;
  VECTOR_3D VVar2;
  int iVar3;
  _OBJ76 *p_Var4;
  VECTOR_3D_LONG local_40;
  double local_28;
  double local_20;
  double local_18;
  VECTOR_3D local_10;
  
  Bullet::Init((Bullet *)this,param_1,param_2);
  iVar3 = this->_padding_;
  (this->origin).x = *(double *)(iVar3 + 0x48);
  (this->origin).y = *(double *)(iVar3 + 0x50);
  (this->origin).z = *(double *)(iVar3 + 0x58);
  send_it_anyways = 1;
  param_2 = *(_OBJ76 **)(this->_padding_ + 0x4c);
  iVar3 = this->_padding_;
  local_28 = ((VECTOR_3D_LONG *)(iVar3 + 0x48))->x;
  local_20 = *(double *)(iVar3 + 0x50);
  local_18 = *(double *)(iVar3 + 0x58);
  VVar2.x = (float)this->_padding_;
  VVar2.y = (float)this->_padding_;
  VVar2.z = (float)this->_padding_;
  iVar3 = Terrain_GetIntersection
                    (*(VECTOR_3D_LONG *)(iVar3 + 0x48),VVar2,(float *)&param_2,&local_10);
  local_40.x = (double)((float)param_2 * (float)this->_padding_ + (float)local_28);
  local_40.y = (double)((float)this->_padding_ * (float)param_2 + (float)local_20);
  local_40.z = (double)((float)this->_padding_ * (float)param_2 + (float)local_18);
  p_Var4 = Bullet::Collision((Bullet *)this,(float *)&param_2,&local_40,&local_10);
  *(double *)(this->_padding_ + 0x48) = local_40.x;
  *(double *)(this->_padding_ + 0x50) = local_40.y;
  *(double *)(this->_padding_ + 0x58) = local_40.z;
  if (p_Var4 == (_OBJ76 *)0x0) {
    if (iVar3 != 0) {
      (**(code **)(this->_padding_ + 0x14))(0,&local_10);
    }
  }
  else {
    (**(code **)(this->_padding_ + 0x14))(p_Var4->gameObj,&local_10);
  }
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 & 0xfffffdff;
  this->_padding_ = *(int *)(this->_padding_ + 0x80);
  return;
}
