/*
 * Entry: 00471c42
 * Name: CDInit
 * Namespace: Global
 * Signature: int CDInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CDInit(void)

{
  char cVar1;
  MCIERROR MVar2;
  undefined4 local_28;
  MCIDEVICEID local_24;
  undefined4 local_20;
  char *local_1c;
  undefined4 uStack_18;
  undefined1 local_14 [4];
  undefined4 local_10;
  char local_8 [4];
  
  cVar1 = CDDriveLetter();
  if (cVar1 == '\0') {
    return 1;
  }
  cVar1 = CDDriveLetter();
  sprintf(local_8,"%c:",(int)cVar1);
  local_28 = 0;
  local_24 = 0;
  uStack_18 = 0;
  local_1c = local_8;
  local_20 = 0x204;
  MVar2 = mciSendCommandA(0,0x803,0x3302,(DWORD_PTR)&local_28);
  if (MVar2 == 0) {
    CD_DeviceID = local_24;
    local_10 = 10;
    MVar2 = mciSendCommandA(local_24,0x80d,0x400,(DWORD_PTR)local_14);
    if (MVar2 == 0) {
      auxCDRomID = CDInitVolume();
      return 0;
    }
    CDDone();
    MVar2 = CDError;
  }
  CDError = MVar2;
  return 1;
}
