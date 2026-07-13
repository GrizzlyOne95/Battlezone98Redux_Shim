/*
 * Entry: 004aed1c
 * Name: Scavenger::Simulate
 * Namespace: Scavenger
 * Signature: void Simulate(Scavenger * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Scavenger::Simulate(Scavenger *this,float param_1)

{
  int *piVar1;
  float fVar2;
  bool bVar3;
  long lVar4;
  char *pcVar5;
  Scrap *pSVar6;
  int iVar7;
  GameObject *pGVar8;
  int *piVar9;
  int iVar10;
  Scavenger *unaff_EDI;
  Scavenger *local_8;
  
  piVar1 = &this->animHandle;
  local_8 = this;
  if (-1 < *piVar1) {
    lVar4 = AnimObj_Status(*piVar1,(tagANIMOBJ_ACTIVE_LIST **)&local_8);
    if ((lVar4 != 0) || (local_8->_padding_ != 1)) {
      AnimObj_Stop(*piVar1);
      *piVar1 = -1;
    }
  }
  iVar7 = this->_padding_;
  if (iVar7 == 0) {
    piVar9 = (int *)(this->_padding_ + 0xe0);
    if (*piVar9 == 0) goto LAB_004aef25;
    this->_padding_ = 1;
    *piVar9 = 0;
    AnimObj_Start((void *)this->_padding_,0,piVar1);
    pcVar5 = (char *)(this->_padding_ + 0x39c);
  }
  else {
    if (iVar7 == 1) {
      if (*piVar1 == -1) {
        this->delayTimer = 1.0;
        this->_padding_ = 2;
        pSVar6 = BestScrap(unaff_EDI);
        if ((this->scrapHeld < this->maxScrap) && (pSVar6 != (Scrap *)0x0)) {
          piVar1 = &pSVar6->_padding_;
          iVar7 = (**(code **)*piVar1)();
          LoadScrap(this,*(int *)(iVar7 + 0x54));
          DoAudioNew((char *)(this->_padding_ + 0x3c4),(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
          iVar7 = Net_IsNetGame();
          if (iVar7 != 0) {
            bVar3 = DistributedObject::IsLocal((DistributedObject *)&this->_padding_);
            if (!bVar3) goto LAB_004aef25;
          }
          iVar7 = Net_IsNetGame();
          if (iVar7 != 0) {
            bVar3 = DistributedObject::IsLocal((DistributedObject *)piVar1);
            if (!bVar3) {
              iVar7 = Net_IsNetGame();
              if (iVar7 != 0) {
                bVar3 = DistributedObject::IsRemote((DistributedObject *)piVar1);
                if (bVar3) {
                  DistributedObject::Destroy((DistributedObject *)piVar1);
                  DistributedObject::RemoteDelete((DistributedObject *)piVar1);
                }
              }
              goto LAB_004aef25;
            }
          }
          (**(code **)(*piVar1 + 0x10))();
        }
        else if (0 < this->scrapHeld) {
          pGVar8 = BestDropoff(this);
          if (pGVar8 != (GameObject *)0x0) {
            iVar7 = this->scrapHeld;
            UnloadScrap(this,iVar7);
            iVar10 = Net_IsNetGame();
            if (iVar10 != 0) {
              iVar7 = iVar7 * 2;
            }
            Team::AddScrap(pGVar8->teamList,iVar7);
          }
        }
      }
      goto LAB_004aef25;
    }
    if (iVar7 != 2) {
      if ((iVar7 == 3) && (*piVar1 == -1)) {
        this->_padding_ = 0;
      }
      goto LAB_004aef25;
    }
    fVar2 = this->delayTimer - param_1;
    this->delayTimer = fVar2;
    if (0.0 < fVar2) goto LAB_004aef25;
    this->_padding_ = 3;
    if (-1 < *piVar1) {
      AnimObj_Stop(*piVar1);
      *piVar1 = -1;
    }
    AnimObj_Start((void *)this->_padding_,1,piVar1);
    pcVar5 = (char *)(this->_padding_ + 0x3ac);
  }
  DoAudioNew(pcVar5,(_OBJ76 *)this->_padding_,(GAS_CTRL *)0x0);
LAB_004aef25:
  bVar3 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
  if (((!bVar3) && (*(char *)((int)&this->_padding_ + 1) != '\0')) &&
     (iVar7 = this->scrapHeld, 0 < iVar7)) {
    UnloadScrap(this,iVar7);
    iVar10 = Net_IsNetGame();
    if (iVar10 != 0) {
      iVar7 = iVar7 * 2;
    }
    Team::AddScrap((Team *)this->_padding_,iVar7);
  }
  HoverCraft::Simulate((HoverCraft *)this,param_1);
  return;
}
