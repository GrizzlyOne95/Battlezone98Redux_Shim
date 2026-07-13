/*
 * Entry: 004c2885
 * Name: HardPoints::Render
 * Namespace: HardPoints
 * Signature: void Render(HardPoints * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HardPoints::Render(HardPoints *this)

{
  Craft *this_00;
  Carrier *pCVar1;
  _OBJ76 *p_Var2;
  bool bVar3;
  Craft **ppCVar4;
  float *pfVar5;
  VECTOR_3D *pVVar6;
  SPHERE *pSVar7;
  long lVar8;
  tagPOINT tVar9;
  int aiStackY_158 [37];
  undefined4 uStackY_c4;
  VECTOR_3D local_8c;
  VECTOR_3D local_80;
  VECTOR_3D local_74;
  float local_68;
  long local_64 [4];
  long local_54;
  long local_50;
  long local_4c;
  long local_48;
  long local_44;
  long local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  ulong local_2c;
  VECTOR_3D local_28;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_1c;
  _OBJ76 **local_14;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_10;
  int local_8;
  
  local_64[0] = DisplayInterface::colorDkRed;
  local_64[1] = DisplayInterface::colorRed;
  local_64[2] = DisplayInterface::colorDkYellow;
  local_64[3] = DisplayInterface::colorYellow;
  local_54 = DisplayInterface::colorDkGreen;
  local_50 = DisplayInterface::colorGreen;
  local_4c = DisplayInterface::colorDkCyan;
  local_48 = DisplayInterface::colorCyan;
  local_44 = DisplayInterface::colorDkBlue;
  local_40 = DisplayInterface::colorBlue;
  local_3c = GetSpriteIndex("weapon_c");
  local_38 = GetSpriteIndex("weapon_r");
  local_34 = GetSpriteIndex("weapon_m");
  local_30 = GetSpriteIndex("weapon_s");
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_10,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
  local_1c._padding_ = local_10._padding_;
  local_1c._Myptr = local_10._Myptr;
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_10,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
  bVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                    (&local_1c,&local_10);
  while (!bVar3) {
    ppCVar4 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_1c);
    this_00 = *ppCVar4;
    pfVar5 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
    pVVar6 = Camera_World_to_Camera
                       (&local_80,DisplayInterface::currentCamera,(double)*pfVar5,(double)pfVar5[1],
                        (double)pfVar5[2]);
    local_28.x = pVVar6->x;
    local_28.y = pVVar6->y;
    local_28.z = pVVar6->z;
    pSVar7 = GameObject::GetSphere((GameObject *)this_00);
    lVar8 = Camera_Bounding_Sphere_Test(DisplayInterface::currentCamera,&local_28,pSVar7->radius);
    if (((lVar8 < 1) &&
        (local_28.z * local_28.z + local_28.x * local_28.x + local_28.y * local_28.y <= 10000.0)) &&
       (pCVar1 = (Carrier *)this_00->_padding_, pCVar1 != (Carrier *)0x0)) {
      local_2c = pCVar1->selected;
      local_8 = 0;
      local_14 = pCVar1->hardpoint;
      do {
        p_Var2 = *local_14;
        if (p_Var2 != (_OBJ76 *)0x0) {
          pVVar6 = obj_get_world_position(&local_8c,p_Var2);
          local_74.x = pVVar6->x;
          local_74.y = pVVar6->y;
          local_74.z = pVVar6->z;
          tVar9 = WorldToScreen(&local_74,DisplayInterface::currentCamera,&local_68);
          Foreground_Color = local_64[(local_2c >> ((byte)local_8 & 0x1f) & 1) + local_8 * 2];
          uStackY_c4 = 0x4c2a70;
          DrawSprite(DisplayInterface::currentBuffer,aiStackY_158[p_Var2->class_id],tVar9.x,tVar9.y,
                     5);
        }
        local_8 = local_8 + 1;
        local_14 = local_14 + 1;
      } while (local_8 < 5);
    }
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_1c);
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_10,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_1c,&local_10);
  }
  return;
}
