/*
 * Entry: 005292b0
 * Name: zixAddToIndex
 * Namespace: Global
 * Signature: int zixAddToIndex(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl zixAddToIndex(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  ZIX_FENTRY_TYPE *pZVar4;
  ZIX_FENTRY_TYPE *pZVar5;
  int unaff_EDI;
  ZIX_PATH_TYPE *_Str1;
  int local_3c;
  char local_38 [48];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  PurgeItem(param_1);
  local_3c = 0;
  if (0 < zix_numpaths) {
    _Str1 = zix_paths;
    do {
      iVar2 = _stricmp(_Str1->name,param_2);
      if (iVar2 == 0) break;
      local_3c = local_3c + 1;
      _Str1 = _Str1 + 1;
    } while (local_3c < zix_numpaths);
    if (0xff < local_3c) {
      sprintf(&zfserr,"More than %d zix paths specified",0x100);
      return 0;
    }
  }
  if (local_3c == zix_numpaths) {
    zix_paths[zix_numpaths].type = med_dir;
    iVar2 = zix_numpaths * 0x10c - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[(int)zix_paths + iVar2] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
    zix_numpaths = zix_numpaths + 1;
  }
  to_zfsname(local_38,param_1);
  pvVar3 = bsearch(local_38,fentry,num_fentries,0x30,fentry_compare2);
  if (pvVar3 == (void *)0x0) {
    pZVar4 = realloc(fentry,(num_fentries + 1) * 0x30);
    if (pZVar4 == (ZIX_FENTRY_TYPE *)0x0) {
                    /* WARNING: Subroutine does not return */
      I76FatalError((char *)0x0);
    }
    pZVar5 = pZVar4 + num_fentries;
    num_fentries = num_fentries + 1;
    fentry = pZVar4;
    pZVar4 = pZVar5;
    to_zfsname(pZVar5->name,param_1);
    paths_setbit(pZVar5->paths,(int)pZVar4);
    qsort(fentry,num_fentries,0x30,fentry_compare2);
  }
  else {
    paths_setbit((ulong *)((int)pvVar3 + 0x10),unaff_EDI);
  }
  return 1;
}
