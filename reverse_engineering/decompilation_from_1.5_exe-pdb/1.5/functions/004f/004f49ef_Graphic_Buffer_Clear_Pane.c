/*
 * Entry: 004f49ef
 * Name: Graphic_Buffer_Clear_Pane
 * Namespace: Global
 * Signature: void Graphic_Buffer_Clear_Pane(_GRAPHIC_BUFFER * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Graphic_Buffer_Clear_Pane(_GRAPHIC_BUFFER *param_1,long param_2)

{
  ushort uVar1;
  uint uVar2;
  uchar *puVar3;
  int iVar4;
  undefined1 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  int iVar11;
  ushort *puVar12;
  uint *puVar13;
  
  if (param_1->Status != 0) {
    if (param_1->Bit_Depth == WORD_FORMAT) {
      iVar8 = (param_1->Pane).y0;
      uVar2 = param_1->Width;
      puVar3 = param_1->Buffer;
      iVar4 = (param_1->Pane).x0;
      uVar1 = D3D_Remap_Palette[param_2 & 0xff];
      param_1 = (_GRAPHIC_BUFFER *)(((param_1->Pane).y1 - iVar8) + 1);
      if (0 < (int)param_1) {
        do {
          if (0 < (int)uVar2) {
            puVar12 = (ushort *)(puVar3 + (iVar8 * uVar2 + iVar4) * 2);
            for (uVar6 = uVar2 >> 1; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(uint *)puVar12 = CONCAT22(uVar1,uVar1);
              puVar12 = puVar12 + 2;
            }
            for (uVar6 = (uint)((uVar2 & 1) != 0); uVar6 != 0; uVar6 = uVar6 - 1) {
              *puVar12 = uVar1;
              puVar12 = puVar12 + 1;
            }
          }
          param_1 = (_GRAPHIC_BUFFER *)((int)&param_1[-1].Allocated + 3);
        } while (param_1 != (_GRAPHIC_BUFFER *)0x0);
      }
    }
    else {
      iVar8 = (param_1->Pane).y0;
      iVar4 = param_1->Width;
      iVar7 = (param_1->Pane).x0;
      puVar9 = (uint *)(param_1->Buffer + iVar7 + iVar8 * iVar4);
      uVar2 = param_2 | param_2 << 8;
      iVar7 = ((param_1->Pane).x1 - iVar7) + 1;
      iVar11 = ((param_1->Pane).y1 - iVar8) + 1;
      uVar5 = (undefined1)param_2;
      iVar8 = iVar7;
      puVar13 = puVar9;
      if (iVar7 < 8) {
        do {
          for (; iVar8 != 0; iVar8 = iVar8 + -1) {
            *(undefined1 *)puVar9 = uVar5;
            puVar9 = (uint *)((int)puVar9 + 1);
          }
          puVar9 = (uint *)((int)puVar13 + iVar4);
          iVar11 = iVar11 + -1;
          iVar8 = iVar7;
          puVar13 = puVar9;
        } while (iVar11 != 0);
      }
      else {
        do {
          uVar6 = -(int)puVar9 & 3;
          uVar10 = iVar7 - uVar6;
          puVar13 = puVar9;
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar13 = uVar5;
            puVar13 = (uint *)((int)puVar13 + 1);
          }
          uVar6 = uVar10 & 3;
          for (uVar10 = uVar10 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
            *puVar13 = uVar2 | uVar2 << 0x10;
            puVar13 = puVar13 + 1;
          }
          for (; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined1 *)puVar13 = uVar5;
            puVar13 = (uint *)((int)puVar13 + 1);
          }
          puVar9 = (uint *)((int)puVar9 + iVar4);
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      }
    }
  }
  return;
}
