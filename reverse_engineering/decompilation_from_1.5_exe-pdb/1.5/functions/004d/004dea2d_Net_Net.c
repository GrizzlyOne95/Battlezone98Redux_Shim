/*
 * Entry: 004dea2d
 * Name: Net::Net
 * Namespace: Net
 * Signature: Net * Net(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

Net * __thiscall Net::Net(Net *this)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 local_16c;
  int local_168;
  ulong local_158;
  ulong local_150;
  Net *local_144;
  undefined4 local_140;
  char local_13c [128];
  undefined1 local_bc [12];
  char local_b0 [40];
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  respawn_timer = 0.0;
  VictoryTime = 0.0;
  respawn = 0;
  bStopGame = false;
  sentsyncs = 1;
  this->bDoNetSync = false;
  this->dwLastBandWidthSendTime = 0;
  local_144 = this;
  NextPositionPacketSendTime = Get_TimeNow();
  dwLastByteSentTime = NextPositionPacketSendTime;
  this->dwNextScoreTime = 0;
  this->state = INITIAL;
  if (bFoundSession != false) {
    this->state = FINISHED_ENUM_SESSIONS;
  }
  this->got_start_location = false;
  sDesc.field3_0xd.sessionType = session_type;
  params.reqLen = 0x2c;
  sDesc.field0_0x0.dummy = '_';
  this->dpEnumSessionsTimeout = 10000;
  myPlayerID = 0xfa01;
  this->dwLastPing = 0;
  this->dwLastSpawn = 0;
  Chat_Init();
  ALLIE_Init();
  Scores_Init();
  if ((bSyncJoin == false) && (bNewGame == false)) {
    if (bNetShell == false) {
      if (dp == (dp_s *)0x0) {
        memset(&sDesc,0,0x5f);
        sDesc.field3_0xd.sessionType = session_type;
        sDesc.field0_0x0.dummy = '_';
        iVar2 = 0;
        do {
          cVar1 = transport[iVar2];
          local_13c[iVar2] = cVar1;
          iVar2 = iVar2 + 1;
        } while (cVar1 != '\0');
        dpCreate(&dp,local_13c,&params,0);
        if ((hostname[0] != '\0') &&
           ((pcVar3 = strstr(local_13c,"winet"), pcVar3 != (char *)0x0 ||
            (pcVar3 = strstr(local_13c,"WINET"), pcVar3 != (char *)0x0)))) {
          dpSetGameServer(dp,hostname);
        }
      }
      local_16c = 0x28;
      dpGetCaps(dp,&local_16c,0);
      goto LAB_004decd5;
    }
    this->state = WAITING_FOR_CREATE_PLAYER;
    dpCreate(&dp,0,0,"freeze.dat");
    local_140 = 0x5f;
    dpGetSessionDesc(dp,&sDesc,&local_140);
    dpEnumPlayers(dp,0,dpEnumPlayersCallback,this,0x6d6);
    local_16c = 0x28;
    dpGetCaps(dp,&local_16c,0);
  }
  else {
    this->state = FINISHED_CREATE_PLAYER;
    local_140 = 0x5f;
    dpGetSessionDesc(dp,&sDesc,&local_140);
    dpEnumPlayers(dp,0,dpEnumPlayersCallback,this,0x6d6);
    local_16c = 0x28;
    dpGetCaps(dp,&local_16c,0);
  }
  if (local_168 == 1) {
    hosting = true;
  }
LAB_004decd5:
  this->dwMaxBufferSize = local_158;
  this->dwMaxPlayers = local_150;
  DistributedObject_SetDP(dp);
  this->ping = (PING_PACKET *)(this->buffer + 2);
  this->ping_master_send_time = (ulong *)(this->buffer + 2);
  this->pingreply_buffer[0] = 'P';
  this->pingreply_buffer[1] = 'R';
  this->pingreply = (PINGREPLY_PACKET *)(this->pingreply_buffer + 2);
  this->pingreply_master_send_time = (ulong *)(this->pingreply_buffer + 2);
  this->dwNextPing = 300;
  this->pingreply_slave_received_time = (ulong *)(this->pingreply_buffer + 6);
  DivisorMPPI2NPPI = 3;
  DivisorPing2NPPI = 3;
  LimitLowNPPI = 0x32;
  LimitHiNPPI = 0x14d;
  MaxPing = GetPrivateProfileIntA("Net","MaxPing",700,".\\net.ini");
  UpCount = GetPrivateProfileIntA("Net","UpCount",7,".\\net.ini");
  dwMinBandwidth = GetPrivateProfileIntA("Net","MinBandwidth",dwMinBandwidth,".\\net.ini");
  dwMaxBandwidth = GetPrivateProfileIntA("Net","MaxBandwidth",dwMaxBandwidth,".\\net.ini");
  bUseCompression = GetPrivateProfileIntA("Net","UseCompression",bUseCompression,".\\net.ini");
  bRemovePlayerOnKick =
       GetPrivateProfileIntA("Net","RemovePlayerOnKick",bUseCompression,".\\net.ini");
  dwAutoKickStart = GetPrivateProfileIntA("Net","AutoKickStart",dwAutoKickStart,".\\net.ini");
  dwAutoKickPing = GetPrivateProfileIntA("Net","AutoKickPing",dwAutoKickPing,".\\net.ini");
  dwAutoKickLoss = GetPrivateProfileIntA("Net","AutoKickLoss",dwAutoKickLoss,".\\net.ini");
  dwAutoKickTime = GetPrivateProfileIntA("Net","AutoKickTime",dwAutoKickTime,".\\net.ini");
  iVar2 = dpGetCurrentTransportInfo(dp,local_88,local_bc);
  bInternetGame = true;
  if (iVar2 == 0) {
    bInternetGame = true;
    iVar2 = 9;
    pcVar3 = local_b0;
    pcVar4 = "Internet";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bInternetGame = *pcVar3 == *pcVar4;
      pcVar3 = pcVar3 + 1;
      pcVar4 = pcVar4 + 1;
    } while (bInternetGame);
    pcVar3 = strrchr(local_88,0x2e);
    this = local_144;
    if (pcVar3 != (char *)0x0) {
      builtin_strncpy(pcVar3,".ini",5);
      LimitLowNPPI = GetPrivateProfileIntA("Net","LimitLowNPPI",LimitLowNPPI,local_88);
      LimitHiNPPI = GetPrivateProfileIntA("Net","LimitHiNPPI",LimitHiNPPI,local_88);
      DivisorMPPI2NPPI = GetPrivateProfileIntA("Net","DivisorMPPI2NPPI",DivisorMPPI2NPPI,local_88);
      DivisorPing2NPPI = GetPrivateProfileIntA("Net","DivisorPing2NPPI",DivisorPing2NPPI,local_88);
      this = local_144;
    }
  }
  return this;
}
