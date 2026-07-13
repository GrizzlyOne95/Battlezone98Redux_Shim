/*
 * Entry: 0044c448
 * Name: MultDMMission::Init
 * Namespace: MultDMMission
 * Signature: void Init(MultDMMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MultDMMission::Init(MultDMMission *this)

{
  bool bVar1;
  ushort uVar2;
  MultDMEvent *pMVar3;
  PathSpawn *pPVar4;
  int iVar5;
  char *pcVar6;
  GameObjectClass *pGVar7;
  SpawnPoint *this_00;
  VECTOR_3D *pVVar8;
  NetPlayer *this_01;
  GameObject *pGVar9;
  UserProcess *this_02;
  MAT_3D *pMVar10;
  MAT_3D *pMVar11;
  char *pcVar12;
  MAT_3D local_54;
  VECTOR_3D local_14;
  MultDMMission *local_8;
  
  if (theNet != (Net *)0x0) {
    local_8 = this;
    pMVar3 = operator_new(0x38);
    if (pMVar3 == (MultDMEvent *)0x0) {
      pMVar3 = (MultDMEvent *)0x0;
    }
    else {
      pMVar3 = MultDMEvent::MultDMEvent(pMVar3,(AiMission *)this);
    }
    this->multEvent = pMVar3;
    pPVar4 = operator_new(0x114c);
    if (pPVar4 == (PathSpawn *)0x0) {
      pPVar4 = (PathSpawn *)0x0;
    }
    else {
      pPVar4 = PathSpawn::PathSpawn(pPVar4,(AiMission *)this);
    }
    this->pathSpawn = pPVar4;
    Net::SetDeathMatch(true);
    iVar5 = Net_IsNetGame();
    if (iVar5 != 0) {
      local_14.y = 0.0;
      local_14.z = 0.0;
      pcVar12 = Net::odfName;
      do {
        pcVar6 = pcVar12;
        pcVar12 = pcVar6 + 1;
      } while (*pcVar6 != '\0');
      memcpy(&local_14.y,Net::odfName,pcVar6 + -0x62a994);
      pGVar7 = GameObjectClass::Find(CONCAT44(local_14.z,local_14.y));
      bVar1 = Net::GetHosting();
      if (bVar1) {
        this_00 = SpawnPoint::GetRandom(Net::Team);
        if (this_00 == (SpawnPoint *)0x0) {
          if ((SpawnPoint::spawnPointList ==
               (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0) ||
             (((int)SpawnPoint::spawnPointList->_Mylast - (int)SpawnPoint::spawnPointList->_Myfirst
              & 0xfffffffcU) == 0)) {
            pcVar12 = "Map has no spawn points";
          }
          else {
            pcVar12 = "Could not get a spawn point";
          }
          DEBUG_systemWarning(pcVar12);
          SetRunning(2);
          return;
        }
        pVVar8 = SpawnPoint::GetLocation(this_00);
        Net::SetStartLocation(theNet,pVVar8);
        uVar2 = Net::GetMyPlayerID(theNet);
        this_01 = NetPlayer::Find(uVar2);
        NetPlayer::SetWaitingForSpawnPoint(this_01,false);
      }
      Net::GetStartLocation(theNet,&local_14);
      pMVar10 = &Identity_Matrix;
      pMVar11 = &local_54;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar11->right_x = pMVar10->right_x;
        pMVar10 = (MAT_3D *)&pMVar10->right_y;
        pMVar11 = (MAT_3D *)&pMVar11->right_y;
      }
      local_54.posit_x = (double)local_14.x;
      local_54.posit_y = (double)local_14.y;
      local_54.posit_z = (double)local_14.z;
      pGVar9 = GameObjectClass::Build(pGVar7,&local_54,Net::Team,1,-1,(char *)0x0);
      this_02 = operator_new(0x70);
      if (this_02 != (UserProcess *)0x0) {
        UserProcess::UserProcess(this_02,(AiMission *)local_8,pGVar9);
      }
      DistributedObject::SetLocal((DistributedObject *)&pGVar9->_padding_);
      if (pGVar9->curPilot == (GameObjectClass *)0x0) {
        iVar5 = (**(code **)pGVar9->_padding_)();
        if (pGVar9 == GameObject::userObject) {
          pGVar7 = *(GameObjectClass **)(iVar5 + 0xdc);
        }
        else {
          pGVar7 = *(GameObjectClass **)(iVar5 + 0xd8);
        }
        pGVar9->curPilot = pGVar7;
      }
    }
  }
  return;
}
