/*
 * Entry: 004e2674
 * Name: NetPlayer::~NetPlayer
 * Namespace: NetPlayer
 * Signature: void ~NetPlayer(NetPlayer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall NetPlayer::~NetPlayer(NetPlayer *this)

{
  int *this_00;
  GameObject *pGVar1;
  vector<GameObject_*,std::allocator<GameObject_*>_> *pvVar2;
  bool bVar3;
  ushort uVar4;
  GameObject **ppGVar5;
  int iVar6;
  _OBJ76 *p_Var7;
  ulong uVar8;
  Team *pTVar9;
  uint uVar10;
  uint uVar11;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_18;
  _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_> local_10;
  vector<GameObject_*,std::allocator<GameObject_*>_> *local_8;
  
  pvVar2 = GameObject::objectList;
  if (GameObject::objectList != (vector<GameObject_*,std::allocator<GameObject_*>_> *)0x0) {
    local_8 = GameObject::objectList;
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
      ppGVar5 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator*
                          (&local_10);
      pGVar1 = *ppGVar5;
      this_00 = &pGVar1->_padding_;
      uVar4 = DistributedObject::GetPlayerID((DistributedObject *)this_00);
      if (uVar4 == this->playerId) {
        iVar6 = (**(code **)(*this_00 + 4))();
        bVar3 = GetAIControl(iVar6);
        if (!bVar3) {
          pGVar1->curPilot = (GameObjectClass *)0x0;
          p_Var7 = (_OBJ76 *)(**(code **)(*this_00 + 0x30))();
          if ((p_Var7 != (_OBJ76 *)0x0) && (p_Var7->gravestone != 1)) {
            uVar8 = DistributedObject::GetID((DistributedObject *)this_00);
            if ((0xffff < uVar8) && (p_Var7->class_id != CLASS_ID_SCRAP)) {
              obj_set_flag(p_Var7,0x280);
            }
            DistributedObject::SetLocal((DistributedObject *)this_00);
          }
        }
      }
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator++(&local_10)
      ;
      std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::
      _Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>
                (&local_18,local_8->_Mylast,(_Container_base_aux *)local_8);
      bVar3 = std::_Vector_const_iterator<GameObject_*,std::allocator<GameObject_*>_>::operator==
                        (&local_10,&local_18);
    }
  }
  if ((this->bTeamNumber != 0) && (this->bTeamNumber < 0x10)) {
    iVar6 = GetRunning();
    if ((iVar6 == 5) && (iVar6 = ALLIE_IsLocked(), iVar6 == 0)) {
      uVar11 = 1;
      do {
        if (this->bTeamNumber != uVar11) {
          uVar10 = uVar11;
          pTVar9 = Team::GetTeam((uint)this->bTeamNumber);
          Team::UnAlly(pTVar9,uVar10);
          uVar10 = (uint)this->bTeamNumber;
          pTVar9 = Team::GetTeam(uVar11);
          Team::UnAlly(pTVar9,uVar10);
        }
        uVar11 = uVar11 + 1;
      } while ((int)uVar11 < 0x10);
    }
    SetTeam(this,0);
  }
  std::
  _Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
  ::erase((_Tree<std::_Tmap_traits<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>,0>_>
           *)&netPlayerMap,&this->playerId);
  if (this->SpawnPointer != (SpawnPoint *)0x0) {
    SpawnPoint::Unlock(this->SpawnPointer,this);
  }
  return;
}
