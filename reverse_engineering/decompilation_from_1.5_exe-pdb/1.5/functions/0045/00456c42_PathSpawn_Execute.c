/*
 * Entry: 00456c42
 * Name: PathSpawn::Execute
 * Namespace: PathSpawn
 * Signature: void Execute(PathSpawn * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathSpawn::Execute(PathSpawn *this)

{
  bool bVar1;
  GameObject **ppGVar2;
  GameObject *pGVar3;
  int iVar4;
  Item *pIVar5;
  float *pfVar6;
  float fVar7;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  int local_8;
  
  bVar1 = Net::IsNetGame();
  if ((!bVar1) || (bVar1 = Net::GetHosting(), bVar1)) {
    iVar4 = 0;
    if (this->state == INIT) {
      this->state = RUN;
      local_8 = 0;
      if (0 < this->number) {
        pIVar5 = this->pup;
        do {
          std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
          _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                    (&local_10,GameObject::objectList->_Myfirst,
                     (_Container_base_aux *)GameObject::objectList);
          while( true ) {
            std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
            _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                      (&local_18,GameObject::objectList->_Mylast,
                       (_Container_base_aux *)GameObject::objectList);
            bVar1 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
                    operator==(&local_10,&local_18);
            if (bVar1) break;
            ppGVar2 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
                      operator*(&local_10);
            pGVar3 = *ppGVar2;
            iVar4 = strncmp(pIVar5->str,pGVar3->label,0x14);
            if (iVar4 == 0) {
              iVar4 = GameObject::GetHandle(pGVar3);
              pIVar5->powerup = iVar4;
              break;
            }
            std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++
                      (&local_10);
          }
          if (pIVar5->powerup == 0) {
            iVar4 = BuildObject(pIVar5->odf,0,pIVar5->str,0);
            pIVar5->powerup = iVar4;
            pGVar3 = GameObjectHandle::GetObj(iVar4);
            if (pGVar3 != (GameObject *)0x0) {
              GameObject::SetLabel(pGVar3,pIVar5->str);
            }
          }
          local_8 = local_8 + 1;
          pIVar5->waiting = false;
          pIVar5 = pIVar5 + 1;
        } while (local_8 < this->number);
      }
    }
    else if (0 < this->number) {
      pfVar6 = &this->pup[0].time;
      do {
        pGVar3 = GameObjectHandle::GetObj(((Item *)(pfVar6 + -1))->powerup);
        if (pGVar3 == (GameObject *)0x0) {
          if (*(bool *)((int)pfVar6 + 0x26) == false) {
            *(bool *)((int)pfVar6 + 0x26) = true;
            fVar7 = Get_Time();
            *pfVar6 = fVar7 + pfVar6[1];
            goto LAB_00456d65;
          }
LAB_00456d6b:
          fVar7 = Get_Time();
          if (*pfVar6 < fVar7) {
            fVar7 = (float)BuildObject((char *)(pfVar6 + 7),0,(char *)(pfVar6 + 2),0);
            ((Item *)(pfVar6 + -1))->powerup = (int)fVar7;
            GameObjectHandle::GetObj((int)fVar7);
            *(bool *)((int)pfVar6 + 0x26) = false;
          }
        }
        else {
LAB_00456d65:
          if (*(bool *)((int)pfVar6 + 0x26) != false) goto LAB_00456d6b;
        }
        iVar4 = iVar4 + 1;
        pfVar6 = pfVar6 + 0xb;
      } while (iVar4 < this->number);
    }
  }
  return;
}
