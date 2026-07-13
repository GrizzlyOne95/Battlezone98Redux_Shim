/*
 * Entry: 0056eed9
 * Name: Read_Bitmap_24
 * Namespace: Global
 * Signature: int Read_Bitmap_24(tagBITMAPINFOHEADER * param_1, uchar * param_2, tagRGBQUAD * param_3, tagBITMAPINFO * * param_4, void * * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Read_Bitmap_24(tagBITMAPINFOHEADER *param_1,uchar *param_2,tagRGBQUAD *param_3,
              tagBITMAPINFO **param_4,void **param_5)

{
  tagRGBQUAD tVar1;
  undefined2 *puVar2;
  tagBITMAPINFO *ptVar3;
  uint uVar4;
  int iVar5;
  tagBITMAPINFOHEADER *ptVar6;
  size_t _Size;
  
  tVar1 = (tagRGBQUAD)malloc(0x42c);
  *param_3 = tVar1;
  uVar4 = 0;
  if (tVar1 != (tagRGBQUAD)0x0) {
    ptVar6 = param_1;
    for (iVar5 = 10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(ulong *)tVar1 = ptVar6->biSize;
      ptVar6 = (tagBITMAPINFOHEADER *)&ptVar6->biWidth;
      tVar1 = (tagRGBQUAD)((int)tVar1 + 4);
    }
    puVar2 = (undefined2 *)((int)*param_3 + 0x28);
    iVar5 = 0;
    do {
      *puVar2 = (short)iVar5;
      puVar2 = puVar2 + 1;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0x100);
    _Size = param_1->biHeight * param_1->biWidth * 3;
    ptVar3 = malloc(_Size);
    *param_4 = ptVar3;
    if (ptVar3 != (tagBITMAPINFO *)0x0) {
      memcpy(ptVar3,param_2,_Size);
    }
    else {
      free((void *)*param_3);
      param_3->rgbBlue = '\0';
      param_3->rgbGreen = '\0';
      param_3->rgbRed = '\0';
      param_3->rgbReserved = '\0';
    }
    uVar4 = (uint)(ptVar3 != (tagBITMAPINFO *)0x0);
  }
  return uVar4;
}
