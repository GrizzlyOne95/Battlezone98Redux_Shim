/*
 * Entry: 004d3676
 * Name: OverView::ClickedOn
 * Namespace: OverView
 * Signature: GameObject * ClickedOn(OverView * this, tagPOINT param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall OverView::ClickedOn(OverView *this,tagPOINT param_1)

{
  int *piVar1;
  GameObject *this_00;
  float fVar2;
  float fVar3;
  bool bVar4;
  GameObject **ppGVar5;
  int iVar6;
  float *pfVar7;
  SPHERE *pSVar8;
  tagPOINT tVar9;
  VECTOR_3D local_34;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_28;
  int local_20;
  int local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  float local_10;
  GameObject *local_c;
  float local_8;
  
  local_c = (GameObject *)0x0;
  local_8 = 1e+37;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_28,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_18._padding_ = local_28._padding_;
  local_18._Myptr = local_28._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_28,GameObject::objectList->_Mylast,(_Container_base_aux *)GameObject::objectList
            );
  bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_18,&local_28);
  while (!bVar4) {
    ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_18);
    this_00 = *ppGVar5;
    piVar1 = &this_00->_padding_;
    iVar6 = (**(code **)(*piVar1 + 0x30))();
    if (((*(byte *)(iVar6 + 0x14) & 1) == 0) &&
       (iVar6 = (**(code **)(*piVar1 + 0x2c))(), iVar6 != 0)) {
      pfVar7 = (float *)(**(code **)(*piVar1 + 0xc))();
      local_34.x = *pfVar7;
      local_34.y = pfVar7[1];
      local_34.z = pfVar7[2];
      tVar9 = WorldToScreen(&local_34,DisplayInterface::currentCamera,&local_10);
      local_20 = tVar9.x;
      pSVar8 = GameObject::GetSphere(this_00);
      local_1c = tVar9.y - param_1.y;
      local_20 = tVar9.x - param_1.x;
      fVar2 = pSVar8->radius * local_10 + 5.0;
      fVar3 = (float)local_20 * (float)local_20 + (float)local_1c * (float)local_1c;
      if ((fVar3 < fVar2 * fVar2) && (fVar3 < local_8)) {
        local_c = this_00;
        local_8 = fVar3;
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_18);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_28,GameObject::objectList->_Mylast,
               (_Container_base_aux *)GameObject::objectList);
    bVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_18,&local_28);
  }
  return local_c;
}
