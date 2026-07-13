/*
 * Entry: 00582867
 * Name: draw_cursor
 * Namespace: Global
 * Signature: void draw_cursor(INPUT_REGION * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl draw_cursor(INPUT_REGION *param_1)

{
  int iVar1;
  char cVar2;
  ushort uVar3;
  CHARACTER *pCVar4;
  uint uVar5;
  int *unaff_ESI;
  int iVar6;
  
  iVar6 = unaff_ESI[0x46] + *unaff_ESI;
  iVar1 = ((uint)(((Device.Viewport.Pane.y1 - Device.Viewport.Pane.y0) + 1) * unaff_ESI[1]) / 0x1e0
          - 1) + unaff_ESI[3];
  for (uVar5 = unaff_ESI[0x45]; uVar5 < (uint)unaff_ESI[0x44]; uVar5 = uVar5 + 1) {
    pCVar4 = GetCharacterAddress(Default_Font,(short)*(char *)((int)unaff_ESI + uVar5 + 0x10));
    iVar6 = iVar6 + pCVar4->Width;
  }
  cVar2 = *(char *)(uVar5 + 0x10 + (int)unaff_ESI);
  if (cVar2 == '\0') {
    uVar3 = 0x77;
  }
  else {
    uVar3 = (ushort)cVar2;
  }
  pCVar4 = GetCharacterAddress(Default_Font,uVar3);
  Graphic_Line(&Device.Viewport,iVar6,iVar1,pCVar4->Width + iVar6,iVar1,unaff_ESI[0x47],SOLID_PIXELS
              );
  return;
}
