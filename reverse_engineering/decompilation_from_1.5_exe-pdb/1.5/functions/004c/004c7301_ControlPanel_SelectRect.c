/*
 * Entry: 004c7301
 * Name: ControlPanel::SelectRect
 * Namespace: ControlPanel
 * Signature: void SelectRect(ControlPanel * this, tagRECT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::SelectRect(ControlPanel *this,tagRECT param_1)

{
  long *plVar1;
  Craft *this_00;
  ControlPanel *pCVar2;
  bool bVar3;
  char cVar4;
  Craft **ppCVar5;
  int iVar6;
  float *pfVar7;
  tagPOINT tVar8;
  VECTOR_3D local_30;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_24;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_1c;
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> local_14;
  long local_c;
  ControlPanel *local_8;
  
  local_8 = this;
  SelectNone(this);
  local_c = GameObject::userTeamNumber;
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_14,Craft::craftList._Myfirst,(_Container_base_aux *)&Craft::craftList);
  std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
            (&local_1c,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
  bVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                    (&local_14,&local_1c);
  while (!bVar3) {
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++(&local_14);
    ppCVar5 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator*(&local_24);
    this_00 = *ppCVar5;
    iVar6 = (**(code **)(this_00->_padding_ + 4))();
    if (((iVar6 == local_c) && (-1 < this_00->_padding_)) &&
       (cVar4 = (**(code **)(this_00->_padding_ + 0x38))(), cVar4 != '\0')) {
      pfVar7 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
      local_30.x = *pfVar7;
      local_30.y = pfVar7[1];
      local_30.z = pfVar7[2];
      tVar8 = WorldToScreen(&local_30,DisplayInterface::currentCamera,(float *)0x0);
      iVar6 = InsideRect(tVar8,&param_1);
      if (iVar6 != 0) {
        GameObject::SetSelected((GameObject *)this_00,true);
        pCVar2 = local_8;
        plVar1 = &local_8->selectNum;
        iVar6 = GameObject::GetHandle((GameObject *)this_00);
        pCVar2->selectList[*plVar1] = iVar6;
        *plVar1 = *plVar1 + 1;
      }
    }
    std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::
    _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>
              (&local_1c,Craft::craftList._Mylast,(_Container_base_aux *)&Craft::craftList);
    bVar3 = std::_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator==
                      (&local_14,&local_1c);
    this = local_8;
  }
  this->currentItem = -1;
  this->itemSelected = 0;
  return;
}
