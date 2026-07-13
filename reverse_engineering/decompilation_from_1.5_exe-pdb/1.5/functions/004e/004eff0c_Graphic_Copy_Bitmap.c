/*
 * Entry: 004eff0c
 * Name: Graphic_Copy_Bitmap
 * Namespace: Global
 * Signature: void Graphic_Copy_Bitmap(_GRAPHIC_BUFFER * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, BITMAP_OPER param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Graphic_Copy_Bitmap(_GRAPHIC_BUFFER *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,
                   BITMAP_OPER param_5)

{
  PANE *pPVar1;
  char *pcVar2;
  long lVar3;
  int iVar4;
  uchar *puVar5;
  int iVar6;
  int iVar7;
  long unaff_EBX;
  long unaff_ESI;
  long unaff_EDI;
  uchar *puVar8;
  int iVar9;
  PANE local_24;
  uchar *local_14;
  ushort *local_10;
  _GRAPHIC_BUFFER *local_c;
  uchar *local_8;
  
  if ((param_1->Status != 0) && (param_2->Status != 0)) {
    local_24.y0 = (param_1->Pane).y0 + param_4;
    pPVar1 = &param_1->Pane;
    local_24.x0 = pPVar1->x0 + param_3;
    local_24.x1 = ((param_2->Pane).x1 - (param_2->Pane).x0) + local_24.x0;
    local_24.y1 = ((param_2->Pane).y1 - (param_2->Pane).y0) + local_24.y0;
    lVar3 = Clip_Pane(&local_24,pPVar1);
    if (-1 < lVar3) {
      iVar4 = (((param_2->Pane).x0 - param_3) - pPVar1->x0) + local_24.x0;
      iVar7 = (((param_2->Pane).y0 - param_4) - (param_1->Pane).y0) + local_24.y0;
      local_8 = (uchar *)((local_24.x1 - local_24.x0) + 1);
      local_c = (_GRAPHIC_BUFFER *)((local_24.y1 - local_24.y0) + 1);
      iVar9 = param_2->Bit_Depth + param_1->Bit_Depth * 2;
      if (iVar9 == 0) {
        pcVar2 = (char *)param_1->Width;
        local_14 = param_2->Buffer;
        local_10 = (ushort *)param_2->Width;
        puVar5 = param_1->Buffer + local_24.x0 + (int)pcVar2 * local_24.y0;
        puVar8 = local_14 + iVar4 + (int)local_10 * iVar7;
        iVar9 = (int)local_10;
        if (param_5 != TRANSPARENT_PIXELS) {
          if (param_5 == ONE_THIRD_TRANSLUCENT_PIXELS) {
            Blit_Translucent_Bitmap
                      ((char *)puVar5,(char *)puVar8,(long)local_8,(long)local_c,(long)pcVar2,
                       (long)local_10);
            return;
          }
          if (param_5 == TWO_THIRD_TRANSLUCENT_PIXELS) {
            Blit_Translucent2_Bitmap
                      ((char *)puVar5,(char *)puVar8,(long)local_8,(long)local_c,(long)pcVar2,
                       (long)local_10);
            return;
          }
          if (param_5 == ALPHA_PIXELS) {
            Blit_Alpha_Bitmap((char *)puVar5,(char *)puVar8,(long)local_8,(long)local_c,(long)pcVar2
                              ,(long)local_10);
            return;
          }
          if (param_5 == COLORIZE_PIXELS) {
            Old_Blit_Colorized_Bitmap
                      ((char *)local_8,pcVar2,(long)local_10,(uint)(byte)Foreground_Color,unaff_EBX,
                       unaff_ESI,(char)unaff_EDI);
            return;
          }
          if (param_5 != UPSIDE_DOWN_TRANSPARENT_PIXELS) {
            Blit_Solid_Bitmap((char *)puVar5,(char *)puVar8,(long)local_8,(long)local_c,(long)pcVar2
                              ,(long)local_10);
            return;
          }
          puVar8 = local_14 + iVar4 + ((param_2->Height - iVar7) + -1) * (int)local_10;
          iVar9 = -(int)local_10;
        }
        Blit_Transparent_Bitmap
                  ((char *)puVar5,(char *)puVar8,(long)local_8,(long)local_c,(long)pcVar2,iVar9);
      }
      else if (iVar9 == 2) {
        iVar9 = param_1->Width;
        local_14 = param_2->Buffer;
        local_10 = (ushort *)(param_1->Buffer + (iVar9 * local_24.y0 + local_24.x0) * 2);
        iVar6 = param_2->Width;
        puVar5 = local_14 + iVar4 + iVar6 * iVar7;
        if (param_5 == SOLID_PIXELS) {
          param_1 = local_c;
          if (0 < (int)local_c) {
            do {
              iVar4 = 0;
              if (0 < (int)local_8) {
                do {
                  local_10[iVar4] = D3D_Remap_Palette[puVar5[iVar4]];
                  iVar4 = iVar4 + 1;
                } while (iVar4 < (int)local_8);
              }
              local_10 = local_10 + iVar9;
              puVar5 = puVar5 + iVar6;
              param_1 = (_GRAPHIC_BUFFER *)((int)&param_1[-1].Allocated + 3);
            } while (param_1 != (_GRAPHIC_BUFFER *)0x0);
          }
        }
        else {
          if (param_5 != TRANSPARENT_PIXELS) {
            if ((int)param_5 < 2) {
              return;
            }
            if (4 < (int)param_5) {
              if (param_5 != UPSIDE_DOWN_TRANSPARENT_PIXELS) {
                return;
              }
              iVar6 = -iVar6;
            }
          }
          Blit_Transparent_Bitmap_8to16(local_10,local_8,iVar6,unaff_EBX,unaff_ESI,unaff_EDI);
        }
      }
      else {
        Trace("Unsupported Graphic_Copy_Bitmap format\n");
      }
    }
  }
  return;
}
