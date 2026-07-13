/*
 * Entry: 0056edd6
 * Name: Read_Bitmap_8_24
 * Namespace: Global
 * Signature: int Read_Bitmap_8_24(tagBITMAPINFOHEADER * param_1, uchar * param_2, tagRGBQUAD * param_3, tagBITMAPINFO * * param_4, void * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Read_Bitmap_8_24(tagBITMAPINFOHEADER *param_1,uchar *param_2,tagRGBQUAD *param_3,
                tagBITMAPINFO **param_4,void **param_5)

{
  uchar *puVar1;
  ulong *puVar2;
  tagRGBQUAD tVar3;
  undefined2 *puVar4;
  tagBITMAPINFO *ptVar5;
  int iVar6;
  uchar *puVar7;
  int iVar8;
  undefined4 *unaff_EBX;
  undefined4 *puVar9;
  uint uVar10;
  int local_10;
  uchar *local_c;
  tagBITMAPINFOHEADER *local_8;
  
  tVar3 = (tagRGBQUAD)malloc(0x42c);
  *param_3 = tVar3;
  if (tVar3 != (tagRGBQUAD)0x0) {
    puVar9 = unaff_EBX;
    for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *(undefined4 *)tVar3 = *puVar9;
      puVar9 = puVar9 + 1;
      tVar3 = (tagRGBQUAD)((int)tVar3 + 4);
    }
    *(undefined2 *)((int)*param_3 + 0xe) = 0x18;
    puVar4 = (undefined2 *)((int)*param_3 + 0x28);
    iVar6 = 0;
    do {
      *puVar4 = (short)iVar6;
      puVar4 = puVar4 + 1;
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0x100);
    memcpy(param_2,param_1,0x400);
    local_8 = (tagBITMAPINFOHEADER *)&param_1[0x19].biXPelsPerMeter;
    iVar6 = unaff_EBX[1];
    uVar10 = (iVar6 + 1) * 3 & 0xfffffffc;
    ptVar5 = malloc(unaff_EBX[2] * uVar10);
    *param_4 = ptVar5;
    if (ptVar5 == (tagBITMAPINFO *)0x0) {
      free((void *)*param_3);
      param_3->rgbBlue = '\0';
      param_3->rgbGreen = '\0';
      param_3->rgbRed = '\0';
      param_3->rgbReserved = '\0';
      iVar6 = 0;
    }
    else {
      local_10 = 0;
      if (0 < (int)unaff_EBX[2]) {
        iVar8 = unaff_EBX[1];
        local_c = (uchar *)((int)&(ptVar5->bmiHeader).biSize + 1);
        do {
          param_3 = (tagRGBQUAD *)0x0;
          param_1 = local_8;
          puVar7 = local_c;
          if (0 < iVar8) {
            do {
              puVar2 = &param_1->biSize;
              param_1 = (tagBITMAPINFOHEADER *)((int)&param_1->biSize + 1);
              puVar1 = param_2 + (uint)(byte)*puVar2 * 4;
              puVar7[1] = puVar1[2];
              *puVar7 = puVar1[1];
              puVar7[-1] = *puVar1;
              iVar8 = unaff_EBX[1];
              param_3 = (tagRGBQUAD *)&param_3->rgbGreen;
              puVar7 = puVar7 + 3;
            } while ((int)param_3 < iVar8);
          }
          local_8 = (tagBITMAPINFOHEADER *)((int)&local_8->biSize + (iVar6 + 3U & 0xfffffffc));
          local_c = local_c + uVar10;
          local_10 = local_10 + 1;
        } while (local_10 < (int)unaff_EBX[2]);
      }
      iVar6 = 1;
    }
    return iVar6;
  }
  return 0;
}
