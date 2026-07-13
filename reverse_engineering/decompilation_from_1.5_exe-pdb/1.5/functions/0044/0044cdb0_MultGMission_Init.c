/*
 * Entry: 0044cdb0
 * Name: MultGMission::Init
 * Namespace: MultGMission
 * Signature: void Init(MultGMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MultGMission::Init(MultGMission *this)

{
  float fVar1;
  float fVar2;
  char *pcVar3;
  ushort uVar4;
  MultGEvent *this_00;
  int iVar5;
  char *pcVar6;
  NetPlayer *this_01;
  AiPath *pAVar7;
  GameObject *pGVar8;
  UserProcess *this_02;
  GameObjectClass *pGVar9;
  MAT_3D *pMVar10;
  MAT_3D *pMVar11;
  MAT_3D local_68;
  AiMission *local_28;
  undefined4 local_24;
  GameObjectClass *local_20;
  char local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (theNet != (Net *)0x0) {
    Net::MessageHandler = MyMessageHandler;
    local_28 = (AiMission *)this;
    this_00 = operator_new(0x40c);
    if (this_00 == (MultGEvent *)0x0) {
      multGEvent = (MultGEvent *)0x0;
    }
    else {
      multGEvent = MultGEvent::MultGEvent(this_00,local_28);
    }
    Net::SetDeathMatch(true);
    iVar5 = Net_IsNetGame();
    if (iVar5 != 0) {
      local_24 = 0;
      local_20 = (GameObjectClass *)0x0;
      pcVar3 = Net::odfName;
      do {
        pcVar6 = pcVar3;
        pcVar3 = pcVar6 + 1;
      } while (*pcVar6 != '\0');
      memcpy(&local_24,Net::odfName,pcVar6 + -0x62a994);
      local_20 = GameObjectClass::Find(CONCAT44(local_20,local_24));
      uVar4 = Net::GetMyPlayerID(theNet);
      this_01 = NetPlayer::Find(uVar4);
      NetPlayer::SetWaitingForSpawnPoint(this_01,false);
      sprintf(local_1c,"team%da",Net::Team);
      pAVar7 = AiPath::Find(local_1c);
      fVar1 = pAVar7->points->x;
      fVar2 = pAVar7->points->z;
      pMVar10 = &Identity_Matrix;
      pMVar11 = &local_68;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar11->right_x = pMVar10->right_x;
        pMVar10 = (MAT_3D *)&pMVar10->right_y;
        pMVar11 = (MAT_3D *)&pMVar11->right_y;
      }
      local_68.posit_x = (double)fVar1;
      local_68.posit_y = 0.0;
      local_68.posit_z = (double)fVar2;
      pGVar8 = GameObjectClass::Build(local_20,&local_68,Net::Team,1,-1,(char *)0x0);
      DistributedObject::SetLocal((DistributedObject *)&pGVar8->_padding_);
      this_02 = operator_new(0x70);
      if (this_02 != (UserProcess *)0x0) {
        UserProcess::UserProcess(this_02,local_28,pGVar8);
      }
      if (pGVar8->curPilot == (GameObjectClass *)0x0) {
        iVar5 = (**(code **)pGVar8->_padding_)();
        if (pGVar8 == GameObject::userObject) {
          pGVar9 = *(GameObjectClass **)(iVar5 + 0xdc);
        }
        else {
          pGVar9 = *(GameObjectClass **)(iVar5 + 0xd8);
        }
        pGVar8->curPilot = pGVar9;
      }
    }
  }
  return;
}
