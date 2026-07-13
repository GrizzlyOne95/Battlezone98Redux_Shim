/*
 * Entry: 0053d31b
 * Name: Torpedo::RegCollision
 * Namespace: Torpedo
 * Signature: bool RegCollision(Torpedo * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
Torpedo::RegCollision(Torpedo *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  uint *puVar1;
  ushort uVar2;
  int iVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  short sVar6;
  GameObject *pGVar7;
  _OBJ76 *p_Var8;
  ulong uVar9;
  VECTOR_3D *pVVar10;
  GameObject *pGVar11;
  float local_3c;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  int *local_8;
  
  pGVar7 = GameObject::GetObj(this->_padding_);
  if (((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) && (pGVar7 != (GameObject *)0x0)) {
    local_8 = &pGVar7->_padding_;
    p_Var8 = (_OBJ76 *)(**(code **)(*local_8 + 0x30))();
    if (param_1 == p_Var8) {
      if (*(float *)(this->_padding_ + 400) != 0.0) {
        local_38.y = 0.0;
        local_38.z = 0.0;
        local_3c = (float)this->_padding_;
        local_38.x = local_3c;
        sVar6 = (**(code **)(this->_padding_ + 4))();
        uVar2 = SUB42(local_38.y,0) ^ (sVar6 << 6 ^ SUB42(local_38.y,0)) & 0x3c0;
        local_38.y = (float)CONCAT22(local_38.y._2_2_,
                                     uVar2 ^ (*(ushort *)(this->_padding_ + 0x194) ^ uVar2) & 0xf);
        local_38.z = *(float *)(this->_padding_ + 400);
        iVar3 = this->_padding_;
        local_2c.x = *(float *)(iVar3 + 0x38);
        local_2c.y = *(float *)(iVar3 + 0x3c);
        local_2c.z = *(float *)(iVar3 + 0x40);
        local_14 = local_2c.x;
        local_10 = local_2c.y;
        local_c = local_2c.z;
        (**(code **)(*local_8 + 0x38))(&local_3c,&local_2c);
      }
      puVar1 = (uint *)(this->_padding_ + 0x14);
      *puVar1 = *puVar1 | 0x200;
      *(undefined4 *)(this->_padding_ + 0x108) = 0;
    }
  }
  uVar9 = Get_Time_Long();
  if (uVar9 < this->_padding_ + 1000U) {
    pGVar7 = GameObject::GetObj(this->_padding_);
    if (param_1 == (_OBJ76 *)0x0) {
      pGVar11 = (GameObject *)0x0;
    }
    else {
      pGVar11 = param_1->gameObj;
    }
    if (pGVar7 == pGVar11) {
      return false;
    }
  }
  VVar4.x = (float)this->_padding_;
  VVar4.y = (float)this->_padding_;
  VVar4.z = (float)this->_padding_;
  pVVar10 = CombineVectors(&local_2c,0.5,VVar4,
                           -((param_2->normal).x * (float)this->_padding_ +
                            (float)this->_padding_ * (param_2->normal).y +
                            (float)this->_padding_ * (param_2->normal).z),param_2->normal);
  this->_padding_ = (int)pVVar10->x;
  this->_padding_ = (int)pVVar10->y;
  this->_padding_ = (int)pVVar10->z;
  iVar3 = this->_padding_;
  local_20.x = (param_2->point).x;
  local_20.y = (param_2->point).y;
  local_20.z = (param_2->point).z;
  local_2c.x = local_20.x - *(float *)(iVar3 + 8);
  local_2c.y = local_20.y - *(float *)(iVar3 + 0xc);
  local_2c.z = local_20.z - *(float *)(iVar3 + 0x10);
  local_14 = local_2c.x;
  local_10 = local_2c.y;
  local_c = local_2c.z;
  pVVar10 = Vector_Unrotate(&local_38,&param_2->vel,(MAT_3D *)(this->_padding_ + 0x20));
  local_20.x = pVVar10->x;
  local_20.y = pVVar10->y;
  local_20.z = pVVar10->z;
  pVVar10 = Cross_Product(&local_38,&local_20,&local_2c);
  VVar5.x = (float)this->_padding_;
  VVar5.y = (float)this->_padding_;
  VVar5.z = (float)this->_padding_;
  pVVar10 = AddMultVectors(&local_2c,VVar5,
                           0.2 / (local_14 * local_14 + local_10 * local_10 + local_c * local_c),
                           *pVVar10);
  this->_padding_ = (int)pVVar10->x;
  this->_padding_ = (int)pVVar10->y;
  this->_padding_ = (int)pVVar10->z;
  return true;
}
