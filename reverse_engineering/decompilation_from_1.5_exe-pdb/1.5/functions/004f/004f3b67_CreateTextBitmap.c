/*
 * Entry: 004f3b67
 * Name: CreateTextBitmap
 * Namespace: Global
 * Signature: _GRAPHIC_BUFFER * CreateTextBitmap(_GRAPHIC_BUFFER * __return_storage_ptr__, HDC__ * param_1, long param_2, long param_3, HBITMAP__ * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_GRAPHIC_BUFFER * __cdecl
CreateTextBitmap(_GRAPHIC_BUFFER *__return_storage_ptr__,HDC__ *param_1,long param_2,long param_3,
                HBITMAP__ **param_4)

{
  long lVar1;
  BYTE *pBVar2;
  HBITMAP pHVar3;
  _GRAPHIC_BUFFER *p_Var4;
  BYTE *pBVar5;
  int iVar6;
  _GRAPHIC_BUFFER *p_Var7;
  BITMAPINFO local_460 [24];
  _GRAPHIC_BUFFER local_38;
  
  memset(local_460,0,0x428);
  lVar1 = param_2;
  local_460[0].bmiHeader.biHeight = -param_3;
  local_460[0].bmiHeader.biPlanes = 1;
  local_460[0].bmiHeader.biBitCount = 8;
  local_460[0].bmiHeader.biWidth = param_2;
  local_460[0].bmiHeader.biSize = 0x28;
  local_460[0].bmiHeader.biCompression = 0;
  pBVar2 = &local_460[0].bmiColors[0].rgbGreen;
  pBVar5 = &DAT_0062c431;
  do {
    ((RGBQUAD *)(pBVar2 + -1))->rgbBlue = pBVar5[-1];
    *pBVar2 = *pBVar5;
    pBVar2[1] = pBVar5[1];
    pBVar2[2] = '\0';
    pBVar5 = pBVar5 + 3;
    pBVar2 = pBVar2 + 4;
  } while ((int)pBVar5 < 0x62c731);
  pHVar3 = CreateDIBSection((HDC)param_1,local_460,0,(void **)&param_2,(HANDLE)0x0,0);
  *param_4 = (HBITMAP__ *)pHVar3;
  if (pHVar3 == (HBITMAP)0x0) {
    memset(&local_38,0,0x34);
    p_Var4 = &local_38;
  }
  else {
    RealizePalette((HDC)param_1);
    p_Var4 = Graphic_Buffer_Init_Ex(&local_38,lVar1,param_3,(char *)param_2,BYTES_FORMAT);
  }
  p_Var7 = __return_storage_ptr__;
  for (iVar6 = 0xd; iVar6 != 0; iVar6 = iVar6 + -1) {
    p_Var7->Width = p_Var4->Width;
    p_Var4 = (_GRAPHIC_BUFFER *)&p_Var4->Height;
    p_Var7 = (_GRAPHIC_BUFFER *)&p_Var7->Height;
  }
  return __return_storage_ptr__;
}
