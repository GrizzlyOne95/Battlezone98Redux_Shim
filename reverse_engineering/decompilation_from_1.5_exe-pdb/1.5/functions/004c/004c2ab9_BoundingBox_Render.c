/*
 * Entry: 004c2ab9
 * Name: BoundingBox::Render
 * Namespace: BoundingBox
 * Signature: void Render(BoundingBox * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall BoundingBox::Render(BoundingBox *this)

{
  int iVar1;
  _OBJ76 *p_Var2;
  BoundingBox *this_00;
  bool bVar3;
  GameObject **ppGVar4;
  float *pfVar5;
  VECTOR_3D *pVVar6;
  SPHERE *pSVar7;
  long lVar8;
  int *piVar9;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  BoundingBox *local_c;
  GameObject *local_8;
  
  local_c = this;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_1c,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_14._padding_ = local_1c._padding_;
  local_14._Myptr = local_1c._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_1c,GameObject::objectList->_Mylast,(_Container_base_aux *)GameObject::objectList
            );
  bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_14,&local_1c);
  while (!bVar3) {
    ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_14);
    local_8 = *ppGVar4;
    piVar9 = &local_8->_padding_;
    pfVar5 = (float *)(**(code **)(*piVar9 + 0xc))();
    pVVar6 = Camera_World_to_Camera
                       (&local_4c,DisplayInterface::currentCamera,(double)*pfVar5,(double)pfVar5[1],
                        (double)pfVar5[2]);
    local_28.x = pVVar6->x;
    local_28.y = pVVar6->y;
    local_28.z = pVVar6->z;
    pSVar7 = GameObject::GetSphere(local_8);
    lVar8 = Camera_Bounding_Sphere_Test(DisplayInterface::currentCamera,&local_28,pSVar7->radius);
    if ((lVar8 < 1) &&
       (local_28.x * local_28.x + local_28.z * local_28.z + local_28.y * local_28.y <= 40000.0)) {
      local_8 = (GameObject *)GameObject::GetColor(local_8);
      piVar9 = (int *)(**(code **)(*piVar9 + 0x2c))();
      this_00 = local_c;
      DrawBox(local_c,(VECTOR_3D *)(piVar9 + 0x11),(VECTOR_3D *)(piVar9 + 0x14),(MAT_3D *)0x0,
              DisplayInterface::colorDkGrey);
      DrawSphere(this_00,(VECTOR_3D *)(piVar9 + 2),(float)piVar9[5],(MAT_3D *)(*piVar9 + 0x20),
                 DisplayInterface::colorDkGrey);
      iVar1 = piVar9[9];
      if (iVar1 == 1) {
        p_Var2 = (_OBJ76 *)*piVar9;
        piVar9 = (int *)piVar9[10];
        if (piVar9 == (int *)0x0) {
          get_obj_bounding_box(p_Var2,&local_40,&local_34);
        }
        else {
          local_40.x = (float)piVar9[3];
          local_40.y = (float)piVar9[7];
          local_40.z = (float)piVar9[0xb];
          local_34.x = (float)piVar9[*piVar9 + 2];
          local_34.y = (float)piVar9[piVar9[1] + 6];
          local_34.z = (float)piVar9[piVar9[2] + 10];
        }
        DrawBox(this_00,&local_40,&local_34,&p_Var2->transform,(long)local_8);
      }
      else if (iVar1 == 2) {
        iVar1 = *piVar9;
        DrawSphere(this_00,(VECTOR_3D *)(iVar1 + 200),*(float *)(iVar1 + 0xd4),
                   (MAT_3D *)(iVar1 + 0x20),(long)local_8);
      }
      else if (iVar1 == 3) {
        DrawRecurse(this_00,(_OBJ76 *)*piVar9,(MAT_3D *)0x0,(long)local_8);
      }
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_14);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_1c,GameObject::objectList->_Mylast,
               (_Container_base_aux *)GameObject::objectList);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_14,&local_1c);
  }
  return;
}
