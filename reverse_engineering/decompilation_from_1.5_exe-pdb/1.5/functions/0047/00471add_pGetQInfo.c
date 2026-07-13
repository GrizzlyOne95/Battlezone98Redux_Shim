/*
 * Entry: 00471add
 * Name: pGetQInfo
 * Namespace: Global
 * Signature: void pGetQInfo(PS * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl pGetQInfo(PS *param_1)

{
  MCIERROR MVar1;
  uint *unaff_ESI;
  undefined1 local_14 [4];
  uint local_10;
  undefined4 local_c;
  
  if (CD_OK != 0) {
    local_c = 2;
    MVar1 = mciSendCommandA(CD_DeviceID,0x814,0x100,(DWORD_PTR)local_14);
    if (MVar1 == 0) {
      *unaff_ESI = local_10 & 0xff;
      unaff_ESI[1] = local_10 >> 8 & 0xff;
      unaff_ESI[2] = local_10 >> 0x10 & 0xff;
      unaff_ESI[3] = local_10 >> 0x18;
    }
  }
  return;
}
