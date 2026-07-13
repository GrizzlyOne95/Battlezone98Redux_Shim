/*
 * Entry: 00529416
 * Name: locate_file
 * Namespace: Global
 * Signature: ZIX_PATH_TYPE * locate_file(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ZIX_PATH_TYPE * __cdecl locate_file(char *param_1)

{
  uint uVar1;
  char cVar2;
  void *pvVar3;
  ZIX_PATH_TYPE *pZVar4;
  char *in_ECX;
  int iVar5;
  ZIX_DIR_TYPE *pZVar6;
  ZIX_CD_TYPE *pZVar7;
  char *pcVar8;
  int local_44;
  int local_40;
  int local_3c;
  char local_38 [48];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  to_zfsname(local_38,in_ECX);
  pvVar3 = bsearch(local_38,fentry,num_fentries,0x30,fentry_compare2);
  if (pvVar3 == (void *)0x0) {
    sprintf(&zfserr,"Couldn\'t find file \"%.16s\"");
    pZVar4 = (ZIX_PATH_TYPE *)0x0;
  }
  else {
    local_3c = -1;
    local_44 = -1;
    local_40 = -1;
    iVar5 = 0;
    pZVar6 = &zix_paths[0].type;
    do {
      if (((iVar5 < 0x101) &&
          (uVar1 = *(uint *)((int)pvVar3 + ((int)(iVar5 + (iVar5 >> 0x1f & 0x1fU)) >> 5) * 4 + 0x10)
          , uVar1 != 0)) && ((uVar1 & 1 << ((byte)iVar5 & 0x1f)) != 0)) {
        if (local_3c == -1) {
          local_3c = iVar5;
        }
        if (*pZVar6 == med_cd) {
          if (local_44 == -1) {
            local_44 = iVar5;
          }
          if ((pZVar6[1] == current_cd) && (local_40 == -1)) {
            local_40 = iVar5;
          }
        }
      }
      pZVar6 = pZVar6 + 0x43;
      iVar5 = iVar5 + 1;
    } while ((int)pZVar6 < 0xca6d00);
    if (((zixCDMode == 0) || (local_44 == -1)) ||
       ((local_3c < local_44 || (local_3c = local_40, local_40 != -1)))) {
      pZVar4 = zix_paths + local_3c;
    }
    else {
      iVar5 = zix_paths[local_44].num;
      pZVar7 = zix_cds + iVar5;
      close_zfs_files();
      pcVar8 = zix_cds[iVar5].english_name;
      cVar2 = CDDriveLetter();
      iVar5 = (*zixAskForNewCD)(cVar2,pZVar7->cd_name,pcVar8);
      pZVar4 = (ZIX_PATH_TYPE *)0x0;
      if (iVar5 != 0) {
        current_cd = zix_paths[local_44].num;
        pZVar4 = zix_paths + local_44;
      }
    }
  }
  return pZVar4;
}
