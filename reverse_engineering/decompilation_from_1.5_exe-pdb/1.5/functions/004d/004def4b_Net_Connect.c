/*
 * Entry: 004def4b
 * Name: Net::Connect
 * Namespace: Net
 * Signature: void Connect(Net * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::Connect(Net *this)

{
  uchar uVar1;
  int iVar2;
  char *pcVar3;
  
  if (hosting) {
    memset(&sDesc,0,0x5f);
    sDesc.field7_0x15.flags = 0x41;
    sDesc.field3_0xd.sessionType = session_type;
    sDesc.field0_0x0.dummy = '_';
    iVar2 = 0;
    do {
      uVar1 = gameName[iVar2];
      sDesc.adrMaster[iVar2 + 0x16] = uVar1;
      iVar2 = iVar2 + 1;
    } while (uVar1 != '\0');
    strncpy(sDesc.szUserField,&msn_filename,10);
    pcVar3 = strchr(sDesc.szUserField,0x2e);
    if (pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
    }
    sDesc.field5_0x11.maxPlayers = 0x1e;
    this->state = WAITING_FOR_OPEN;
    sDesc.dwUser1 = crc32mission(MissionFileName);
    iVar2 = dpOpen(dp,&sDesc,dpOpenCallback,this);
    if (iVar2 != 0) {
      DEBUG_systemError("Failed to open network connection");
    }
  }
  else {
    bFoundSession = false;
    iVar2 = dpEnumSessions(dp,&sDesc,0,this->dpEnumSessionsTimeout,dpEnumSessionsCallback,this);
    if (iVar2 != 0) {
      DEBUG_systemError("Failed to enum sessions");
    }
    this->state = WAITING_FOR_ENUM_SESSIONS;
  }
  return;
}
