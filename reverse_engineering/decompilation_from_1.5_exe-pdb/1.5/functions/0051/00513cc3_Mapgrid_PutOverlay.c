/*
 * Entry: 00513cc3
 * Name: Mapgrid_PutOverlay
 * Namespace: Global
 * Signature: void Mapgrid_PutOverlay(tagOVERLAY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_PutOverlay(tagOVERLAY *param_1)

{
  tagOVERLAY *ptVar1;
  tagMAPGRID *ptVar2;
  int in_ECX;
  int *unaff_ESI;
  int *unaff_EDI;
  
  ptVar2 = Mapgrid_OverlayGrid(param_1,unaff_EDI,unaff_ESI);
  if (maxoverlayxsize <= (int)param_1) {
    maxoverlayxsize = (int)param_1;
  }
  if (maxoverlayysize <= in_ECX) {
    maxoverlayysize = in_ECX;
  }
  ptVar1 = ptVar2->firstoverlay;
  param_1->gridprev = (tagOVERLAY *)0x0;
  param_1->gridnext = ptVar1;
  if (ptVar1 != (tagOVERLAY *)0x0) {
    ptVar1->gridprev = param_1;
  }
  ptVar2->firstoverlay = param_1;
  return;
}
