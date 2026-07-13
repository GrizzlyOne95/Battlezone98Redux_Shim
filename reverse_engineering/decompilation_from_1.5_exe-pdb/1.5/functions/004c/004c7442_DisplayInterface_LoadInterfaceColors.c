/*
 * Entry: 004c7442
 * Name: DisplayInterface::LoadInterfaceColors
 * Namespace: DisplayInterface
 * Signature: void LoadInterfaceColors(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DisplayInterface::LoadInterfaceColors(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  long lVar4;
  int iVar5;
  byte *pbVar6;
  uchar *puVar7;
  int local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar5 = 0;
  colorBlack = 0;
  colorDkGrey = Get_Closest_RGB_Entry(0.3,0.3,0.3);
  colorGrey = Get_Closest_RGB_Entry(0.6,0.6,0.6);
  colorWhite = Get_Closest_RGB_Entry(1.0,1.0,1.0);
  colorBlue = Get_Closest_RGB_Entry(0.0,0.5,1.0);
  colorDkBlue = Get_Closest_RGB_Entry(0.0,0.3,0.6);
  colorGreen = Get_Closest_RGB_Entry(0.0,1.0,0.0);
  colorDkGreen = Get_Closest_RGB_Entry(0.0,0.6,0.0);
  colorYellow = Get_Closest_RGB_Entry(1.0,1.0,0.0);
  colorDkYellow = Get_Closest_RGB_Entry(0.6,0.6,0.0);
  colorRed = Get_Closest_RGB_Entry(1.0,0.0,0.0);
  colorDkRed = Get_Closest_RGB_Entry(0.6,0.0,0.0);
  colorCyan = Get_Closest_RGB_Entry(0.0,1.0,1.0);
  colorDkCyan = Get_Closest_RGB_Entry(0.0,0.6,0.6);
  pbVar6 = &DAT_0062c431;
  do {
    bVar1 = pbVar6[-1];
    bVar2 = *pbVar6;
    bVar3 = pbVar6[1];
    puVar7 = colorRamp[0] + iVar5;
    local_14 = 0x10;
    local_10 = 0.0;
    local_c = 0.0;
    local_8 = 0.0;
    do {
      local_10 = local_10 + (float)bVar1 * 0.00024509805;
      local_c = local_c + (float)bVar2 * 0.00024509805;
      local_8 = local_8 + (float)bVar3 * 0.00024509805;
      lVar4 = Get_Closest_RGB_Entry(local_10,local_c,local_8);
      *puVar7 = (uchar)lVar4;
      puVar7 = puVar7 + 0x100;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
    pbVar6 = pbVar6 + 3;
    iVar5 = iVar5 + 1;
  } while ((int)pbVar6 < 0x62c731);
  return;
}
