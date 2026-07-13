/*
 * Entry: 004ae19d
 * Name: Scanner::BasicVisibility
 * Namespace: Scanner
 * Signature: void BasicVisibility(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scanner::BasicVisibility(void)

{
  GameObject *this;
  bool bVar1;
  byte bVar2;
  GameObject **ppGVar3;
  int iVar4;
  uint uVar5;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar6;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_8;
  
  pvVar6 = GameObject::objectList;
  local_8 = GameObject::objectList;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,GameObject::objectList->_Myfirst,
             (_Container_base_aux *)GameObject::objectList);
  local_10._padding_ = local_18._padding_;
  local_10._Myptr = local_18._Myptr;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_18,pvVar6->_Mylast,(_Container_base_aux *)pvVar6);
  bVar1 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                    (&local_10,&local_18);
  if (!bVar1) {
    do {
      ppGVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      this = *ppGVar3;
      if ((this->obj->flags & 1) == 0) {
        iVar4 = (**(code **)this->_padding_)();
        pvVar6 = local_8;
        if (*(int *)(iVar4 + 0x28) != 2) {
          if (this->isObjective == false) {
            this->isVisible = 0;
            bVar2 = (**(code **)(this->_padding_ + 4))();
            uVar5 = 1 << (bVar2 & 0x1f);
            this->isVisible = this->isVisible | uVar5;
            this->seen = this->seen | uVar5;
            iVar4 = 1;
            do {
              bVar1 = GameObject::FriendP(this,iVar4);
              if (bVar1) {
                uVar5 = 1 << ((byte)iVar4 & 0x1f);
                this->isVisible = this->isVisible | uVar5;
                this->seen = this->seen | uVar5;
              }
              iVar4 = iVar4 + 1;
              pvVar6 = local_8;
            } while (iVar4 < 0x10);
          }
          else {
            this->isVisible = 0xffffffff;
          }
        }
      }
      else {
        this->isVisible = 0;
        if ((this->obj->flags & 0x10) != 0) {
          bVar2 = (**(code **)(this->_padding_ + 4))();
          uVar5 = 1 << (bVar2 & 0x1f);
          this->isVisible = this->isVisible | uVar5;
          this->seen = this->seen | uVar5;
        }
      }
      iVar4 = UserPref_unlimitedRadar();
      if (iVar4 != 0) {
        uVar5 = 1 << ((byte)GameObject::userTeamNumber & 0x1f);
        this->isVisible = this->isVisible | uVar5;
        this->seen = this->seen | uVar5;
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10)
      ;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_18,pvVar6->_Mylast,(_Container_base_aux *)pvVar6);
      bVar1 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_10,&local_18);
    } while (!bVar1);
  }
  return;
}
