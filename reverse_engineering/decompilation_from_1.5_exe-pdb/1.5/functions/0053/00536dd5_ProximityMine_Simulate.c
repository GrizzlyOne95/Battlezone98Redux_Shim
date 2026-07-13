/*
 * Entry: 00536dd5
 * Name: ProximityMine::Simulate
 * Namespace: ProximityMine
 * Signature: void Simulate(ProximityMine * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ProximityMine::Simulate(ProximityMine *this,float param_1)

{
  uint *puVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  ExplosionClass *this_00;
  VECTOR_3D VVar8;
  Craft *pCVar9;
  bool bVar10;
  Craft **ppCVar11;
  float *pfVar12;
  GameObject *pGVar13;
  _OBJ76 *p_Var14;
  float fVar15;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_28;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_20;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_18;
  Craft *local_10;
  float local_c;
  char local_5;
  
  fVar15 = this->searchTimer - param_1;
  this->searchTimer = fVar15;
  if ((fVar15 < 0.0) && ((*(uint *)(this->_padding_ + 0x14) & 0x200) == 0)) {
    this->searchTimer = fVar15 + *(float *)(this->_padding_ + 0x16c);
    local_c = *(float *)(this->_padding_ + 0x168);
    local_5 = '\0';
    local_c = local_c * local_c;
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_18,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_20,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar10 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                       (&local_18,&local_20);
    if (!bVar10) {
      do {
        local_28._padding_ = local_18._padding_;
        local_28._Myptr = local_18._Myptr;
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_18);
        ppCVar11 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*
                             (&local_28);
        local_10 = *ppCVar11;
        if ((*(uint *)(local_10->_padding_ + 0x14) & 0x200) == 0) {
          fVar15 = (float)this->_padding_;
          fVar5 = (float)this->_padding_;
          fVar6 = (float)this->_padding_;
          pfVar12 = (float *)(**(code **)(local_10->_padding_ + 0xc))();
          pCVar9 = local_10;
          fVar15 = *pfVar12 - fVar15;
          fVar5 = pfVar12[1] - fVar5;
          fVar6 = pfVar12[2] - fVar6;
          if (fVar15 * fVar15 + fVar5 * fVar5 + fVar6 * fVar6 <= local_c) {
            bVar10 = GameObject::FriendP((GameObject *)this,(GameObject *)local_10);
            if (bVar10) {
              local_5 = '\0';
              break;
            }
            if (0.0 < (float)pCVar9->_padding_ * fVar15 +
                      (float)pCVar9->_padding_ * fVar5 + (float)pCVar9->_padding_ * fVar6) {
              local_5 = '\x01';
            }
          }
        }
        std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
        _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                  (&local_20,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
        bVar10 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                           (&local_18,&local_20);
      } while (!bVar10);
      if (local_5 != '\0') {
        iVar7 = this->_padding_;
        dVar2 = *(double *)(iVar7 + 0x48);
        local_c = 2.8026e-44;
        dVar3 = *(double *)(iVar7 + 0x50);
        dVar4 = *(double *)(iVar7 + 0x58);
        do {
          VVar8.y = (float)dVar3;
          VVar8.x = (float)dVar2;
          VVar8.z = (float)dVar4;
          ChunkEffect::CreateChunklet
                    (&chunkEffect,VVar8,(VECTOR_3D)ZEXT812(0x4170000000000000),false);
          local_c = (float)((int)local_c + -1);
        } while (local_c != 0.0);
        MakeCrater((float)*(double *)(this->_padding_ + 0x48),
                   (float)*(double *)(this->_padding_ + 0x58),3.0);
        fVar15 = Terrain_FindFloor(*(double *)(this->_padding_ + 0x48),
                                   *(double *)(this->_padding_ + 0x58));
        *(double *)(this->_padding_ + 0x50) = (double)fVar15;
        pGVar13 = GameObject::GetObj(this->_padding_);
        if (pGVar13 == (GameObject *)0x0) {
          p_Var14 = (_OBJ76 *)this->_padding_;
        }
        else {
          p_Var14 = (_OBJ76 *)(**(code **)(pGVar13->_padding_ + 0x30))();
        }
        this_00 = *(ExplosionClass **)(this->_padding_ + 0x170);
        if (this_00 != (ExplosionClass *)0x0) {
          ExplosionClass::Build(this_00,(MAT_3D *)(this->_padding_ + 0x20),p_Var14);
        }
        puVar1 = (uint *)(this->_padding_ + 0x14);
        *puVar1 = *puVar1 | 0x280;
        bVar10 = Net::IsNetGame();
        if (bVar10) {
          DistributedObject::SetLocal((DistributedObject *)&this->_padding_);
        }
      }
    }
  }
  Mine::Simulate((Mine *)this,param_1);
  return;
}
