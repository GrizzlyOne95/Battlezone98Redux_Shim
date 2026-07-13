/*
 * Entry: 0047dfb3
 * Name: APC::Simulate
 * Namespace: APC
 * Signature: void Simulate(APC * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall APC::Simulate(APC *this,float param_1)

{
  VECTOR_3D VVar1;
  bool bVar2;
  GameObject *pGVar3;
  VECTOR_3D *pVVar4;
  AiMission *pAVar5;
  GameObject *pGVar6;
  int *piVar7;
  VECTOR_3D *pVVar8;
  GameObject **ppGVar9;
  int iVar10;
  float *pfVar11;
  MAT_3D *pMVar12;
  float fVar13;
  int iVar14;
  int iVar15;
  _OBJ76 *p_Var16;
  char *pcVar17;
  MAT_3D local_90;
  VECTOR_3D local_50;
  float local_44;
  float local_40;
  float local_3c;
  VECTOR_3D local_38;
  undefined1 local_2c [8];
  float local_24;
  VECTOR_3D local_20;
  undefined1 local_14 [8];
  float local_c;
  GameObject *local_8;
  
  iVar10 = this->_padding_;
  if (iVar10 != 0) {
    if (iVar10 == 1) {
      if (0 < this->soldierCount) {
        fVar13 = this->soldierDelay - param_1;
        this->soldierDelay = fVar13;
        if (fVar13 <= 0.0) {
          this->soldierDelay = fVar13 + *(float *)(this->_padding_ + 0x3d0);
          bVar2 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
          if (!bVar2) {
            local_8 = *(GameObject **)(this->_padding_ + 0x3c8);
            iVar10 = this->_padding_;
            local_2c._0_4_ = (*(float *)(iVar10 + 0xe4) + *(float *)(iVar10 + 0xd8)) * 0.5;
            local_2c._4_4_ = (*(float *)(iVar10 + 0xe8) + *(float *)(iVar10 + 0xdc)) * 0.5;
            local_24 = *(float *)(iVar10 + 0xe0);
            Vector_Transform((VECTOR_3D *)local_14,(VECTOR_3D *)local_2c,1,(MAT_3D *)(iVar10 + 0x20)
                            );
            pfVar11 = (float *)(this->_padding_ + 0x20);
            pMVar12 = &local_90;
            for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
              pMVar12->right_x = *pfVar11;
              pfVar11 = pfVar11 + 1;
              pMVar12 = (MAT_3D *)&pMVar12->right_y;
            }
            local_90.posit_x = (double)(float)local_14._0_4_;
            local_90.posit_y = (double)(float)local_14._4_4_;
            local_90.posit_z = (double)local_c;
            pcVar17 = (char *)0x0;
            iVar15 = -1;
            iVar14 = 0;
            iVar10 = (**(code **)(this->_padding_ + 4))();
            pGVar3 = GameObjectClass::Build
                               ((GameObjectClass *)local_8,&local_90,iVar10,iVar14,iVar15,pcVar17);
            local_8 = pGVar3;
            if (pGVar3 != (GameObject *)0x0) {
              iVar10 = Net_IsNetGame();
              if (iVar10 != 0) {
                DistributedObject::SetLocal((DistributedObject *)&pGVar3->_padding_);
              }
              local_20.x = 0.0;
              local_20.y = 5.0;
              local_20.z = 5.0;
              pVVar4 = Vector_Rotate(&local_50,&local_20,(MAT_3D *)(this->_padding_ + 0x20));
              pGVar3 = local_8;
              local_20.x = pVVar4->x;
              local_20.y = pVVar4->y;
              local_20.z = pVVar4->z;
              local_44 = local_20.x + (float)this->_padding_;
              local_40 = local_20.y + (float)this->_padding_;
              local_3c = local_20.z + (float)this->_padding_;
              local_38.x = local_44;
              local_38.y = local_40;
              local_38.z = local_3c;
              GameObject::SetVelocity(local_8,&local_38);
              pGVar6 = pGVar3;
              pAVar5 = AiMission::GetCurrent();
              AiProcess::Attach(pAVar5,pGVar6);
              if (this->_padding_ == 4) {
                pGVar6 = GameObjectHandle::GetObj(this->_padding_);
              }
              else {
                pGVar6 = GameObject::GetObj(this->_padding_);
              }
              if (pGVar6 != (GameObject *)0x0) {
                GameObject::SetCommand(pGVar3,CMD_ATTACK,pGVar6);
              }
              GameObject::SetOwner(pGVar3,(GameObject *)this);
            }
          }
          this->soldierCount = this->soldierCount + -1;
        }
        goto LAB_0047e50a;
      }
      this->reloadDelay = *(float *)(this->_padding_ + 0x3dc);
      this->_padding_ = 2;
      *(undefined4 *)(this->_padding_ + 0xe0) = 1;
      if ((*(byte *)(this->_padding_ + 0x14) & 0x30) == 0) goto LAB_0047e50a;
    }
    else if (iVar10 != 2) {
      if (iVar10 == 3) {
        this->_padding_ = 0;
      }
      goto LAB_0047e50a;
    }
    piVar7 = (int *)(this->_padding_ + 0xe0);
    if (*piVar7 != 0) {
      *piVar7 = 0;
      this->_padding_ = 3;
      DoAudioNew((char *)(this->_padding_ + 0x3ac),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
    }
    goto LAB_0047e50a;
  }
  piVar7 = (int *)(this->_padding_ + 0xe0);
  if (*piVar7 != 0) {
    *piVar7 = 0;
    if (this->soldierCount < 1) {
LAB_0047e2ed:
      p_Var16 = (_OBJ76 *)this->_padding_;
      pcVar17 = "mnu_buzz.wav";
    }
    else {
      if (this->_padding_ != 4) {
        pGVar6 = GameObject::GetObj(this->_padding_);
        pGVar3 = (GameObject *)GameObject::objectList;
        if (pGVar6 == (GameObject *)0x0) {
          local_8 = (GameObject *)GameObject::objectList;
          std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
          _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                    ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                     (local_14 + 4),GameObject::objectList->_Myfirst,
                     (_Container_base_aux *)GameObject::objectList);
          ppGVar9 = ((vector<GameObject_*,std::allocator<GameObject_*>_> *)pGVar3)->_Mylast;
          while( true ) {
            std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
            _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                      ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                       (local_2c + 4),ppGVar9,(_Container_base_aux *)pGVar3);
            bVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
                    operator==((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *
                               )(local_14 + 4),
                               (_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *
                               )(local_2c + 4));
            if (bVar2) break;
            ppGVar9 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
                      operator*((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                                 *)(local_14 + 4));
            pGVar3 = *ppGVar9;
            piVar7 = &pGVar3->_padding_;
            iVar10 = (**(code **)(*piVar7 + 4))();
            bVar2 = GameObject::EnemyP((GameObject *)this,iVar10);
            if ((bVar2) &&
               (bVar2 = GameObject::EnemyP((GameObject *)this,pGVar3->perceivedTeam), bVar2)) {
              pVVar4 = (VECTOR_3D *)(**(code **)(*piVar7 + 0xc))();
              VVar1.x = (float)this->_padding_;
              VVar1.y = (float)this->_padding_;
              VVar1.z = (float)this->_padding_;
              fVar13 = Dist3D_Squared(VVar1,*pVVar4);
              if (fVar13 < 5625.0) {
                bVar2 = true;
                goto LAB_0047e4aa;
              }
            }
            std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
                      ((_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> *)
                       (local_14 + 4));
            ppGVar9 = (GameObject **)local_8->_padding_;
            pGVar3 = local_8;
          }
        }
        else {
          iVar10 = (**(code **)(pGVar6->_padding_ + 4))();
          bVar2 = GameObject::EnemyP((GameObject *)this,iVar10);
          if ((bVar2) &&
             (bVar2 = GameObject::EnemyP((GameObject *)this,pGVar6->perceivedTeam), bVar2)) {
            pVVar4 = (VECTOR_3D *)(**(code **)(pGVar6->_padding_ + 0xc))();
            pVVar8 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
            fVar13 = Dist3D_Squared(*pVVar8,*pVVar4);
            if (fVar13 < 5625.0) goto LAB_0047e4b2;
          }
        }
        goto LAB_0047e2ed;
      }
      pGVar3 = GameObjectHandle::GetObj(this->_padding_);
      bVar2 = pGVar3 != (GameObject *)0x0;
LAB_0047e4aa:
      if (!bVar2) goto LAB_0047e2ed;
LAB_0047e4b2:
      p_Var16 = (_OBJ76 *)this->_padding_;
      pcVar17 = (char *)(this->_padding_ + 0x39c);
      this->_padding_ = 1;
    }
    DoAudioNew(pcVar17,p_Var16,(GAS_CTRL *)0x0);
  }
  if ((*(int *)(this->_padding_ + 0x3cc) <= this->soldierCount) ||
     (fVar13 = this->reloadDelay - param_1, this->reloadDelay = fVar13, 0.0 < fVar13))
  goto LAB_0047e50a;
  fVar13 = *(float *)(this->_padding_ + 0x3d4);
  local_8 = (GameObject *)(fVar13 * fVar13);
  pGVar3 = Team::GetSlot((Team *)this->_padding_,1);
  if (pGVar3 == (GameObject *)0x0) {
LAB_0047e391:
    local_c = 1.05097e-43;
    do {
      pGVar3 = Team::GetSlot((Team *)this->_padding_,(int)local_c);
      if (pGVar3 != (GameObject *)0x0) {
        pVVar4 = (VECTOR_3D *)(**(code **)(pGVar3->_padding_ + 0xc))();
        pVVar8 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
        fVar13 = Dist3D_Squared(*pVVar8,*pVVar4);
        if (fVar13 < (float)local_8) goto LAB_0047e4d6;
      }
      local_c = (float)((int)local_c + 1);
    } while ((int)local_c < 0x50);
    fVar13 = 0.2;
  }
  else {
    pVVar4 = (VECTOR_3D *)(**(code **)(pGVar3->_padding_ + 0xc))();
    pVVar8 = (VECTOR_3D *)(**(code **)(this->_padding_ + 0xc))();
    fVar13 = Dist3D_Squared(*pVVar8,*pVVar4);
    if ((float)local_8 <= fVar13) goto LAB_0047e391;
LAB_0047e4d6:
    this->soldierCount = this->soldierCount + 1;
    if (this->soldierCount < *(int *)(this->_padding_ + 0x3cc)) {
      fVar13 = *(float *)(this->_padding_ + 0x3d8) + this->reloadDelay;
    }
    else {
      fVar13 = 0.0;
    }
  }
  this->reloadDelay = fVar13;
LAB_0047e50a:
  HoverCraft::Simulate((HoverCraft *)this,param_1);
  return;
}
