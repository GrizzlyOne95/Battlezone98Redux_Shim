/*
 * Entry: 0056ed40
 * Name: Read_Bitmap_8
 * Namespace: Global
 * Signature: int Read_Bitmap_8(tagBITMAPINFOHEADER * param_1, uchar * param_2, tagRGBQUAD * param_3, tagBITMAPINFO * * param_4, void * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Read_Bitmap_8(tagBITMAPINFOHEADER *param_1,uchar *param_2,tagRGBQUAD *param_3,
             tagBITMAPINFO **param_4,void **param_5)

{
  tagRGBQUAD tVar1;
  undefined2 *puVar2;
  tagBITMAPINFO *ptVar3;
  int iVar4;
  undefined4 *unaff_EBX;
  undefined4 *puVar5;
  
  tVar1 = (tagRGBQUAD)malloc(0x42c);
  *param_3 = tVar1;
  if (tVar1 == (tagRGBQUAD)0x0) {
    return 0;
  }
  puVar5 = unaff_EBX;
  for (iVar4 = 10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)tVar1 = *puVar5;
    puVar5 = puVar5 + 1;
    tVar1 = (tagRGBQUAD)((int)tVar1 + 4);
  }
  puVar2 = (undefined2 *)((int)*param_3 + 0x28);
  iVar4 = 0;
  do {
    *puVar2 = (short)iVar4;
    puVar2 = puVar2 + 1;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x100);
  memcpy(param_2,param_1,0x400);
  ptVar3 = malloc(unaff_EBX[1] * unaff_EBX[2]);
  *param_4 = ptVar3;
  if (ptVar3 != (tagBITMAPINFO *)0x0) {
    memcpy(ptVar3,&param_1[0x19].biXPelsPerMeter,unaff_EBX[1] * unaff_EBX[2]);
  }
  else {
    free((void *)*param_3);
    param_3->rgbBlue = '\0';
    param_3->rgbGreen = '\0';
    param_3->rgbRed = '\0';
    param_3->rgbReserved = '\0';
  }
  return (uint)(ptVar3 != (tagBITMAPINFO *)0x0);
}
