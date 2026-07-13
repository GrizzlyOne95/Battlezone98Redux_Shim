/*
 * Entry: 00526517
 * Name: Process_WRLD_Chunk
 * Namespace: Global
 * Signature: long Process_WRLD_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_WRLD_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  char cVar1;
  uchar uVar2;
  RGB *pRVar3;
  char *pcVar4;
  void *pvVar5;
  uchar *puVar6;
  int iVar7;
  RGB *pRVar8;
  undefined4 *puVar9;
  
  InitMusic(param_1[1].ckID.longID);
  Init_Light_Model(*(long *)((int)&param_1[0x11].ckSize + 2));
  pRVar3 = UseItem((char *)((int)&param_1[4].ckSize + 2));
  if (pRVar3 == (RGB *)0x0) {
    DEBUG_systemWarning("Error loading palette %s");
  }
  pcVar4 = UseItem((char *)&param_1[6].ckID.structID.char4);
  if (pcVar4 == (char *)0x0) {
    DEBUG_systemWarning("Error loading luminance table %s");
  }
  if (pRVar3 != (RGB *)0x0) {
    pRVar8 = pRVar3;
    puVar9 = (undefined4 *)&Default_Palette;
    for (iVar7 = 0xc0; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar9 = *(undefined4 *)pRVar8;
      pRVar8 = (RGB *)&pRVar8[1].g;
      puVar9 = puVar9 + 1;
    }
    (*Device.VideoMode.writePaletteEntries)(&Device,0,0x100,pRVar3,pcVar4);
  }
  if (pcVar4 != (char *)0x0) {
    UnlockItem((char *)&param_1[6].ckID.structID.char4);
  }
  if (pRVar3 != (RGB *)0x0) {
    UnlockItem((char *)((int)&param_1[4].ckSize + 2));
  }
  pvVar5 = UseItem((char *)(param_1 + 8));
  if (pvVar5 == (void *)0x0) {
    DEBUG_systemWarning("Translucency table not found; disabled");
  }
  else {
    Device_Init_Chrome_Key_Table(&Device);
    memcpy(Translucency_Table,pvVar5,0x10000);
    UnlockItem((char *)(param_1 + 8));
  }
  Device_Set_Chrome_Key(&Device,0xff);
  RegisterSurfaceAttributes((SURFACE_ATTRIBUTE *)((int)&param_1[0x12].ckID + 2));
  pcVar4 = (char *)((int)&param_1[9].ckSize + 1);
  iVar7 = (int)&npTextFilename - (int)pcVar4;
  do {
    cVar1 = *pcVar4;
    pcVar4[iVar7] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  puVar6 = &param_1[0x10].ckID.structID.char2;
  iVar7 = (int)mapName - (int)puVar6;
  do {
    uVar2 = *puVar6;
    puVar6[iVar7] = uVar2;
    puVar6 = puVar6 + 1;
  } while (uVar2 != '\0');
  LoadScrounge((char *)((int)&param_1[0xc].ckSize + 3));
  CreateTerrainTextureNames((char *)&param_1[0xe].ckSize);
  IntroMovie.dosName._0_4_ = param_1[1].ckSize;
  IntroMovie.dosName._4_4_ = param_1[2].ckID;
  IntroMovie.dosName._8_4_ = param_1[2].ckSize;
  IntroMovie.dosName[0xc] = param_1[3].ckID.structID.char1;
  OutroMovie.dosName._0_4_ = *(undefined4 *)((int)&param_1[3].ckID + 1);
  OutroMovie.dosName._4_4_ = *(undefined4 *)((int)&param_1[3].ckSize + 1);
  OutroMovie.dosName._8_4_ = *(undefined4 *)((int)&param_1[4].ckID + 1);
  OutroMovie.dosName[0xc] = *(char *)((int)&param_1[4].ckSize + 1);
  FarClip = (float)*(int *)((int)&param_1[0x26].ckID + 2);
  return 1;
}
