/*
 * Entry: 00528c2a
 * Name: zixReadPath
 * Namespace: Global
 * Signature: int zixReadPath(_iobuf * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl zixReadPath(_iobuf *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  bool bVar6;
  uint local_410;
  _iobuf *local_40c;
  char local_408 [120];
  undefined1 local_390 [136];
  char local_308 [256];
  char local_208 [256];
  char local_108;
  char local_107 [255];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_390;
  zix_numcds = 0;
  local_40c = param_1;
  do {
    iVar2 = get_nonblank_line(&local_108,0x100,local_40c);
    if ((iVar2 == 0) || (local_108 == '-')) break;
    sscanf(&local_108,"%d %s %s",&local_410,local_308,local_408);
    pcVar4 = &local_108;
    cVar1 = local_108;
    while ((cVar1 != '\0' && (pcVar4 = pcVar4 + 1, cVar1 != '\''))) {
      cVar1 = *pcVar4;
    }
    if (local_410 < 0x10) {
      iVar2 = local_410 * 0x300;
      pcVar3 = local_308;
      iVar5 = iVar2 - (int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[iVar5 + 0xc93200] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      pcVar3 = local_408;
      iVar5 = iVar2 - (int)pcVar3;
      do {
        cVar1 = *pcVar3;
        pcVar3[(int)zix_cds + iVar5] = cVar1;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (*pcVar4 == '\0') {
        zix_cds[local_410].english_name[0] = '\0';
      }
      else {
        iVar2 = iVar2 - (int)pcVar4;
        do {
          cVar1 = *pcVar4;
          pcVar4[iVar2 + 0xc93100] = cVar1;
          pcVar4 = pcVar4 + 1;
        } while (cVar1 != '\0');
      }
    }
    zix_numcds = zix_numcds + 1;
  } while (zix_numcds < 0x10);
  do {
    zix_numpaths = param_2 + 1;
    if (((0xff < zix_numpaths) ||
        (iVar2 = get_nonblank_line(&local_108,0x100,local_40c), iVar2 == 0)) || (local_108 == '-'))
    {
      if (((zix_numpaths == 0x100) &&
          (iVar2 = get_nonblank_line(&local_108,0x100,local_40c), iVar2 != 0)) && (local_108 != '-')
         ) {
        sprintf(&zfserr,"More than %d zix paths specified",0x100);
        iVar2 = 0;
      }
      else {
        iVar2 = 1;
      }
      return iVar2;
    }
    sscanf(&local_108,"%s %s",local_208,zix_paths + zix_numpaths);
    iVar2 = 5;
    bVar6 = true;
    pcVar4 = local_208;
    pcVar3 = "dir:";
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar6 = *pcVar4 == *pcVar3;
      pcVar4 = pcVar4 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar6);
    if (bVar6) {
      zix_paths[zix_numpaths].type = med_dir;
      param_2 = zix_numpaths;
    }
    else {
      iVar2 = strncmp(local_208,"cd",2);
      param_2 = zix_numpaths;
      if (iVar2 == 0) {
        zix_paths[zix_numpaths].type = med_cd;
        iVar2 = atoi(local_208 + 2);
        zix_paths[zix_numpaths].num = iVar2;
        param_2 = zix_numpaths;
      }
    }
  } while( true );
}
