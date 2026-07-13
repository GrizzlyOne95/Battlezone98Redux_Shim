/*
 * Entry: 00471fd3
 * Name: pDiscInit
 * Namespace: Global
 * Signature: int pDiscInit(Disc * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl pDiscInit(Disc *param_1)

{
  MCIERROR MVar1;
  int iVar2;
  int *unaff_ESI;
  int iVar3;
  undefined1 local_14 [4];
  int local_10;
  undefined4 local_c;
  int local_8;
  
  if (CD_OK == 0) {
    return 1;
  }
  local_c = 3;
  MVar1 = mciSendCommandA(CD_DeviceID,0x814,0x100,(DWORD_PTR)local_14);
  if (MVar1 == 0) {
    iVar2 = local_10;
    if (0x32 < local_10) {
      iVar2 = 0x32;
    }
    iVar3 = 1;
    *unaff_ESI = 1;
    unaff_ESI[1] = iVar2;
    if (0 < iVar2) {
      do {
        local_c = 2;
        local_8 = iVar3;
        MVar1 = mciSendCommandA(CD_DeviceID,0x814,0x110,(DWORD_PTR)local_14);
        if (MVar1 != 0) {
          PlayerDone();
          return 0;
        }
        iVar2 = iVar3 - *unaff_ESI;
        iVar3 = iVar3 + 1;
        unaff_ESI[iVar2 + 2] = local_10;
      } while (iVar3 <= unaff_ESI[1]);
    }
    unaff_ESI[(iVar3 - *unaff_ESI) + 2] = (uint)(byte)((char)unaff_ESI[1] + 1);
  }
  else {
    PlayerDone();
  }
  return 0;
}
