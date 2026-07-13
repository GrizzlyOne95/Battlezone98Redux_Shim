/*
 * Entry: 00528132
 * Name: zfsReplaceRecord
 * Namespace: Global
 * Signature: int zfsReplaceRecord(ZFS_COOKIE * param_1, void * param_2, int param_3, long param_4, char * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
zfsReplaceRecord(ZFS_COOKIE *param_1,void *param_2,int param_3,long param_4,char *param_5)

{
  long _Offset;
  FILE *_File;
  long lVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  char *_Format;
  undefined1 local_e1c [20];
  long alStack_e08 [2];
  int iStack_e00;
  long alStack_dfc [893];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  fseek((FILE *)param_1->fp,0,2);
  lVar1 = ftell((FILE *)param_1->fp);
  if (param_1->encrypt_key != 0) {
    decrypt_buffer(param_2,param_3,param_1->encrypt_key);
  }
  sVar2 = fwrite(param_2,param_3,1,(FILE *)param_1->fp);
  if (sVar2 == 0) {
    _Format = "Could not write data %s to file \"%s\"";
  }
  else {
    iVar3 = zfsFindRecordNum(param_1,param_5);
    if (iVar3 == -1) {
      _Format = "Could not find old record \"%s\" in file \"%s\"";
    }
    else {
      iVar4 = iVar3 % 100;
      _Offset = param_1->dtable_pos[iVar3 / 100];
      fseek((FILE *)param_1->fp,_Offset,0);
      sVar2 = fread(local_e1c,0xe14,1,(FILE *)param_1->fp);
      if (sVar2 != 0) {
        alStack_e08[iVar4 * 9] = lVar1;
        (&iStack_e00)[iVar4 * 9] = param_3;
        _File = (FILE *)param_1->fp;
        alStack_dfc[iVar4 * 9] = param_4;
        fseek(_File,_Offset,0);
        sVar2 = fwrite(local_e1c,0xe14,1,(FILE *)param_1->fp);
        if (sVar2 == 0) {
          sprintf(&zfserr,"Could not write dtable to file \"%s\"",param_1->fname);
          return 0;
        }
        return 1;
      }
      param_5 = (char *)(param_1->num_dtables + -1);
      _Format = "Could not read dtable %d of file \"%s\"";
    }
  }
  sprintf(&zfserr,_Format,param_5,param_1->fname);
  return 0;
}
