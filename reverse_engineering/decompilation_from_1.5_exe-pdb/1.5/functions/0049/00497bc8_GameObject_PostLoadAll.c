/*
 * Entry: 00497bc8
 * Name: GameObject::PostLoadAll
 * Namespace: GameObject
 * Signature: bool PostLoadAll(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GameObject::PostLoadAll(void)

{
  GameObject *pGVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  char cVar4;
  GameObject **ppGVar5;
  UserProcess *this;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_1c;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_14;
  AiMission *local_c;
  GameObject *local_8;
  
  pvVar2 = objectList;
  cVar4 = '\x01';
  local_c = AiMission::GetCurrent();
  local_8 = userObject;
  std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
            (&local_14,pvVar2->_Myfirst,(_Container_base_aux *)pvVar2);
  do {
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
    _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
              (&local_1c,pvVar2->_Mylast,(_Container_base_aux *)pvVar2);
    bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                      (&local_14,&local_1c);
    if (bVar3) {
      return (bool)cVar4;
    }
    ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                        (&local_14);
    pGVar1 = *ppGVar5;
    if ((missionSave != false) && (pGVar1->aiProcess == (AiProcess *)0x1)) {
      pGVar1->aiProcess = (AiProcess *)0x0;
      if (pGVar1 == local_8) {
        this = ::operator_new(0x70);
        if (this != (UserProcess *)0x0) {
          UserProcess::UserProcess(this,local_c,local_8);
        }
      }
      else {
        (**(code **)(local_c->_padding_ + 0x18))(pGVar1);
      }
    }
    cVar4 = (**(code **)(pGVar1->_padding_ + 0x54))();
    std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_14);
  } while (cVar4 != '\0');
  return false;
}
