/*
 * Entry: 004a91e7
 * Name: PowerUp::RegCollision
 * Namespace: PowerUp
 * Signature: bool RegCollision(PowerUp * this, _OBJ76 * param_1, CLSN_INFO * param_2, CLSN_INFO * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
PowerUp::RegCollision(PowerUp *this,_OBJ76 *param_1,CLSN_INFO *param_2,CLSN_INFO *param_3)

{
  int *this_00;
  uint uVar1;
  OBJECT_CLASS_T OVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  bool bVar5;
  char cVar6;
  GameObject *pGVar7;
  VEHICLE *pVVar8;
  VECTOR_3D *pVVar9;
  int iVar10;
  int *this_01;
  CLSN_INFO *pCVar11;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  GameObject *local_8;
  
  if (param_1 == (_OBJ76 *)0x0) {
    local_8 = (GameObject *)0x0;
  }
  else {
    local_8 = param_1->gameObj;
  }
  uVar1 = this->vhcl->flags;
  if (((uVar1 & 4) == 0) || ((uVar1 & 8) == 0)) {
LAB_004a9234:
    if (((this->vhcl->flags & 4) != 0) && (param_1->class_id == CLASS_ID_POWERUP)) {
      pVVar8 = get_obj_vhcl(param_1);
      if ((pVVar8->flags & 4) != 0) goto LAB_004a922d;
    }
    VVar3.z._2_2_ = (short)((uint)this->_padding_ >> 0x10);
    VVar3._0_10_ = *(unkbyte10 *)&this->_padding_;
    pVVar9 = CombineVectors(&local_2c,0.5,VVar3,
                            -((float)this->_padding_ * (param_2->normal).x +
                             (float)this->_padding_ * (param_2->normal).y +
                             (float)this->_padding_ * (param_2->normal).z),param_2->normal);
    this->_padding_ = (int)pVVar9->x;
    this->_padding_ = (int)pVVar9->y;
    this->_padding_ = (int)pVVar9->z;
    iVar10 = this->_padding_;
    local_20.x = (param_2->point).x;
    local_20.y = (param_2->point).y;
    local_20.z = (param_2->point).z;
    local_2c.x = local_20.x - *(float *)(iVar10 + 8);
    local_2c.y = local_20.y - *(float *)(iVar10 + 0xc);
    local_2c.z = local_20.z - *(float *)(iVar10 + 0x10);
    local_14 = local_2c.x;
    local_10 = local_2c.y;
    local_c = local_2c.z;
    pVVar9 = Vector_Unrotate(&local_38,&param_2->vel,(MAT_3D *)(this->_padding_ + 0x20));
    local_20.x = pVVar9->x;
    local_20.y = pVVar9->y;
    local_20.z = pVVar9->z;
    pVVar9 = Cross_Product(&local_38,&local_20,&local_2c);
    VVar4.z._2_2_ = (short)((uint)this->_padding_ >> 0x10);
    VVar4._0_10_ = *(unkbyte10 *)&this->_padding_;
    pVVar9 = AddMultVectors(&local_2c,VVar4,
                            0.2 / (local_14 * local_14 + local_10 * local_10 + local_c * local_c),
                            *pVVar9);
    pGVar7 = local_8;
    this->_padding_ = (int)pVVar9->x;
    this->_padding_ = (int)pVVar9->y;
    this->_padding_ = (int)pVVar9->z;
    if ((((*(uint *)(this->_padding_ + 0x14) & 0x1000200) == 0) &&
        (((OVar2 = param_1->class_id, OVar2 == CLASS_ID_HELICOPTER || (OVar2 == CLASS_ID_VEHICLE))
         || (OVar2 == CLASS_ID_STRUCTURE1)))) && (local_8 != (GameObject *)0x0)) {
      this_00 = &local_8->_padding_;
      bVar5 = DistributedObject::IsRemote((DistributedObject *)this_00);
      if (!bVar5) {
        cVar6 = (**(code **)(this->_padding_ + 0x5c))(pGVar7);
        if (cVar6 != '\0') {
          bVar5 = Net::IsNetGame();
          if (bVar5) {
            this_01 = &this->_padding_;
            iVar10 = (**(code **)*this_01)();
            if (*(int *)(iVar10 + 0x20) != 0x414d4d4f) {
              iVar10 = (**(code **)*this_01)();
              if (*(int *)(iVar10 + 0x20) != 0x524b4954) {
                DistributedObject::packet_buffer[0] = 'R';
                DistributedObject::packet_buffer[1] = 'G';
                DistributedObject::packet_buffer._2_4_ =
                     DistributedObject::GetID((DistributedObject *)this_01);
                DistributedObject::packet_buffer._6_4_ =
                     DistributedObject::GetID((DistributedObject *)this_00);
                Net::Send(Net::dp,DistributedObject::global_activnet_id,0,1,
                          DistributedObject::packet_buffer,10);
              }
            }
            DistributedObject::RemoteDelete((DistributedObject *)this_01);
            goto LAB_004a922d;
          }
        }
      }
    }
    pCVar11 = &this->vhcl->clsn_info;
    for (iVar10 = 0x1e; iVar10 != 0; iVar10 = iVar10 + -1) {
      pCVar11->collided = param_2->collided;
      param_2 = (CLSN_INFO *)&param_2->obj;
      pCVar11 = (CLSN_INFO *)&pCVar11->obj;
    }
    bVar5 = true;
  }
  else {
    pGVar7 = GameObject::GetObj(this->_padding_);
    if (local_8 != pGVar7) goto LAB_004a9234;
LAB_004a922d:
    bVar5 = false;
  }
  return bVar5;
}
