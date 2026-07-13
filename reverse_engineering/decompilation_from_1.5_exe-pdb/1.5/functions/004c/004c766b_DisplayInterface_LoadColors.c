/*
 * Entry: 004c766b
 * Name: DisplayInterface_LoadColors
 * Namespace: Global
 * Signature: void DisplayInterface_LoadColors(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface_LoadColors(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  int iVar5;
  byte *pbVar6;
  uchar *puVar7;
  int iStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  iVar5 = 0;
  DisplayInterface::colorBlack = 0;
  DisplayInterface::colorDkGrey = Get_Closest_RGB_Entry(0.3,0.3,0.3);
  DisplayInterface::colorGrey = Get_Closest_RGB_Entry(0.6,0.6,0.6);
  DisplayInterface::colorWhite = Get_Closest_RGB_Entry(1.0,1.0,1.0);
  DisplayInterface::colorBlue = Get_Closest_RGB_Entry(0.0,0.5,1.0);
  DisplayInterface::colorDkBlue = Get_Closest_RGB_Entry(0.0,0.3,0.6);
  DisplayInterface::colorGreen = Get_Closest_RGB_Entry(0.0,1.0,0.0);
  DisplayInterface::colorDkGreen = Get_Closest_RGB_Entry(0.0,0.6,0.0);
  DisplayInterface::colorYellow = Get_Closest_RGB_Entry(1.0,1.0,0.0);
  DisplayInterface::colorDkYellow = Get_Closest_RGB_Entry(0.6,0.6,0.0);
  DisplayInterface::colorRed = Get_Closest_RGB_Entry(1.0,0.0,0.0);
  DisplayInterface::colorDkRed = Get_Closest_RGB_Entry(0.6,0.0,0.0);
  DisplayInterface::colorCyan = Get_Closest_RGB_Entry(0.0,1.0,1.0);
  DisplayInterface::colorDkCyan = Get_Closest_RGB_Entry(0.0,0.6,0.6);
  pbVar6 = &DAT_0062c431;
  do {
    bVar1 = pbVar6[-1];
    bVar2 = *pbVar6;
    bVar3 = pbVar6[1];
    puVar7 = DisplayInterface::colorRamp[0] + iVar5;
    iStack_14 = 0x10;
    fStack_10 = 0.0;
    fStack_c = 0.0;
    fStack_8 = 0.0;
    do {
      fStack_10 = fStack_10 + (float)bVar1 * 0.00024509805;
      fStack_c = fStack_c + (float)bVar2 * 0.00024509805;
      fStack_8 = fStack_8 + (float)bVar3 * 0.00024509805;
      lVar4 = Get_Closest_RGB_Entry(fStack_10,fStack_c,fStack_8);
      *puVar7 = (uchar)lVar4;
      puVar7 = puVar7 + 0x100;
      iStack_14 = iStack_14 + -1;
    } while (iStack_14 != 0);
    pbVar6 = pbVar6 + 3;
    iVar5 = iVar5 + 1;
  } while ((int)pbVar6 < 0x62c731);
  return;
}
