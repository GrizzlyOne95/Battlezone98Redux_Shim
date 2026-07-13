/*
 * Entry: 00513d18
 * Name: Mapgrid_RemoveOverlay
 * Namespace: Global
 * Signature: void Mapgrid_RemoveOverlay(tagOVERLAY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_RemoveOverlay(tagOVERLAY *param_1)

{
  tagMAPGRID *ptVar1;
  int *unaff_ESI;
  int *unaff_EDI;
  
  ptVar1 = Mapgrid_OverlayGrid(param_1,unaff_EDI,unaff_ESI);
  if (param_1->gridprev == (tagOVERLAY *)0x0) {
    ptVar1->firstoverlay = param_1->gridnext;
  }
  else {
    param_1->gridprev->gridnext = param_1->gridnext;
  }
  if (param_1->gridnext != (tagOVERLAY *)0x0) {
    param_1->gridnext->gridprev = param_1->gridprev;
  }
  param_1->gridnext = (tagOVERLAY *)0x0;
  param_1->gridprev = (tagOVERLAY *)0x0;
  return;
}
