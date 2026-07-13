/*
 * Entry: 0056ef59
 * Name: Read_Shell_Bitmap
 * Namespace: Global
 * Signature: int Read_Shell_Bitmap(char * param_1, tagRGBQUAD * param_2, tagBITMAPINFO * * param_3, void * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Read_Shell_Bitmap(char *param_1,tagRGBQUAD *param_2,tagBITMAPINFO **param_3,void **param_4)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  FILE *_File;
  size_t sVar6;
  tagBITMAPINFOHEADER *ptVar7;
  int iVar8;
  void **unaff_EDI;
  void *local_c;
  uint local_8;
  
  iVar3 = forceBitmap24;
  forceBitmap24 = 0;
  pcVar4 = strrchr(param_1,0x5c);
  pcVar5 = param_1;
  if (pcVar4 != (char *)0x0) {
    pcVar5 = pcVar4 + 1;
  }
  bVar2 = true;
  local_8 = 0;
  local_c = zixReadFile(pcVar5,(int *)&local_8);
  if (local_c == (void *)0x0) {
    bVar2 = false;
    _File = fopen(param_1,"rb");
    if (_File == (FILE *)0x0) {
      return 0;
    }
    fseek(_File,0,2);
    local_8 = ftell(_File);
    fseek(_File,0,0);
    local_c = malloc(local_8);
    if (local_c == (void *)0x0) {
      fclose(_File);
      return 0;
    }
    sVar6 = fread(local_c,local_8,1,_File);
    if (sVar6 != 1) {
      free(local_c);
      fclose(_File);
      return 0;
    }
    fclose(_File);
  }
  iVar8 = 0;
  if (local_8 < 0x36) goto LAB_0056f0bc;
  sVar1 = *(short *)((int)local_c + 0x1c);
  ptVar7 = (tagBITMAPINFOHEADER *)((int)local_c + 0x36);
  if (sVar1 == 1) {
    iVar8 = Read_Bitmap_1(ptVar7,&param_2->rgbBlue,(tagRGBQUAD *)param_3,param_4,unaff_EDI);
LAB_0056f0a8:
    if (iVar8 != 0) goto LAB_0056f0bc;
  }
  else {
    if (sVar1 == 8) {
      if (iVar3 == 0) {
        iVar8 = Read_Bitmap_8(ptVar7,&param_2->rgbBlue,(tagRGBQUAD *)param_3,param_4,unaff_EDI);
      }
      else {
        iVar8 = Read_Bitmap_8_24(ptVar7,&param_2->rgbBlue,(tagRGBQUAD *)param_3,param_4,unaff_EDI);
      }
      goto LAB_0056f0a8;
    }
    if (sVar1 == 0x18) {
      iVar8 = Read_Bitmap_24((tagBITMAPINFOHEADER *)((int)local_c + 0xe),(uchar *)ptVar7,
                             (tagRGBQUAD *)param_3,param_4,unaff_EDI);
      goto LAB_0056f0a8;
    }
  }
  DEBUG_systemError("BattleZone (Read_Shell_Bitmap) illegal bpp Error!");
LAB_0056f0bc:
  if (bVar2) {
    zixFree(local_c);
  }
  else {
    free(local_c);
  }
  return iVar8;
}
