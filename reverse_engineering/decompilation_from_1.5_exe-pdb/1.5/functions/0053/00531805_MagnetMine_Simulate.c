/*
 * Entry: 00531805
 * Name: MagnetMine::Simulate
 * Namespace: MagnetMine
 * Signature: void Simulate(MagnetMine * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MagnetMine::Simulate(MagnetMine *this,float param_1)

{
  VECTOR_3D *pVVar1;
  Craft *pCVar2;
  Ordnance *pOVar3;
  _OBJ76 *p_Var4;
  float fVar5;
  bool bVar6;
  _gas_object *p_Var7;
  Craft **ppCVar8;
  int iVar9;
  tagENTITY *ptVar10;
  Ordnance **ppOVar11;
  float fVar12;
  double dVar13;
  BBOX local_ac;
  float local_94;
  float local_90;
  float local_8c;
  VECTOR_3D local_88;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_7c;
  Mine *local_74;
  GAS_PREP_INFO local_70;
  Craft *local_54;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_50;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_48;
  float local_40;
  float local_3c;
  float local_38;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_7c._Myptr;
  iVar9 = *(int *)&this->field_0xec;
  local_74 = (Mine *)this;
  if (*(float *)(iVar9 + 0x168) < *(float *)(iVar9 + 0x160) - *(float *)&this->field_0x230) {
    if ((*(int *)&this->field_0x228 == 0) && (*(char *)(iVar9 + 0x150) != '\0')) {
      InitGASCtrl(&local_34);
      local_34.flags = 0x801;
      InitGASPrep(&local_70);
      local_70.loopMode = 1;
      local_70.pri = 10;
      p_Var7 = StartGASEvent((char *)(*(int *)&this->field_0xec + 0x150),
                             *(_OBJ76 **)&this->field_0xe8,&local_34,&local_70);
      *(_gas_object **)&this->field_0x228 = p_Var7;
    }
    local_70.loopMode = *(long *)&this->field_0xfc;
    local_70.volume = *(long *)&this->field_0x100;
    local_70.random = *(long *)&this->field_0x104;
    local_70.sampleRate = *(long *)(*(int *)&this->field_0xec + 0x16c);
    local_ac.min.x = (float)local_70.loopMode - (float)local_70.sampleRate;
    local_ac.min.y = (float)local_70.volume - (float)local_70.sampleRate;
    local_ac.min.z = (float)local_70.random - (float)local_70.sampleRate;
    local_ac.max.x = (float)local_70.loopMode + (float)local_70.sampleRate;
    local_ac.max.y = (float)local_70.volume + (float)local_70.sampleRate;
    local_ac.max.z = (float)local_70.sampleRate + (float)local_70.random;
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_48,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
    while( true ) {
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&local_50,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
      bVar6 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                        (&local_48,&local_50);
      if (bVar6) break;
      local_7c._padding_ = local_48._padding_;
      local_7c._Myptr = local_48._Myptr;
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_48);
      ppCVar8 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_7c);
      pCVar2 = *ppCVar8;
      local_54 = pCVar2;
      if (pCVar2 != (Craft *)this) {
        iVar9 = (**(code **)(pCVar2->_padding_ + 0x2c))();
        if (iVar9 != 0) {
          ptVar10 = (tagENTITY *)(**(code **)(pCVar2->_padding_ + 0x2c))();
          iVar9 = CheckBoxes(&local_ac,ptVar10);
          if (iVar9 != 0) {
            iVar9 = pCVar2->_padding_;
            local_94 = (float)pCVar2->_padding_;
            local_40 = (float)*(double *)(iVar9 + 0x48) - (float)local_70.loopMode;
            local_90 = (float)pCVar2->_padding_;
            local_3c = (float)*(double *)(iVar9 + 0x50) - (float)local_70.volume;
            local_8c = (float)pCVar2->_padding_;
            local_38 = (float)*(double *)(iVar9 + 0x58) - (float)local_70.random;
            fVar12 = local_40 * local_40 + local_3c * local_3c + local_38 * local_38;
            if (fVar12 < (float)local_70.sampleRate * (float)local_70.sampleRate) {
              iVar9 = *(int *)&this->field_0xec;
              dVar13 = rsqrt((double)(fVar12 + 0.0001));
              fVar12 = ((float)dVar13 * *(float *)(iVar9 + 0x170) + *(float *)(iVar9 + 0x174)) *
                       param_1;
              fVar5 = *(float *)(iVar9 + 0x178) * param_1;
              local_88.x = fVar12 * local_40 - local_94 * fVar5;
              local_88.y = fVar12 * local_3c - local_90 * fVar5;
              local_88.z = fVar12 * local_38 - local_8c * fVar5;
              GameObject::AddVelocity((GameObject *)local_54,&local_88);
            }
          }
        }
      }
    }
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              ((_Const_iterator<1> *)&local_48,(Ordnance::ordnanceList._Myhead)->_Next,
               &Ordnance::ordnanceList);
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              ((_Const_iterator<1> *)&local_50,Ordnance::ordnanceList._Myhead,
               &Ordnance::ordnanceList);
    bVar6 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                      ((_Const_iterator<1> *)&local_48,(_Const_iterator<1> *)&local_50);
    if (!bVar6) {
      local_54 = (Craft *)((float)local_70.sampleRate * (float)local_70.sampleRate);
      do {
        local_7c._padding_ = local_48._padding_;
        local_7c._Myptr = local_48._Myptr;
        std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++
                  ((_Const_iterator<1> *)&local_48);
        ppOVar11 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                             ((_Const_iterator<1> *)&local_7c);
        pOVar3 = *ppOVar11;
        p_Var4 = pOVar3->obj;
        local_40 = (float)(p_Var4->transform).posit_x - (float)local_70.loopMode;
        local_88.x = (pOVar3->euler).v.x;
        local_88.y = (pOVar3->euler).v.y;
        local_3c = (float)(p_Var4->transform).posit_y - (float)local_70.volume;
        local_88.z = (pOVar3->euler).v.z;
        local_38 = (float)(p_Var4->transform).posit_z - (float)local_70.random;
        fVar12 = local_40 * local_40 + local_3c * local_3c + local_38 * local_38;
        if (fVar12 < (float)local_54) {
          iVar9 = local_74->_padding_;
          dVar13 = rsqrt((double)(fVar12 + 0.0001));
          fVar12 = ((float)dVar13 * *(float *)(iVar9 + 0x17c) + *(float *)(iVar9 + 0x180)) * param_1
          ;
          pVVar1 = &(pOVar3->euler).v;
          fVar5 = *(float *)(iVar9 + 0x184) * param_1;
          pVVar1->x = (fVar12 * local_40 - local_88.x * fVar5) + pVVar1->x;
          (pOVar3->euler).v.y = (fVar12 * local_3c - local_88.y * fVar5) + (pOVar3->euler).v.y;
          (pOVar3->euler).v.z = (fVar12 * local_38 - local_88.z * fVar5) + (pOVar3->euler).v.z;
          fVar12 = VecLen(*pVVar1);
          (pOVar3->euler).v_mag = fVar12;
          if (fVar12 <= 0.0) {
            fVar12 = 1e+30;
          }
          else {
            fVar12 = 1.0 / fVar12;
          }
          (pOVar3->euler).v_mag_inv = fVar12;
        }
        std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
                  ((_Const_iterator<1> *)&local_50,Ordnance::ordnanceList._Myhead,
                   &Ordnance::ordnanceList);
        bVar6 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                          ((_Const_iterator<1> *)&local_48,(_Const_iterator<1> *)&local_50);
        this = (MagnetMine *)local_74;
      } while (!bVar6);
    }
  }
  Mine::Simulate((Mine *)this,param_1);
  return;
}
