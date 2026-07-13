/*
 * Entry: 00527d10
 * Name: zfsAddRecordInternal
 * Namespace: Global
 * Signature: int zfsAddRecordInternal(ZFS_COOKIE * param_1, void * param_2, int param_3, long param_4, char * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
zfsAddRecordInternal
          (ZFS_COOKIE *param_1,void *param_2,int param_3,long param_4,char *param_5,int *param_6)

{
  size_t sVar1;
  int iVar2;
  void *pvVar3;
  undefined4 *in_ECX;
  int *in_EDX;
  int iVar4;
  char *pcVar5;
  int local_1c58;
  long local_1c54;
  ZFS_COOKIE *local_1c50;
  undefined1 local_1c4c [112];
  undefined1 local_1bdc [3492];
  long local_e38;
  char acStack_e34 [16];
  long lStack_e24;
  int aiStack_e20 [895];
  undefined1 local_24 [16];
  int local_14;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1bdc;
  local_1c58 = 0;
  local_1c50 = param_1;
  fseek((FILE *)*in_ECX,0,2);
  local_1c54 = ftell((FILE *)*in_ECX);
  if (in_ECX[7] != 0) {
    decrypt_buffer(local_1c50,(int)param_2,in_ECX[7]);
  }
  if ((in_EDX != (int *)0x0) && ((int)param_2 < 0x1000000)) {
    local_1c50 = compressData(local_1c50,(int)param_2,in_EDX,&local_1c58);
    if (local_1c50 == (ZFS_COOKIE *)0x0) {
      return 0;
    }
    param_2 = (void *)*in_EDX;
  }
  sVar1 = fwrite(local_1c50,(size_t)param_2,1,(FILE *)*in_ECX);
  if (local_1c58 != 0) {
    free(local_1c50);
  }
  if (sVar1 == 0) {
    pcVar5 = "Could not write data %s to file \"%s\"";
  }
  else {
    local_1c50 = *(ZFS_COOKIE **)(in_ECX[9] + -4 + in_ECX[5] * 4);
    fseek((FILE *)*in_ECX,(long)local_1c50,0);
    sVar1 = fread(&local_e38,0xe14,1,(FILE *)*in_ECX);
    if (sVar1 != 0) {
      iVar4 = (int)in_ECX[8] % 100;
      strncpy(acStack_e34 + iVar4 * 0x24,(char *)param_4,0x10);
      strlower(acStack_e34 + iVar4 * 0x24);
      (&lStack_e24)[iVar4 * 9] = local_1c54;
      iVar2 = in_ECX[8];
      aiStack_e20[iVar4 * 9 + 1] = (int)param_2;
      aiStack_e20[iVar4 * 9] = iVar2;
      iVar2 = iVar2 + 1;
      aiStack_e20[iVar4 * 9 + 2] = param_3;
      in_ECX[8] = iVar2;
      aiStack_e20[iVar4 * 9 + 3] = local_1c58;
      if (iVar2 % 100 == 0) {
        fseek((FILE *)*in_ECX,0,2);
        local_1c54 = ftell((FILE *)*in_ECX);
        local_e38 = local_1c54;
        memset(local_1c4c,0,0xe14);
        sVar1 = fwrite(local_1c4c,0xe14,1,(FILE *)*in_ECX);
        if (sVar1 == 0) {
          sprintf(&zfserr,"Error writing to file \"%s\"",in_ECX + 1);
          fclose((FILE *)*in_ECX);
          return 0;
        }
        in_ECX[5] = in_ECX[5] + 1;
        pvVar3 = realloc((void *)in_ECX[9],in_ECX[5] << 2);
        in_ECX[9] = pvVar3;
        *(long *)((int)pvVar3 + in_ECX[5] * 4 + -4) = local_1c54;
      }
      fseek((FILE *)*in_ECX,(long)local_1c50,0);
      sVar1 = fwrite(&local_e38,0xe14,1,(FILE *)*in_ECX);
      if (sVar1 == 0) {
        pcVar5 = "Could not write dtable to file \"%s\"";
      }
      else {
        fseek((FILE *)*in_ECX,0,0);
        sVar1 = fread(local_24,0x1c,1,(FILE *)*in_ECX);
        if (sVar1 == 0) {
          pcVar5 = "Could not read header of file \"%s\"";
        }
        else {
          local_14 = local_14 + 1;
          fseek((FILE *)*in_ECX,0,0);
          sVar1 = fwrite(local_24,0x1c,1,(FILE *)*in_ECX);
          if (sVar1 != 0) {
            return 1;
          }
          pcVar5 = "Could not write header of file \"%s\"";
        }
      }
      sprintf(&zfserr,pcVar5,in_ECX + 1);
      return 0;
    }
    param_4 = in_ECX[5] + -1;
    pcVar5 = "Could not read dtable %d of file \"%s\"";
  }
  sprintf(&zfserr,pcVar5,param_4,in_ECX + 1);
  return 0;
}
