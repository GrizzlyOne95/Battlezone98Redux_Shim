/*
 * Entry: 0044d409
 * Name: MultSTMission::Init
 * Namespace: MultSTMission
 * Signature: void Init(MultSTMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MultSTMission::Init(MultSTMission *this)

{
  char cVar1;
  bool bVar2;
  ushort uVar3;
  PathSpawn *pPVar4;
  char *pcVar5;
  GameObjectClass *pGVar6;
  SpawnPoint *this_00;
  VECTOR_3D *pVVar7;
  NetPlayer *this_01;
  GameObject *pGVar8;
  UserProcess *this_02;
  GameObjectClass *pGVar9;
  int iVar10;
  undefined1 uVar11;
  MAT_3D *pMVar12;
  MAT_3D *pMVar13;
  float fVar14;
  MAT_3D local_70;
  VECTOR_3D local_30;
  MultSTMission *local_24;
  int local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (theNet == (Net *)0x0) {
    return;
  }
  local_24 = this;
  pPVar4 = operator_new(0x114c);
  if (pPVar4 == (PathSpawn *)0x0) {
    pPVar4 = (PathSpawn *)0x0;
  }
  else {
    pPVar4 = PathSpawn::PathSpawn(pPVar4,(AiMission *)this);
  }
  this->pathSpawn = pPVar4;
  Net::SetDeathMatch(false);
  pcVar5 = Net::odfName;
  local_20 = 0;
  local_1c = 0;
  do {
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  memcpy(&local_20,Net::odfName);
  pGVar6 = GameObjectClass::Find(CONCAT44(local_1c,local_20));
  bVar2 = Net::GetHosting();
  if (bVar2) {
    this_00 = SpawnPoint::GetRandom(Net::Team);
    if (this_00 == (SpawnPoint *)0x0) {
      if ((SpawnPoint::spawnPointList == (vector<SpawnPoint_*,std::allocator<SpawnPoint_*>_> *)0x0)
         || (((int)SpawnPoint::spawnPointList->_Mylast - (int)SpawnPoint::spawnPointList->_Myfirst &
             0xfffffffcU) == 0)) {
        pcVar5 = "Map has no spawn points";
      }
      else {
        pcVar5 = "Could not get a spawn point";
      }
      DEBUG_systemWarning(pcVar5);
      SetRunning(2);
      return;
    }
    pVVar7 = SpawnPoint::GetLocation(this_00);
    Net::SetStartLocation(theNet,pVVar7);
    uVar3 = Net::GetMyPlayerID(theNet);
    this_01 = NetPlayer::Find(uVar3);
    NetPlayer::SetWaitingForSpawnPoint(this_01,false);
    this_01->SpawnPointer = this_00;
    SpawnPoint::Assign(this_00,this_01);
  }
  Net::GetStartLocation(theNet,&local_30);
  pMVar12 = &Identity_Matrix;
  pMVar13 = &local_70;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar13->right_x = pMVar12->right_x;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  local_70.posit_x = (double)local_30.x;
  local_70.posit_y = (double)local_30.y;
  local_70.posit_z = (double)local_30.z;
  pGVar8 = GameObjectClass::Build(pGVar6,&local_70,Net::Team,1,-1,(char *)0x0);
  this_02 = operator_new(0x70);
  if (this_02 != (UserProcess *)0x0) {
    UserProcess::UserProcess(this_02,(AiMission *)local_24,pGVar8);
  }
  DistributedObject::SetLocal((DistributedObject *)&pGVar8->_padding_);
  if (pGVar8->curPilot == (GameObjectClass *)0x0) {
    iVar10 = (**(code **)pGVar8->_padding_)();
    if (pGVar8 == GameObject::userObject) {
      pGVar9 = *(GameObjectClass **)(iVar10 + 0xdc);
    }
    else {
      pGVar9 = *(GameObjectClass **)(iVar10 + 0xd8);
    }
    pGVar8->curPilot = pGVar9;
  }
  cVar1 = pGVar6->nation;
  if (((cVar1 == 'a') || (cVar1 == 's')) || (Net::bNations != false)) {
    local_1c = 0x706d;
    local_20 = CONCAT31(0x657276,cVar1);
    sprintf(local_18,"%.8s.odf");
    iVar10 = ItemExists(local_18);
    if (iVar10 == 0) {
      local_1c = 0x7963;
      local_20 = CONCAT31(0x657276,cVar1);
      sprintf(local_18,"%.8s.odf");
      iVar10 = ItemExists(local_18);
      if (iVar10 == 0) {
        local_20 = 0;
        local_1c = 0;
      }
    }
    if (local_20 != 0 || local_1c != 0) goto LAB_0044d6a5;
  }
  if ((cVar1 == 'c') || (uVar11 = 0x61, cVar1 == 's')) {
    uVar11 = 0x73;
  }
  local_1c = 0x706d;
  local_20 = CONCAT31(0x657276,uVar11);
  sprintf(local_18,"%.8s.odf");
  iVar10 = ItemExists(local_18);
  if (iVar10 == 0) {
    local_1c = 0x7963;
    local_20 = CONCAT31(0x657276,uVar11);
    sprintf(local_18,"%.8s.odf");
    ItemExists(local_18);
  }
LAB_0044d6a5:
  pGVar6 = GameObjectClass::Find(CONCAT44(local_1c,local_20));
  local_70.posit_x = local_70.posit_x + 20.0;
  local_70.posit_z = local_70.posit_z + 20.0;
  fVar14 = Terrain_FindFloor(local_70.posit_x,local_70.posit_z);
  local_70.posit_y = (double)(fVar14 + 2.0);
  pGVar8 = GameObjectClass::Build(pGVar6,&local_70,Net::Team,0,-1,(char *)0x0);
  Team::AddScrap(pGVar8->teamList,0x14);
  DistributedObject::SetLocal((DistributedObject *)&pGVar8->_padding_);
  (**(code **)(local_24->_padding_ + 0x18))();
  return;
}
