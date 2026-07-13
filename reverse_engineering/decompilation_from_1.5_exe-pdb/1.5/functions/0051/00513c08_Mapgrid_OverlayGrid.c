/*
 * Entry: 00513c08
 * Name: Mapgrid_OverlayGrid
 * Namespace: Global
 * Signature: tagMAPGRID * Mapgrid_OverlayGrid(tagOVERLAY * param_1, int * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagMAPGRID * __cdecl Mapgrid_OverlayGrid(tagOVERLAY *param_1,int *param_2,int *param_3)

{
  int *unaff_ESI;
  int *unaff_EDI;
  int local_18 [2];
  int local_10;
  int local_c;
  int local_8;
  
  Sortdisp_GetExtent(param_1->display,&local_8,&local_c,&local_10,local_18);
  param_1 = (tagOVERLAY *)(local_8 / 0x18);
  local_c = local_c / 0x18;
  if (unaff_ESI != (int *)0x0) {
    *unaff_ESI = (local_10 + 0x17) / 0x18 - (int)param_1;
  }
  if (unaff_EDI != (int *)0x0) {
    *unaff_EDI = (local_18[0] + 0x17) / 0x18 - local_c;
  }
  if ((int)param_1 < 1) {
    param_1 = (tagOVERLAY *)0x0;
  }
  if (mapsizex + -1 <= (int)param_1) {
    param_1 = (tagOVERLAY *)(mapsizex + -1);
  }
  if (local_c < 1) {
    local_c = 0;
  }
  if (mapsizey + -1 <= local_c) {
    local_c = mapsizey + -1;
  }
  return mapgrid[(int)(local_c + (local_c >> 0x1f & 0xfU)) >> 4] +
         ((int)((int)&param_1->id + ((int)param_1 >> 0x1f & 0xfU)) >> 4);
}
