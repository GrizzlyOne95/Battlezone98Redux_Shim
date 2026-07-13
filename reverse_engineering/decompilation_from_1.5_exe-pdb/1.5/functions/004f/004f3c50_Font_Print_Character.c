/*
 * Entry: 004f3c50
 * Name: Font_Print_Character
 * Namespace: Global
 * Signature: void Font_Print_Character(FONT * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, ushort param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl
Font_Print_Character
          (FONT *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,ushort param_5)

{
  PANE *pPVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  FONT *pFVar7;
  CHARACTER *pCVar8;
  long lVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 *puVar13;
  uchar *puVar14;
  PANE local_12c;
  int local_11c;
  FONT *local_118;
  undefined1 *local_114;
  CHARACTER *local_110;
  int local_10c;
  undefined1 local_108 [72];
  undefined1 local_c0 [184];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_c0;
  local_118 = param_1;
  if (param_2->Status != 0) {
    pCVar8 = GetCharacterAddress(param_1,param_5);
    local_12c.y0 = (param_2->Pane).y0 + param_4;
    pPVar1 = &param_2->Pane;
    local_12c.x0 = pPVar1->x0 + param_3;
    local_12c.x1 = pCVar8->Width + -1 + local_12c.x0;
    local_12c.y1 = local_12c.y0 + -1 + local_118->char_height;
    lVar9 = Clip_Pane(&local_12c,pPVar1);
    pFVar7 = local_118;
    if (-1 < lVar9) {
      local_11c = (local_12c.x1 - local_12c.x0) + 1;
      iVar3 = pCVar8->Width;
      iVar10 = (local_12c.y1 - local_12c.y0) + 1;
      iVar4 = param_2->Width;
      puVar14 = param_2->Buffer;
      iVar12 = local_12c.x0 + iVar4 * local_12c.y0;
      iVar11 = iVar3 * ((local_12c.y0 - param_4) - (param_2->Pane).y0) +
               ((local_12c.x0 - param_3) - pPVar1->x0);
      local_114 = (undefined1 *)(iVar11 + 4 + (int)pCVar8);
      if ((local_118->type & 0x100U) != 0) {
        local_110 = pCVar8 + 1;
        memset(local_108,0,0x100);
        iVar5 = pCVar8->Width;
        local_114 = (undefined1 *)0x0;
        if (iVar5 < 9) {
          puVar13 = local_108;
          if (0 < pFVar7->char_height) {
            do {
              if ((char)local_110->Width == '\0') {
                puVar13 = puVar13 + pCVar8->Width;
              }
              else {
                local_10c = 7;
                if (8 - iVar5 < 8) {
                  do {
                    if (((int)(char)local_110->Width & 1 << ((byte)local_10c & 0x1f)) != 0) {
                      *puVar13 = 1;
                    }
                    puVar13 = puVar13 + 1;
                    local_10c = local_10c + -1;
                  } while (8 - iVar5 <= local_10c);
                }
              }
              local_110 = (CHARACTER *)((int)&local_110->Width + 1);
              local_114 = (undefined1 *)((int)local_114 + 1);
            } while ((int)local_114 < pFVar7->char_height);
          }
        }
        else {
          puVar13 = local_108;
          if (0 < pFVar7->char_height) {
            do {
              if ((char)local_110->Width == '\0') {
                puVar13 = puVar13 + 8;
              }
              else {
                local_10c = 7;
                do {
                  if (((int)(char)local_110->Width & 1 << ((byte)local_10c & 0x1f)) != 0) {
                    *puVar13 = 1;
                  }
                  puVar13 = puVar13 + 1;
                  local_10c = local_10c + -1;
                } while (-1 < local_10c);
              }
              pcVar2 = (char *)((int)&local_110->Width + 1);
              if (*pcVar2 == '\0') {
                puVar13 = puVar13 + pCVar8->Width + -8;
              }
              else {
                local_10c = 7;
                if (0x10 - iVar5 < 8) {
                  do {
                    if (((int)*pcVar2 & 1 << ((byte)local_10c & 0x1f)) != 0) {
                      *puVar13 = 1;
                    }
                    puVar13 = puVar13 + 1;
                    local_10c = local_10c + -1;
                  } while (0x10 - iVar5 <= local_10c);
                }
              }
              local_110 = (CHARACTER *)((int)&local_110->Width + 2);
              local_114 = (undefined1 *)((int)local_114 + 1);
            } while ((int)local_114 < pFVar7->char_height);
          }
        }
        local_114 = local_108 + iVar11;
      }
      puVar14 = puVar14 + local_11c + iVar12;
      local_114 = local_114 + local_11c;
      iVar12 = -local_11c;
      do {
        do {
          puVar14[iVar12] =
               local_118->Back_Foreground[0][CONCAT11(local_114[iVar12],puVar14[iVar12])];
          bVar6 = iVar12 < -1;
          iVar12 = iVar12 + 1;
        } while (bVar6);
        puVar14 = puVar14 + iVar4;
        local_114 = local_114 + iVar3;
        iVar10 = iVar10 + -1;
        iVar12 = -local_11c;
      } while (iVar10 != 0);
    }
  }
  return;
}
