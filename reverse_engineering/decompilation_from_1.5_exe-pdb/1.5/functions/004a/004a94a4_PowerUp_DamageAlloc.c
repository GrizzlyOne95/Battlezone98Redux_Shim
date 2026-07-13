/*
 * Entry: 004a94a4
 * Name: PowerUp::DamageAlloc
 * Namespace: PowerUp
 * Signature: bool DamageAlloc(PowerUp * this, DAMAGE * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PowerUp::DamageAlloc(PowerUp *this,DAMAGE *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  _OBJ76 *p_Var2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  bool bVar6;
  int extraout_EAX;
  float *pfVar7;
  VECTOR_3D *pVVar8;
  VECTOR_3D local_40;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  if ((param_1 != (DAMAGE *)0x0) && ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0)) {
    GameObject::SetDamageFlags((GameObject *)&this[-1]._padding_,param_1);
    bVar6 = DistributedObject::IsRemote((DistributedObject *)this);
    if (!bVar6) {
      (**(code **)(this->_padding_ + 0x28))(-param_1->dmg_value);
      if (((((byte)useD3D & 4) != 0) && (p_Var2 = param_1->dmg_source, p_Var2 != (_OBJ76 *)0x0)) &&
         (p_Var2->class_id == CLASS_ID_ORDNANCE)) {
        _ftol2_sse();
        param_1 = (DAMAGE *)((int)(extraout_EAX + (extraout_EAX >> 0x1f & 0x1fU)) >> 5);
        if (9 < (int)param_1) {
          param_1 = (DAMAGE *)0xa;
        }
        if (0 < (int)param_1) {
          local_34 = (float)(p_Var2->transform).posit_x;
          local_30 = (float)(p_Var2->transform).posit_y;
          local_2c = (float)(p_Var2->transform).posit_z;
          local_10.x = (float)(p_Var2->transform).posit_x;
          local_10.y = (float)(p_Var2->transform).posit_y;
          local_10.z = (float)(p_Var2->transform).posit_z;
          pfVar7 = (float *)(**(code **)(this->_padding_ + 0xc))();
          local_28 = *pfVar7 - local_10.x;
          local_24 = pfVar7[1] - local_10.y;
          local_20 = pfVar7[2] - local_10.z;
          local_1c.x = local_28;
          local_1c.y = local_24;
          local_1c.z = local_20;
          pVVar8 = Normalize_Vector(&local_10,&local_1c);
          VVar5.x = (float)this->_padding_;
          VVar5.y = (float)this->_padding_;
          VVar5.z = (float)this->_padding_;
          pVVar8 = AddMultVectors(&local_40,VVar5,-5.0,*pVVar8);
          local_28 = pVVar8->x;
          local_24 = pVVar8->y;
          local_20 = pVVar8->z;
          if (0 < (int)param_1) {
            do {
              VVar3.y = local_30;
              VVar3.x = local_34;
              VVar3.z = local_2c;
              VVar4.y = local_24;
              VVar4.x = local_28;
              VVar4.z = local_20;
              ChunkEffect::CreateChunklet(&chunkEffect,VVar3,VVar4,false);
              param_1 = (DAMAGE *)((int)&param_1[-1].dmg_value + 3);
            } while (param_1 != (DAMAGE *)0x0);
          }
        }
      }
      if ((float)this->_padding_ < 0.0) {
        puVar1 = (uint *)(this->_padding_ + 0x14);
        *puVar1 = *puVar1 | 0x1000000;
        return true;
      }
    }
  }
  return false;
}
