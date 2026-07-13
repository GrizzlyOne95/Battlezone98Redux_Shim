/*
 * Entry: 00482e4a
 * Name: Building::DamageAlloc
 * Namespace: Building
 * Signature: bool DamageAlloc(Building * this, DAMAGE * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Building::DamageAlloc(Building *this,DAMAGE *param_1,VECTOR_3D *param_2)

{
  _OBJ76 *p_Var1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  undefined1 uVar5;
  bool bVar6;
  int iVar7;
  int extraout_EAX;
  float *pfVar8;
  VECTOR_3D *pVVar9;
  uint uVar10;
  char cVar11;
  uint uVar12;
  VECTOR_3D local_40;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  iVar7 = this->_padding_;
  if (this->_padding_ == iVar7) {
    if ((param_1 != (DAMAGE *)0x0) && ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0)) {
      GameObject::SetDamageFlags((GameObject *)&this[-1]._padding_,param_1);
      GameObject::AdjustDamageValues((GameObject *)&this[-1]._padding_,param_1);
      bVar6 = DistributedObject::IsRemote((DistributedObject *)this);
      if (!bVar6) {
        (**(code **)(this->_padding_ + 0x28))(-param_1->dmg_value);
        if (((((byte)useD3D & 4) != 0) && (p_Var1 = param_1->dmg_source, p_Var1 != (_OBJ76 *)0x0))
           && (p_Var1->class_id == CLASS_ID_ORDNANCE)) {
          _ftol2_sse();
          param_2 = (VECTOR_3D *)((int)(extraout_EAX + (extraout_EAX >> 0x1f & 0x1fU)) >> 5);
          if (9 < (int)param_2) {
            param_2 = (VECTOR_3D *)0xa;
          }
          if (0 < (int)param_2) {
            local_34 = (float)(p_Var1->transform).posit_x;
            local_30 = (float)(p_Var1->transform).posit_y;
            local_2c = (float)(p_Var1->transform).posit_z;
            local_10.x = (float)(p_Var1->transform).posit_x;
            local_10.y = (float)(p_Var1->transform).posit_y;
            local_10.z = (float)(p_Var1->transform).posit_z;
            pfVar8 = (float *)(**(code **)(this->_padding_ + 0xc))();
            local_28 = *pfVar8 - local_10.x;
            local_24 = pfVar8[1] - local_10.y;
            local_20 = pfVar8[2] - local_10.z;
            local_1c.x = local_28;
            local_1c.y = local_24;
            local_1c.z = local_20;
            pVVar9 = Normalize_Vector(&local_10,&local_1c);
            VVar4.x = (float)this->_padding_;
            VVar4.y = (float)this->_padding_;
            VVar4.z = (float)this->_padding_;
            pVVar9 = AddMultVectors(&local_40,VVar4,-5.0,*pVVar9);
            local_28 = pVVar9->x;
            local_24 = pVVar9->y;
            local_20 = pVVar9->z;
            if (0 < (int)param_2) {
              do {
                VVar2.y = local_30;
                VVar2.x = local_34;
                VVar2.z = local_2c;
                VVar3.y = local_24;
                VVar3.x = local_28;
                VVar3.z = local_20;
                ChunkEffect::CreateChunklet(&chunkEffect,VVar2,VVar3,false);
                param_2 = (VECTOR_3D *)((int)&param_2[-1].z + 3);
              } while (param_2 != (VECTOR_3D *)0x0);
            }
          }
        }
        if ((float)this->_padding_ < 0.0) {
          if ((((_OBJ76 *)this->_padding_)->flags & 0x200) == 0) {
            obj_set_flag((_OBJ76 *)this->_padding_,0x1000200);
            iVar7 = Net_IsNetGame();
            if (((iVar7 != 0) && (iVar7 = (**(code **)(this->_padding_ + 4))(), iVar7 != 0)) &&
               (*(int *)(this->_padding_ + 0x28) == 2)) {
              DistributedObject::RecordDeath
                        ((DistributedObject *)this,*(ushort *)&param_1->field_0x8 >> 6 & 0xf);
              uVar12 = (uint)((GameObject *)&this[-1]._padding_ == GameObject::userObject);
              uVar10 = *(ushort *)&param_1->field_0x8 >> 6 & 0xf;
              cVar11 = 'B';
              iVar7 = (**(code **)(this->_padding_ + 4))();
              KillMessage(iVar7,uVar10,cVar11,uVar12);
            }
          }
          return true;
        }
      }
    }
    uVar5 = 0;
  }
  else {
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = *(int *)(iVar7 + 0xb4);
    }
    uVar5 = (**(code **)(*(int *)(iVar7 + 0x20) + 0x38))(param_1,param_2);
  }
  return (bool)uVar5;
}
