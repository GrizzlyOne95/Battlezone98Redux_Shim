/*
 * Entry: 004c973f
 * Name: EarthQuake::Simulate
 * Namespace: EarthQuake
 * Signature: void Simulate(EarthQuake * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EarthQuake::Simulate(EarthQuake *this,float param_1)

{
  double dVar1;
  Craft *this_00;
  _OBJ76 *p_Var2;
  bool bVar3;
  Craft **ppCVar4;
  int unaff_EDI;
  float fVar5;
  VECTOR_3D local_54;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_24;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_1c;
  int local_14;
  EarthQuake *local_10;
  float local_c;
  float local_8;
  
  if (0.0 < this->scale) {
    local_10 = this;
    local_14 = Set_Rounding(unaff_EDI);
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_24,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
    local_1c._padding_ = local_24._padding_;
    local_1c._Myptr = local_24._Myptr;
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_24,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_1c,&local_24);
    while (!bVar3) {
      ppCVar4 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_1c);
      this_00 = *ppCVar4;
      p_Var2 = (_OBJ76 *)this_00->_padding_;
      dVar1 = (p_Var2->transform).posit_y;
      fVar5 = Terrain_FindFloor((p_Var2->transform).posit_x,(p_Var2->transform).posit_z);
      fVar5 = (float)dVar1 - fVar5;
      local_c = (param_1 * this->scale) / (fVar5 * fVar5 * 0.5 + 1.0);
      local_8 = Get_Time();
      local_8 = local_8 + local_8;
      local_30 = Noise1D(local_8 + 8.53);
      local_30 = local_30 * local_c;
      fVar5 = Noise1D(local_8 + 17.67);
      local_2c = fVar5 * local_c * 0.3;
      fVar5 = Noise1D(local_8 + 5.19);
      local_3c = ((VECTOR_3D *)&this_00->_padding_)->x;
      local_38 = (float)this_00->_padding_;
      local_34 = (float)this_00->_padding_;
      local_48 = local_3c + local_30;
      local_44 = local_38 + local_2c;
      local_40 = fVar5 * local_c + local_34;
      ((VECTOR_3D *)&this_00->_padding_)->x = local_48;
      this_00->_padding_ = (int)local_44;
      this_00->_padding_ = (int)local_40;
      fVar5 = Noise1D(local_8);
      local_54.x = fVar5 * local_c * 5.0;
      fVar5 = Noise1D(local_8 + 2.27);
      local_54.y = fVar5 * local_c + fVar5 * local_c;
      fVar5 = Noise1D(local_8 + 23.41);
      local_54.z = fVar5 * local_c * 5.0;
      GameObject::AddVelocity((GameObject *)this_00,&local_54);
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_1c);
      std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
      _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
                (&local_24,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
      bVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                        (&local_1c,&local_24);
      this = local_10;
    }
    Set_Rounding(unaff_EDI);
  }
  return;
}
