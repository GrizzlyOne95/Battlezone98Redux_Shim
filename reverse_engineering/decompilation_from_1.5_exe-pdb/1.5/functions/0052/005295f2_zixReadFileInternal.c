/*
 * Entry: 005295f2
 * Name: zixReadFileInternal
 * Namespace: Global
 * Signature: void * zixReadFileInternal(char * param_1, int * param_2, void * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void * __cdecl zixReadFileInternal(char *param_1,int *param_2,void *param_3,int param_4)

{
  ZIX_PATH_TYPE *pZVar1;
  char *pcVar2;
  ZFS_COOKIE *pZVar3;
  int iVar4;
  void *pvVar5;
  FILE *_File;
  size_t sVar6;
  void *in_ECX;
  size_t *unaff_EBX;
  char *unaff_ESI;
  ZIX_PATH_TYPE *unaff_EDI;
  void *local_250;
  char local_244 [116];
  undefined1 local_1d0 [184];
  char local_118 [256];
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1d0;
  to_zfsname(local_18,param_1);
  pZVar1 = locate_file(unaff_EDI->name);
  pcVar2 = resolve_path(unaff_EDI,unaff_ESI);
  if (pcVar2 != (char *)0x0) {
    pcVar2 = strstr(local_118,".zfs");
    if (pcVar2 != (char *)0x0) {
      if (pZVar1->cookie == (ZFS_COOKIE *)0x0) {
        pZVar3 = zfsOpen(local_118,0);
        pZVar1->cookie = pZVar3;
        if (pZVar3 == (ZFS_COOKIE *)0x0) {
          return (void *)0x0;
        }
      }
      if (in_ECX == (void *)0x0) {
        pvVar5 = zfsReadRecord(pZVar1->cookie,local_18,(int *)unaff_EBX);
        return pvVar5;
      }
      iVar4 = zfsReadRecordToBuffer(pZVar1->cookie,local_18,(int *)unaff_EBX,in_ECX,(int)param_2);
      return (void *)(-(uint)(iVar4 != 0) & (uint)in_ECX);
    }
    sprintf(local_244,"%s\\%s",local_118,local_18);
    _File = fopen(local_244,"rb");
    if (_File != (FILE *)0x0) {
      setvbuf(_File,(char *)0x0,4,0);
      fseek(_File,0,2);
      sVar6 = ftell(_File);
      *unaff_EBX = sVar6;
      if (in_ECX == (void *)0x0) {
        local_250 = malloc(sVar6);
        if (local_250 == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
          I76FatalError((char *)0x0);
        }
      }
      else {
        local_250 = in_ECX;
        if ((int)param_2 < (int)sVar6) {
          fclose(_File);
          return (void *)0x0;
        }
      }
      fseek(_File,0,0);
      sVar6 = fread(local_250,*unaff_EBX,1,_File);
      pvVar5 = local_250;
      if ((sVar6 == 0) &&
         (sprintf(&zfserr,"Could not read file \"%s\"",local_244), pvVar5 = (void *)0x0,
         in_ECX == (void *)0x0)) {
        free(local_250);
      }
      fclose(_File);
      return pvVar5;
    }
    sprintf(&zfserr,"Couldn\'t open file \"%s\"",local_244);
  }
  return (void *)0x0;
}
