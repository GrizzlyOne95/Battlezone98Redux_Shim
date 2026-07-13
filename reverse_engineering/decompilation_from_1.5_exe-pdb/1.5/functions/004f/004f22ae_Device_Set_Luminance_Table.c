/*
 * Entry: 004f22ae
 * Name: Device_Set_Luminance_Table
 * Namespace: Global
 * Signature: void Device_Set_Luminance_Table(VIDEO_DEVICE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Device_Set_Luminance_Table(VIDEO_DEVICE *param_1,char *param_2)

{
  uchar (*pauVar1) [256];
  int iVar2;
  
  pauVar1 = Luminance_Table;
  do {
    iVar2 = 0x100;
    do {
      *(char *)pauVar1 = (param_2 + -0xd1e480)[(int)pauVar1];
      pauVar1 = (uchar (*) [256])((int)pauVar1 + 1);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  } while ((int)pauVar1 < 0xd2e480);
  Fill_Luminance_Extras();
  return;
}
