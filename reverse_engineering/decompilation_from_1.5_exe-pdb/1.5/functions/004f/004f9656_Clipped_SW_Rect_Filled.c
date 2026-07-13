/*
 * Entry: 004f9656
 * Name: Clipped_SW_Rect_Filled
 * Namespace: Global
 * Signature: void Clipped_SW_Rect_Filled(_GRAPHIC_BUFFER * param_1, long param_2, long param_3, long param_4, long param_5, long param_6, BITMAP_OPER param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Clipped_SW_Rect_Filled
          (_GRAPHIC_BUFFER *param_1,long param_2,long param_3,long param_4,long param_5,long param_6
          ,BITMAP_OPER param_7)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  
  iVar4 = (param_1->Width - param_4) + -1 + param_2;
  pbVar3 = param_1->Buffer + param_2 + param_1->Width * param_3;
  if (param_7 == ONE_THIRD_TRANSLUCENT_PIXELS) {
    if (param_3 <= param_5) {
      iVar1 = (param_5 - param_3) + 1;
      do {
        if (param_2 <= param_4) {
          iVar2 = (param_4 - param_2) + 1;
          do {
            *pbVar3 = Translucency_Table[param_6][*pbVar3];
            pbVar3 = pbVar3 + 1;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        pbVar3 = pbVar3 + iVar4;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  else if (param_7 == TWO_THIRD_TRANSLUCENT_PIXELS) {
    if (param_3 <= param_5) {
      iVar1 = (param_5 - param_3) + 1;
      do {
        if (param_2 <= param_4) {
          iVar2 = (param_4 - param_2) + 1;
          do {
            *pbVar3 = Translucency_Table[*pbVar3][param_6];
            pbVar3 = pbVar3 + 1;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        pbVar3 = pbVar3 + iVar4;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  else if (param_7 == ALPHA_PIXELS) {
    if (param_3 <= param_5) {
      iVar1 = (param_5 - param_3) + 1;
      do {
        if (param_2 <= param_4) {
          iVar2 = (param_4 - param_2) + 1;
          do {
            *pbVar3 = Headlight_Mask_Luma[param_6][*pbVar3];
            pbVar3 = pbVar3 + 1;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        pbVar3 = pbVar3 + iVar4;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  else {
    for (iVar4 = (param_5 - param_3) + 1; 0 < iVar4; iVar4 = iVar4 + -1) {
      memset(pbVar3,param_6 & 0xff,(param_4 - param_2) + 1);
      pbVar3 = pbVar3 + param_1->Width;
    }
  }
  return;
}
