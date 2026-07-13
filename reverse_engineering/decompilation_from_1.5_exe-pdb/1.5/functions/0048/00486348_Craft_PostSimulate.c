/*
 * Entry: 00486348
 * Name: Craft::PostSimulate
 * Namespace: Craft
 * Signature: void PostSimulate(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::PostSimulate(Craft *this,float param_1)

{
  float fVar1;
  float fVar2;
  VECTOR_3D VVar3;
  int iVar4;
  MAT_3D *pMVar5;
  uint uVar6;
  int iVar7;
  MAT_3D *pMVar8;
  float *pfVar9;
  ushort uVar10;
  MAT_3D local_f8;
  float local_b8 [10];
  double local_90;
  double local_88;
  double local_80;
  MAT_3D local_78;
  float local_38;
  float local_34;
  float local_30;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  int local_8;
  
  if (((this->vhcl->flags & 0x100) != 0) && ((*(uint *)(this->_padding_ + 0x14) & 0x600) == 0)) {
    iVar4 = UserPref_arcadeMode();
    if (iVar4 == 0) {
      fVar1 = this->smokeTimer + param_1;
      this->smokeTimer = fVar1;
      uVar10 = (ushort)(0.0 < fVar1) << 8 | (ushort)NAN(fVar1) << 10;
      while ((POPCOUNT((char)(uVar10 >> 8)) & 1U) != 0) {
        VVar3.x = (float)this->_padding_;
        VVar3.y = (float)this->_padding_;
        VVar3.z = (float)this->_padding_;
        pMVar5 = Spinner(&local_f8,(MAT_3D *)(this->_padding_ + 0x20),VVar3,-this->smokeTimer);
        fVar1 = (float)this->_padding_;
        fVar2 = this->smokeTimer;
        iVar4 = this->smokeCount;
        pMVar8 = &local_78;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          pMVar8->right_x = pMVar5->right_x;
          pMVar5 = (MAT_3D *)&pMVar5->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        local_78.posit_x = (double)((float)local_78.posit_x - fVar1 * fVar2);
        local_78.posit_y =
             (double)((float)local_78.posit_y - this->smokeTimer * (float)this->_padding_);
        local_78.posit_z =
             (double)((float)local_78.posit_z - (float)this->_padding_ * this->smokeTimer);
        if (iVar4 == 0) {
          iVar4 = this->_padding_;
          local_2c.x = (*(float *)(iVar4 + 0xe4) + *(float *)(iVar4 + 0xd8)) * 0.5;
          local_2c.y = (*(float *)(iVar4 + 0xe8) + *(float *)(iVar4 + 0xdc)) * 0.5;
          local_2c.z = *(float *)(iVar4 + 0xe0);
          Vector_Transform(&local_20,&local_2c,1,&local_78);
          uVar6 = (Rand_Counter + 1U & 0xff) + 1;
          local_14.x = *(float *)(&DAT_00c9021c + uVar6 * 4) + (float)this->_padding_ * 0.5;
          uVar6 = (uVar6 & 0xff) + 1;
          Rand_Counter = uVar6 & 0xff;
          local_14.y = (float)this->_padding_ * 0.5 + *(float *)(&DAT_00c9021c + uVar6 * 4) + 3.0;
          local_14.z = (float)this->_padding_ * 0.5 + Pseudo_Rand_Number[Rand_Counter];
          SmokeEffect::AddSmoke
                    (&smokeEffect,this->smokeEmitter,&local_20,&local_14,this->smokeTimer);
        }
        else {
          local_8 = 0;
          if (0 < iVar4) {
            param_1 = (float)this->smokeList;
            do {
              pMVar5 = obj_rel_parent_matrix
                                 (&local_f8,*(_OBJ76 **)param_1,(_OBJ76 *)this->_padding_);
              pfVar9 = local_b8;
              for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
                *pfVar9 = pMVar5->right_x;
                pMVar5 = (MAT_3D *)&pMVar5->right_y;
                pfVar9 = pfVar9 + 1;
              }
              local_38 = (float)local_90;
              local_34 = (float)local_88;
              local_30 = (float)local_80;
              local_20.x = local_38;
              local_20.y = local_34;
              local_20.z = local_30;
              Vector_Transform(&local_20,&local_20,1,&local_78);
              uVar6 = (Rand_Counter + 1U & 0xff) + 1;
              local_14.x = *(float *)(&DAT_00c9021c + uVar6 * 4) + (float)this->_padding_ * 0.5;
              uVar6 = (uVar6 & 0xff) + 1;
              Rand_Counter = uVar6 & 0xff;
              local_14.y = (float)this->_padding_ * 0.5 + *(float *)(&DAT_00c9021c + uVar6 * 4) +
                           3.0;
              local_14.z = (float)this->_padding_ * 0.5 + Pseudo_Rand_Number[Rand_Counter];
              SmokeEffect::AddSmoke
                        (&smokeEffect,this->smokeEmitter,&local_20,&local_14,this->smokeTimer);
              local_8 = local_8 + 1;
              param_1 = (float)((int)param_1 + 4);
            } while (local_8 < this->smokeCount);
          }
        }
        this->smokeTimer = this->smokeTimer - 0.1;
        uVar10 = (ushort)(0.0 < this->smokeTimer) << 8 | (ushort)NAN(this->smokeTimer) << 10;
      }
    }
  }
  return;
}
