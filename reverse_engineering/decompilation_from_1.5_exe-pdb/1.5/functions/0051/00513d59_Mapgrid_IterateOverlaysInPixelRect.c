/*
 * Entry: 00513d59
 * Name: Mapgrid_IterateOverlaysInPixelRect
 * Namespace: Global
 * Signature: void Mapgrid_IterateOverlaysInPixelRect(_func___cdecl_void_tagOVERLAY_ptr_void_ptr * param_1, void * param_2, int param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Mapgrid_IterateOverlaysInPixelRect
          (_func___cdecl_void_tagOVERLAY_ptr_void_ptr *param_1,void *param_2,int param_3,int param_4
          ,int param_5,int param_6)

{
  tagOVERLAY *ptVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  tagOVERLAY *local_10;
  int local_c;
  int local_8;
  
  iVar2 = param_4 / 0x18 - maxoverlayysize;
  local_8 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
  iVar2 = param_3 / 0x18 - maxoverlayxsize;
  iVar4 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
  iVar2 = (param_6 + 0x17) / 0x18 + 0xf;
  local_c = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
  iVar2 = (param_5 + 0x17) / 0x18 + 0xf;
  iVar2 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
  if (local_8 < 1) {
    local_8 = 0;
  }
  if (mapgridysize <= local_c) {
    local_c = mapgridysize;
  }
  if (iVar4 < 1) {
    iVar4 = 0;
  }
  if (mapgridxsize <= iVar2) {
    iVar2 = mapgridxsize;
  }
  if (local_8 < local_c) {
    do {
      if (iVar4 < iVar2) {
        iVar3 = iVar4 * 0x10c;
        local_14 = iVar2 - iVar4;
        do {
          ptVar1 = *(tagOVERLAY **)((int)mapgrid[local_8]->firstbuilding + iVar3 + 0x40);
          while (local_10 = ptVar1, local_10 != (tagOVERLAY *)0x0) {
            ptVar1 = local_10->gridnext;
            Sortdisp_GetExtent(local_10->display,&local_18,&local_1c,&local_20,&local_24);
            if ((((local_18 < param_5) && (local_1c < param_6)) && (param_3 < local_20)) &&
               (param_4 < local_24)) {
              (*param_1)(local_10,param_2);
            }
          }
          iVar3 = iVar3 + 0x10c;
          local_14 = local_14 + -1;
        } while (local_14 != 0);
      }
      local_8 = local_8 + 1;
    } while (local_8 < local_c);
  }
  return;
}
