/*
 * Entry: 0045b250
 * Name: RecycleTask::InitLookingForScrap
 * Namespace: RecycleTask
 * Signature: void InitLookingForScrap(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::InitLookingForScrap(RecycleTask *this)

{
  bool *pbVar1;
  float fVar2;
  float fVar3;
  Craft *pCVar4;
  Team *this_00;
  Scrap *pSVar5;
  VECTOR_3D VVar6;
  bool bVar7;
  uchar uVar8;
  long lVar9;
  long lVar10;
  Scrap **ppSVar11;
  float *pfVar12;
  AiPath *this_01;
  VECTOR_3D *pVVar13;
  int iVar14;
  float fVar15;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_38;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_30;
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> local_28;
  Scrap *local_20;
  VECTOR_3D *local_1c;
  uchar local_18;
  undefined3 uStack_17;
  int local_14;
  float local_10;
  Scrap *local_c;
  char local_6;
  char local_5;
  
  local_14 = (**(code **)(this->me->_padding_ + 4))();
  pCVar4 = this->me;
  local_5 = '\x01';
  if (pCVar4[1]._padding_ < pCVar4[1]._padding_) {
    this_00 = (Team *)pCVar4->_padding_;
    if (pCVar4[1]._padding_ < 1) {
      lVar9 = Team::GetScrap(this_00);
      lVar10 = Team::GetMaxScrap(this_00);
      if (lVar10 <= lVar9) {
        this->nextState = 6;
        return;
      }
    }
    bVar7 = IsStuck(this);
    if (bVar7) {
      this->nextState = 7;
    }
    else {
      while( true ) {
        local_c = (Scrap *)0x0;
        local_10 = 1e+30;
        pVVar13 = (VECTOR_3D *)(**(code **)(this->me->_padding_ + 0xc))();
        VVar6 = *pVVar13;
        if (((int)Scrap::scrapList._Mylast - (int)Scrap::scrapList._Myfirst & 0xfffffffcU) == 0)
        break;
        uVar8 = CellRegion(pVVar13->x,pVVar13->z);
        _local_18 = CONCAT31(uStack_17,uVar8);
        std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
        _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
                  (&local_38,Scrap::scrapList._Myfirst,(_Container_base_aux *)&Scrap::scrapList);
        local_28._padding_ = local_38._padding_;
        local_28._Myptr = local_38._Myptr;
        while( true ) {
          std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::
          _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>
                    (&local_30,Scrap::scrapList._Mylast,(_Container_base_aux *)&Scrap::scrapList);
          bVar7 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator==
                            (&local_28,&local_30);
          if (bVar7) break;
          ppSVar11 = std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator*
                               (&local_28);
          pSVar5 = *ppSVar11;
          local_20 = pSVar5;
          if (local_5 == '\0') {
            if (pSVar5->HardToGetTo == false) goto LAB_0045b337;
          }
          else {
            pSVar5->HardToGetTo = false;
LAB_0045b337:
            if ((((uint)pSVar5->_padding_ >> ((byte)local_14 & 0x1f) & 1) != 0) &&
               (((uint)pSVar5->_padding_ >> ((byte)local_14 & 0x1f) & 1) == 0)) {
              local_1c = (VECTOR_3D *)(**(code **)(pSVar5->_padding_ + 0xc))();
              bVar7 = GoodScrapPosition(local_1c->x,local_1c->z,(uchar)_local_18);
              if (bVar7) {
                fVar15 = Dist3D_Squared(*local_1c,VVar6);
                if (local_10 < fVar15 == (local_10 == fVar15)) {
                  local_c = local_20;
                  local_10 = fVar15;
                }
              }
              else {
                pSVar5->HardToGetTo = true;
              }
            }
          }
          std::_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++(&local_28);
        }
        local_5 = '\0';
        if (local_c == (Scrap *)0x0) {
          pbVar1 = foundScrap + local_14;
          if (*pbVar1 != false) {
            Say(this,this->notFoundMsg);
            *pbVar1 = false;
          }
          break;
        }
        pfVar12 = (float *)(**(code **)(local_c->_padding_ + 0xc))();
        fVar15 = *pfVar12;
        fVar2 = pfVar12[1];
        fVar3 = pfVar12[2];
        (this->lastScrap).x = fVar15;
        (this->lastScrap).y = fVar2;
        pCVar4 = this->me;
        (this->lastScrap).z = fVar3;
        this_01 = FindPlan((GameObject *)pCVar4,fVar15,fVar3);
        local_6 = this_01->pathType != BAD_PATH;
        AiPath::~AiPath(this_01);
        operator_delete(this_01);
        if (local_6 != '\0') {
          foundScrap[local_14] = true;
          pfVar12 = (float *)(**(code **)(local_c->_padding_ + 0xc))();
          (this->lastScrap).x = *pfVar12;
          (this->lastScrap).y = pfVar12[1];
          (this->lastScrap).z = pfVar12[2];
          iVar14 = GameObject::GetHandle((GameObject *)local_c);
          this->scrapHandle = iVar14;
          this->nextState = 2;
          return;
        }
        local_c->HardToGetTo = true;
      }
      this->nextState = ((0 < this->me[1]._padding_) - 1 & 3) + 3;
    }
  }
  else {
    this->nextState = 3;
  }
  return;
}
