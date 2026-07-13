/*
 * Entry: 004f9d75
 * Name: Load_Pcx_Bitmap
 * Namespace: Global
 * Signature: TEXTURE * Load_Pcx_Bitmap(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

TEXTURE * __cdecl Load_Pcx_Bitmap(char *param_1)

{
  int iVar1;
  int iVar2;
  TEXTURE *pTVar3;
  int iVar4;
  size_t _Size;
  _GRAPHIC_BUFFER local_8d4;
  int local_8a0;
  int local_89c;
  int local_898;
  FILE *local_894;
  TEXTURE *local_890;
  int local_88c;
  char local_888;
  char local_887;
  char local_885;
  short local_884;
  short local_882;
  short local_880;
  short local_87e;
  undefined1 local_854 [14];
  short local_846;
  undefined1 local_808 [2048];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_854;
  local_894 = fopen(param_1,"rb");
  pTVar3 = (TEXTURE *)0x0;
  if (local_894 != (FILE *)0x0) {
    fread(&local_888,0x80,1,local_894);
    if (((local_888 == '\n') || (local_887 == '\x05')) || (local_885 == '\b')) {
      _Size = ((int)local_880 - (int)local_884) + 1;
      iVar4 = ((int)local_87e - (int)local_882) + 1;
      pTVar3 = malloc(iVar4 * _Size + 8);
      pTVar3->width = (short)_Size;
      pTVar3->height = iVar4;
      if (0 < iVar4) {
        local_890 = pTVar3 + 1;
        local_898 = iVar4;
        do {
          local_8a0 = (int)local_846;
          local_88c = 0;
          if (0 < local_8a0) {
            do {
              iVar1 = fgetc(local_894);
              if (iVar1 < 0xc1) {
                iVar2 = local_88c + 1;
                local_808[local_88c] = (char)iVar1;
              }
              else {
                iVar1 = iVar1 + -0xc0;
                local_89c = iVar1;
                iVar2 = fgetc(local_894);
                memset(local_808 + local_88c,iVar2,iVar1);
                iVar2 = local_88c + local_89c;
              }
              local_88c = iVar2;
            } while (iVar2 < local_8a0);
          }
          memmove(local_890,local_808,_Size);
          local_890 = (TEXTURE *)((int)local_890 + _Size);
          local_898 = local_898 + -1;
        } while (local_898 != 0);
      }
      Graphic_Buffer_Init_Ex(&local_8d4,_Size,iVar4,(char *)(pTVar3 + 1),BYTES_FORMAT);
    }
    else {
      pTVar3 = (TEXTURE *)0x0;
    }
    fclose(local_894);
  }
  return pTVar3;
}
