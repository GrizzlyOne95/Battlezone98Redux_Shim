/*
 * Entry: 00581e9b
 * Name: DrawWrappedText
 * Namespace: Global
 * Signature: long DrawWrappedText(HDC__ * param_1, tagRECT * param_2, char * param_3, long param_4, long param_5, _GRAPHIC_BUFFER * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
DrawWrappedText(HDC__ *param_1,tagRECT *param_2,char *param_3,long param_4,long param_5,
               _GRAPHIC_BUFFER *param_6)

{
  int x;
  char cVar1;
  char *pcVar2;
  long lVar3;
  WRAP_INFO *pWVar4;
  int iVar5;
  int nMaxExtent;
  BITMAP_OPER BVar6;
  int local_38;
  WRAP_INFO local_2c;
  int local_20;
  int local_1c;
  char *local_18;
  tagSIZE local_14;
  int local_c;
  int local_8;
  
  x = param_2->left;
  local_38 = param_2->top;
  nMaxExtent = param_2->right - x;
  pcVar2 = param_3;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  local_8 = nMaxExtent;
  GetTextExtentExPointA
            ((HDC)param_1,param_3,(int)pcVar2 - (int)(param_3 + 1),nMaxExtent,&local_c,(LPINT)0x0,
             &local_14);
  iVar5 = local_14.cy / 2 + local_38;
  while( true ) {
    pWVar4 = FindWrappingPoint(&local_2c,param_3,nMaxExtent,GetWrapInfoFromDC,param_1);
    local_20 = pWVar4->NumChars;
    local_1c = pWVar4->NumBytes;
    local_18 = pWVar4->NextStr;
    if (local_20 == 0) break;
    TextOutA((HDC)param_1,x,local_38,param_3,local_1c);
    if (param_6 != (_GRAPHIC_BUFFER *)0x0) {
      GetTextExtentPoint32A((HDC)param_1,param_3,local_1c,&local_14);
      BVar6 = SOLID_PIXELS;
      lVar3 = Get_Closest_RGB_Entry(0.2,0.2,0.2);
      Graphic_Line(param_6,x,iVar5,local_14.cx,iVar5,lVar3,BVar6);
    }
    local_38 = local_38 + param_4;
    iVar5 = iVar5 + param_4;
    param_3 = local_18;
    nMaxExtent = local_8;
  }
  return local_38 - param_2->top;
}
