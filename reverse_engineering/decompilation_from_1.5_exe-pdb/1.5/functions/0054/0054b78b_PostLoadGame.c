/*
 * Entry: 0054b78b
 * Name: PostLoadGame
 * Namespace: Global
 * Signature: int PostLoadGame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PostLoadGame(void)

{
  int *this;
  GameObject *pGVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  GameObject **ppGVar4;
  int iVar5;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  GameObject *local_8;
  
  bVar3 = Net::IsNetGame();
  pGVar1 = GameObject::userObject;
  pvVar2 = GameObject::objectList;
  if (bVar3) {
    DistributedObject::dwGlobalIDCounter = 1;
    local_8 = GameObject::userObject;
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_10,GameObject::objectList->_Myfirst,
               (_Container_base_aux *)GameObject::objectList);
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_18,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_10,&local_18);
    while (!bVar3) {
      ppGVar4 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      pGVar1 = *ppGVar4;
      this = &pGVar1->_padding_;
      iVar5 = (**(code **)*this)();
      if (((*(int *)(iVar5 + 0x20) != 0x5350574e) && (*(int *)(iVar5 + 0x20) != 0x4745495a)) &&
         (local_8 != pGVar1)) {
        bVar3 = Net::GetHosting();
        if (bVar3) {
          DistributedObject::GlobalSetLocal((DistributedObject *)this);
        }
        else {
          DistributedObject::GlobalSetRemote((DistributedObject *)this);
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10)
      ;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_18,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_10,&local_18);
      pGVar1 = local_8;
    }
    if (pGVar1 != (GameObject *)0x0) {
      (**(code **)(pGVar1->_padding_ + 0x10))();
    }
  }
  return 1;
}
