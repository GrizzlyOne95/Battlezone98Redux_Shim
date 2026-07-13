/*
 * Entry: 004877bf
 * Name: Craft::DamageAlloc
 * Namespace: Craft
 * Signature: bool DamageAlloc(Craft * this, DAMAGE * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Craft::DamageAlloc(Craft *this,DAMAGE *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  _OBJ76 *p_Var2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  Craft *pCVar8;
  bool bVar9;
  float *pfVar10;
  VECTOR_3D *pVVar11;
  int extraout_EAX;
  int iVar12;
  uint uVar13;
  uint uVar14;
  float fVar15;
  char cVar16;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  Craft *local_8;
  
  if ((param_1 != (DAMAGE *)0x0) && ((UserProfilePtr->playOption & 1) == 0)) {
    local_8 = this;
    GameObject::SetDamageFlags((GameObject *)(this[-1].smokeList + 4),param_1);
    GameObject::AdjustDamageValues((GameObject *)(this[-1].smokeList + 4),param_1);
    local_c = param_1->dmg_value;
    if (0.0 < local_c) {
      if ((GameObject *)(this[-1].smokeList + 4) == GameObject::userObject) {
        ColorFade::SetFade(&colorFade,local_c * 0.002,5.0,0xff,0,0);
      }
      p_Var2 = param_1->dmg_source;
      if ((p_Var2 != (_OBJ76 *)0x0) &&
         ((p_Var2->class_id == CLASS_ID_ORDNANCE || (p_Var2->class_id == CLASS_ID_EXPLOSION)))) {
        local_10 = Clamp((float)this->_padding_ * local_c,0.0,1.0);
        local_1c.x = (float)(p_Var2->transform).posit_x;
        local_1c.y = (float)(p_Var2->transform).posit_y;
        local_1c.z = (float)(p_Var2->transform).posit_z;
        pfVar10 = (float *)(**(code **)(this->_padding_ + 0xc))();
        local_34.x = *pfVar10 - local_1c.x;
        local_34.y = pfVar10[1] - local_1c.y;
        local_34.z = pfVar10[2] - local_1c.z;
        local_28.x = local_34.x;
        local_28.y = local_34.y;
        local_28.z = local_34.z;
        if (p_Var2->class_id == CLASS_ID_ORDNANCE) {
          if (local_8->_padding_ != 2) {
            local_40.x = (p_Var2->transform).front_x;
            local_40.y = (p_Var2->transform).front_y;
            local_40.z = (p_Var2->transform).front_z;
            VVar5.x = (p_Var2->transform).front_x;
            VVar5.y = (p_Var2->transform).front_y;
            VVar5.z = (p_Var2->transform).front_z;
            local_1c.x = local_40.x;
            local_1c.y = local_40.y;
            local_1c.z = local_40.z;
            pVVar11 = ScaleVector(&local_1c,local_10 * 10.0,VVar5);
            local_34.x = pVVar11->x;
            local_34.y = pVVar11->y;
            local_34.z = pVVar11->z;
            GameObject::AddVelocity((GameObject *)(local_8[-1].smokeList + 4),&local_34);
            if (5.0 < *(float *)(local_8->_padding_ + 0x14)) {
              local_10 = (local_10 / *(float *)(local_8->_padding_ + 0x14)) * 5.0;
            }
            pVVar11 = Cross_Product(&local_34,&local_28,&local_40);
            pCVar8 = local_8;
            local_40.x = pVVar11->x;
            local_40.y = pVVar11->y;
            local_40.z = pVVar11->z;
            pVVar11 = Vector_Unrotate(&local_34,&local_40,(MAT_3D *)(local_8->_padding_ + 0x20));
            VVar6.x = (float)pCVar8->_padding_;
            VVar6.y = (float)pCVar8->_padding_;
            VVar6.z = (float)pCVar8->_padding_;
            pVVar11 = AddMultVectors(&local_40,VVar6,local_10,*pVVar11);
            local_8->_padding_ = (int)pVVar11->x;
            local_8->_padding_ = (int)pVVar11->y;
            local_8->_padding_ = (int)pVVar11->z;
          }
          this = local_8;
          if (((byte)useD3D & 4) != 0) {
            _ftol2_sse();
            local_10 = (float)((int)(extraout_EAX + (extraout_EAX >> 0x1f & 0x1fU)) >> 5);
            if (9 < (int)local_10) {
              local_10 = 1.4013e-44;
            }
            this = local_8;
            if (0 < (int)local_10) {
              local_34.x = (float)(p_Var2->transform).posit_x;
              local_34.y = (float)(p_Var2->transform).posit_y;
              local_34.z = (float)(p_Var2->transform).posit_z;
              pVVar11 = Normalize_Vector(&local_1c,&local_28);
              VVar7.x = (float)local_8->_padding_;
              VVar7.y = (float)local_8->_padding_;
              VVar7.z = (float)local_8->_padding_;
              pVVar11 = AddMultVectors(&local_4c,VVar7,-5.0,*pVVar11);
              local_40.x = pVVar11->x;
              local_40.y = pVVar11->y;
              local_40.z = pVVar11->z;
              fVar15 = local_10;
              this = local_8;
              if (0 < (int)local_10) {
                do {
                  VVar3.y = local_34.y;
                  VVar3.x = local_34.x;
                  VVar3.z = local_34.z;
                  VVar4.y = local_40.y;
                  VVar4.x = local_40.x;
                  VVar4.z = local_40.z;
                  ChunkEffect::CreateChunklet(&chunkEffect,VVar3,VVar4,false);
                  fVar15 = (float)((int)fVar15 + -1);
                  this = local_8;
                } while (fVar15 != 0.0);
              }
            }
          }
        }
        else {
          this = local_8;
          if (local_8->_padding_ != 2) {
            pVVar11 = Normalize_Vector(&local_4c,&local_28);
            pVVar11 = ScaleVector(&local_4c,local_10 * 20.0,*pVVar11);
            local_40.x = pVVar11->x;
            local_40.y = pVVar11->y;
            local_40.z = pVVar11->z;
            GameObject::AddVelocity((GameObject *)(local_8[-1].smokeList + 4),&local_40);
            this = local_8;
          }
        }
      }
      bVar9 = DistributedObject::IsRemote((DistributedObject *)this);
      if (!bVar9) {
        bVar9 = DistributedObject::IsLocal((DistributedObject *)this);
        if ((bVar9) && ((param_1->field_0x8 & 0x20) != 0)) {
          local_c = local_c * 7.0 * 0.16666667;
        }
        (**(code **)(this->_padding_ + 0x28))(-local_c);
        if ((float)this->_padding_ < 0.0) {
          if ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0) {
            puVar1 = (uint *)(this->_padding_ + 0x14);
            *puVar1 = *puVar1 | 0x200;
            iVar12 = Net_IsNetGame();
            if ((iVar12 != 0) && (iVar12 = (**(code **)(this->_padding_ + 4))(), iVar12 != 0)) {
              DistributedObject::RecordDeath
                        ((DistributedObject *)this,*(ushort *)&param_1->field_0x8 >> 6 & 0xf);
              uVar14 = (uint)((GameObject *)(this[-1].smokeList + 4) == GameObject::userObject);
              uVar13 = *(ushort *)&param_1->field_0x8 >> 6 & 0xf;
              cVar16 = 'C';
              iVar12 = (**(code **)(this->_padding_ + 4))();
              KillMessage(iVar12,uVar13,cVar16,uVar14);
            }
          }
          return true;
        }
      }
    }
  }
  return false;
}
