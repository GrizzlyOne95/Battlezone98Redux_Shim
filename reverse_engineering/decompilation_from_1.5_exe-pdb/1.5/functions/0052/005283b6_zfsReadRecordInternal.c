/*
 * Entry: 005283b6
 * Name: zfsReadRecordInternal
 * Namespace: Global
 * Signature: void * zfsReadRecordInternal(ZFS_COOKIE * param_1, char * param_2, int * param_3, void * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl
zfsReadRecordInternal(ZFS_COOKIE *param_1,char *param_2,int *param_3,void *param_4,int param_5)

{
  size_t _Size;
  ZFS_RENTRY *pZVar1;
  size_t sVar2;
  int iVar3;
  bool bVar4;
  void *local_10;
  void *local_c;
  void *local_8;
  
  local_8 = (void *)0x0;
  pZVar1 = zfsFindRecordInfo(param_1,param_2);
  bVar4 = (pZVar1->flags & 6) != 0;
  _Size = pZVar1->size;
  if ((bVar4) || (param_4 == (void *)0x0)) {
    local_c = malloc(_Size);
    local_8 = local_c;
    if (local_c == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
      I76FatalError((char *)0x0);
    }
  }
  else {
    local_c = param_4;
    if (param_5 < (int)_Size) {
      return (void *)0x0;
    }
  }
  fseek((FILE *)param_1->fp,pZVar1->offset,0);
  sVar2 = fread(local_c,_Size,1,(FILE *)param_1->fp);
  if (sVar2 == 0) {
    sprintf(&zfserr,"Could not read record %s from file \"%s\"",param_2,param_1->fname);
    if (local_8 == (void *)0x0) {
      return (void *)0x0;
    }
LAB_00528459:
    free(local_8);
  }
  else {
    if (!bVar4) {
      *param_3 = _Size;
      goto LAB_005284d3;
    }
    sVar2 = pZVar1->flags >> 8;
    if (param_4 == (void *)0x0) {
      local_10 = malloc(sVar2);
      if (local_10 == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
        I76FatalError((char *)0x0);
      }
    }
    else {
      if (param_5 < (int)sVar2) goto LAB_00528459;
      local_10 = param_4;
    }
    iVar3 = expandData(local_c,_Size,pZVar1->flags,local_10,sVar2);
    free(local_8);
    if (iVar3 != 0) {
      local_c = local_10;
      *param_3 = sVar2;
LAB_005284d3:
      if (param_1->encrypt_key != 0) {
        decrypt_buffer(local_c,*param_3,param_1->encrypt_key);
        return local_c;
      }
      return local_c;
    }
  }
  return (void *)0x0;
}
