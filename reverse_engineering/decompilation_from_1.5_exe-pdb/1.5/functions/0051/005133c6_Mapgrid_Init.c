/*
 * Entry: 005133c6
 * Name: Mapgrid_Init
 * Namespace: Global
 * Signature: void Mapgrid_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_Init(void)

{
  tagMAPGRID **pptVar1;
  tagMAPGRID *ptVar2;
  int iVar3;
  
  mapgridxsize = (int)(mapsizex + 0xf + (mapsizex + 0xf >> 0x1f & 0xfU)) >> 4;
  mapgridysize = (int)(mapsizey + 0xf + (mapsizey + 0xf >> 0x1f & 0xfU)) >> 4;
  mapgrid = calloc(1,mapgridysize << 2);
  Debug_Assert((int)mapgrid,0x38,".\\Schedule\\Mapgrid.c","mapgrid");
  ptVar2 = calloc(1,mapgridysize * mapgridxsize * 0x10c);
  *mapgrid = ptVar2;
  iVar3 = 1;
  if (1 < mapgridysize) {
    do {
      pptVar1 = mapgrid + iVar3;
      iVar3 = iVar3 + 1;
      *pptVar1 = pptVar1[-1] + mapgridxsize;
    } while (iVar3 < mapgridysize);
  }
  memset(*mapgrid,0,mapgridysize * mapgridxsize * 0x10c);
  maxbuildingxsize = 0;
  maxbuildingysize = 0;
  maxoverlayxsize = 0;
  maxoverlayysize = 0;
  curfoggridcell = 0;
  return;
}
