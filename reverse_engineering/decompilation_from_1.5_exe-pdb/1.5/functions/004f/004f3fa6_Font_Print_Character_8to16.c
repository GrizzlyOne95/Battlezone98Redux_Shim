/*
 * Entry: 004f3fa6
 * Name: Font_Print_Character_8to16
 * Namespace: Global
 * Signature: void Font_Print_Character_8to16(FONT * param_1, _GRAPHIC_BUFFER * param_2, long param_3, long param_4, ushort param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Font_Print_Character_8to16
          (FONT *param_1,_GRAPHIC_BUFFER *param_2,long param_3,long param_4,ushort param_5)

{
  PANE *pPVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  CHARACTER *pCVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uchar *puVar12;
  PANE local_28 [2];
  
  if (param_2->Status != 0) {
    pCVar6 = GetCharacterAddress(param_1,param_5);
    local_28[0].y0 = (param_2->Pane).y0 + param_4;
    pPVar1 = &param_2->Pane;
    local_28[0].x0 = pPVar1->x0 + param_3;
    local_28[0].x1 = pCVar6->Width + -1 + local_28[0].x0;
    local_28[0].y1 = param_1->char_height + -1 + local_28[0].y0;
    lVar7 = Clip_Pane(local_28,pPVar1);
    if (-1 < lVar7) {
      iVar8 = (local_28[0].x1 - local_28[0].x0) + 1;
      iVar3 = pCVar6->Width;
      iVar9 = (local_28[0].y1 - local_28[0].y0) + 1;
      iVar4 = param_2->Width;
      puVar12 = param_2->Buffer + iVar8 * 2 + (iVar4 * local_28[0].y0 + local_28[0].x0) * 2;
      iVar11 = (int)pCVar6 +
               iVar8 + ((((local_28[0].y0 - param_4) - (param_2->Pane).y0) * iVar3 - param_3) -
                       pPVar1->x0) + local_28[0].x0 + 4;
      uVar2 = D3D_Remap_Palette[param_1->Back_Foreground[1][0]];
      iVar10 = -iVar8;
      do {
        do {
          if (*(char *)(iVar11 + iVar10) == '\x01') {
            *(ushort *)(puVar12 + iVar10 * 2) = uVar2;
          }
          bVar5 = iVar10 < -1;
          iVar10 = iVar10 + 1;
        } while (bVar5);
        iVar11 = iVar11 + iVar3;
        puVar12 = puVar12 + iVar4 * 2;
        iVar9 = iVar9 + -1;
        iVar10 = -iVar8;
      } while (iVar9 != 0);
    }
  }
  return;
}
