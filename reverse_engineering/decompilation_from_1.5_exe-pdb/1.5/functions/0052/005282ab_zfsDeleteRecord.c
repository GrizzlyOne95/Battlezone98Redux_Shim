/*
 * Entry: 005282ab
 * Name: zfsDeleteRecord
 * Namespace: Global
 * Signature: int zfsDeleteRecord(ZFS_COOKIE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl zfsDeleteRecord(ZFS_COOKIE *param_1,char *param_2)

{
  long _Offset;
  FILE *_File;
  int iVar1;
  size_t sVar2;
  undefined1 local_e1c [36];
  uint auStack_df8 [892];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar1 = zfsFindRecordNum(param_1,param_2);
  if (iVar1 == -1) {
    sprintf(&zfserr,"Could not find record \"%s\" in file \"%s\"",param_2,param_1->fname);
  }
  else {
    _Offset = param_1->dtable_pos[iVar1 / 100];
    fseek((FILE *)param_1->fp,_Offset,0);
    sVar2 = fread(local_e1c,0xe14,1,(FILE *)param_1->fp);
    if (sVar2 == 0) {
      sprintf(&zfserr,"Could not read dtable %d of file \"%s\"",param_1->num_dtables + -1,
              param_1->fname);
    }
    else {
      _File = (FILE *)param_1->fp;
      auStack_df8[(iVar1 % 100) * 9] = auStack_df8[(iVar1 % 100) * 9] | 1;
      fseek(_File,_Offset,0);
      sVar2 = fwrite(local_e1c,0xe14,1,(FILE *)param_1->fp);
      if (sVar2 != 0) {
        return 1;
      }
      sprintf(&zfserr,"Could not write dtable to file \"%s\"",param_1->fname);
    }
  }
  return 0;
}
