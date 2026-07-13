/*
 * Entry: 0053f9cf
 * Name: WeaponMine::Simulate
 * Namespace: WeaponMine
 * Signature: void Simulate(WeaponMine * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponMine::Simulate(WeaponMine *this,float param_1)

{
  Weapon *pWVar1;
  VECTOR_3D_LONG VVar2;
  VECTOR_3D VVar3;
  bool bVar4;
  char cVar5;
  Craft **ppCVar6;
  float *pfVar7;
  MAT_3D *pMVar8;
  MAT_3D *pMVar9;
  int iVar10;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar11;
  MAT_3D local_190;
  MAT_3D local_150;
  MAT_3D local_110;
  MAT_3D local_d0;
  undefined1 local_90 [12];
  float local_84;
  float fStack_80;
  float fStack_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_3c;
  float local_34;
  float local_30;
  float local_2c;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_28;
  float local_20;
  float local_1c;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_18;
  Craft *local_10;
  Craft *local_c;
  float local_8;
  
  bVar4 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if (!bVar4) {
    cVar5 = (**(code **)(this->weapon->_padding_ + 4))();
    if (cVar5 == '\0') {
      this->_padding_ = 0;
    }
    else {
      local_8 = *(float *)(this->_padding_ + 0x168);
      local_10 = (Craft *)0x0;
      local_8 = local_8 * local_8;
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&local_18,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
LAB_0053fb75:
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&local_28,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
      bVar4 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                        (&local_18,&local_28);
      if (!bVar4) {
        local_3c._padding_ = local_18._padding_;
        local_3c._Myptr = local_18._Myptr;
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_18);
        ppCVar6 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*
                            (&local_3c);
        local_c = *ppCVar6;
        bVar4 = GameObject::FriendP((GameObject *)this,(GameObject *)local_c);
        if (!bVar4) {
          local_6c = (float)this->_padding_;
          local_68 = (float)this->_padding_;
          local_64 = (float)this->_padding_;
          pfVar7 = (float *)(**(code **)(local_c->_padding_ + 0xc))();
          local_48 = *pfVar7;
          local_44 = pfVar7[1];
          local_40 = pfVar7[2];
          local_1c = *(float *)(this->_padding_ + 0x16c) * (local_40 - local_64) *
                     (local_40 - local_64) + (local_44 - local_68) * (local_44 - local_68) +
                     (local_48 - local_6c) * (local_48 - local_6c);
          if (local_1c < local_8) {
            local_60 = (float)this->_padding_;
            local_5c = (float)this->_padding_;
            local_58 = (float)this->_padding_;
            pfVar7 = (float *)(**(code **)(this->weapon->_padding_ + 0x2c))(local_90,local_c);
            local_54 = *pfVar7;
            local_50 = pfVar7[1];
            local_4c = pfVar7[2];
            local_34 = local_54 - local_60;
            local_30 = local_50 - local_5c;
            local_2c = local_4c - local_58;
            if (*(char *)(this->_padding_ + 0x174) != '\0') {
              local_20 = 1.0;
              local_78 = (float)this->_padding_;
              local_74 = (float)this->_padding_;
              local_70 = (float)this->_padding_;
              VVar2.y = (double)local_74;
              VVar2.x = (double)local_78;
              VVar2.z._0_4_ = SUB84((double)local_70,0);
              VVar2.z._4_4_ = (int)((ulonglong)(double)local_70 >> 0x20);
              VVar3.y = local_30;
              VVar3.x = local_34;
              VVar3.z = local_2c;
              iVar10 = Terrain_GetIntersection(VVar2,VVar3,&local_20,(VECTOR_3D *)0x0);
              if (iVar10 != 0) goto LAB_0053fb75;
            }
            local_8 = local_1c;
            local_84 = local_34;
            fStack_80 = local_30;
            fStack_7c = local_2c;
            local_10 = local_c;
          }
        }
        goto LAB_0053fb75;
      }
      GameObject::SetTarget((GameObject *)this,(GameObject *)local_10);
      if (local_10 != (Craft *)0x0) {
        pMVar9 = &local_d0;
        pMVar8 = Build_Directinal_Matrix(pMVar9,unaff_EDI,unaff_ESI);
        pMVar11 = &local_110;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar11->right_x = pMVar8->right_x;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
          pMVar11 = (MAT_3D *)&pMVar11->right_y;
        }
        pMVar9 = Matrix_Inverse(&local_d0,pMVar9);
        pMVar8 = &local_150;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar8->right_x = pMVar9->right_x;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        pMVar9 = Matrix_Multiply(&local_190,&local_110,&local_150);
        pWVar1 = this->weapon;
        pMVar8 = &local_d0;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar8->right_x = pMVar9->right_x;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        pMVar9 = &local_d0;
        pMVar8 = &pWVar1->obj->transform;
        for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
          pMVar8->right_x = pMVar9->right_x;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        if ((*(char *)(this->_padding_ + 0x174) == '\0') ||
           (bVar4 = MayHitFriends((GameObject *)this,local_8,0.3,1.0), !bVar4)) {
          (**(code **)(this->weapon->_padding_ + 8))();
        }
      }
    }
  }
  Mine::Simulate((Mine *)this,param_1);
  return;
}
