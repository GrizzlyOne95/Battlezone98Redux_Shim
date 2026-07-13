/*
 * Entry: 004f1f34
 * Name: Device_Init_Chrome_Key_Table
 * Namespace: Global
 * Signature: void Device_Init_Chrome_Key_Table(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Device_Init_Chrome_Key_Table(VIDEO_DEVICE *param_1)

{
  int iVar1;
  uchar (*pauVar2) [256];
  
  iVar1 = 0;
  pauVar2 = Chrome_Key_Table;
  do {
    (&Reset_Chroma)[iVar1] = (char)iVar1;
    memset(pauVar2,iVar1,0x100);
    pauVar2 = pauVar2 + 1;
    iVar1 = iVar1 + 1;
  } while ((int)pauVar2 < 0xd0e440);
  memset(&DAT_00d3fda0,0xff,0x100);
  return;
}
