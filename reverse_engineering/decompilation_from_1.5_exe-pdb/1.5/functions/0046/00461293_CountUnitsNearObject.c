/*
 * Entry: 00461293
 * Name: CountUnitsNearObject
 * Namespace: Global
 * Signature: int CountUnitsNearObject(int param_1, float param_2, int param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CountUnitsNearObject(int param_1,float param_2,int param_3,char *param_4)

{
  int *piVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  GameObject *pGVar4;
  float *pfVar5;
  GameObject **ppGVar6;
  int iVar7;
  float local_34;
  float local_2c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_28;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_20;
  int local_18;
  int local_14;
  float local_10;
  int local_c;
  char local_5;
  
  if (10000.0 <= param_2) {
    local_5 = '\0';
  }
  else {
    local_5 = '\x01';
    pGVar4 = GameObjectHandle::GetObj(param_1);
    if (pGVar4 == (GameObject *)0x0) {
      Trace("CountUnitsNearObject passed dead object\n");
      return 0;
    }
    pfVar5 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
    local_10 = param_2 * param_2;
    local_34 = *pfVar5;
    local_2c = pfVar5[2];
  }
  local_18 = 0;
  local_14 = 0;
  if (param_4 != (char *)0x0) {
    strncpy((char *)&local_18,param_4,8);
  }
  pvVar2 = GameObject::objectList;
  local_c = 0;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_20,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  while( true ) {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_28,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_20,&local_28);
    if (bVar3) break;
    ppGVar6 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_20);
    piVar1 = &(*ppGVar6)->_padding_;
    iVar7 = (**(code **)(*piVar1 + 0x30))();
    if (((((*(uint *)(iVar7 + 0x14) & 0x200) == 0) &&
         ((param_3 < 0 || (iVar7 = (**(code **)(*piVar1 + 4))(), iVar7 == param_3)))) &&
        ((param_4 == (char *)0x0 ||
         ((iVar7 = (**(code **)*piVar1)(), *(int *)(iVar7 + 0x38) == local_18 &&
          (*(int *)(iVar7 + 0x3c) == local_14)))))) &&
       ((local_5 == '\0' ||
        (pfVar5 = (float *)(**(code **)(*piVar1 + 0xc))(),
        (local_2c - pfVar5[2]) * (local_2c - pfVar5[2]) +
        (local_34 - *pfVar5) * (local_34 - *pfVar5) <= local_10)))) {
      local_c = local_c + 1;
    }
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_20);
  }
  return local_c;
}
