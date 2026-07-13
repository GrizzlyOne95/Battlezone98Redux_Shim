/*
 * Entry: 00527b23
 * Name: buildcookie
 * Namespace: Global
 * Signature: ZFS_COOKIE * buildcookie(char * param_1, _iobuf * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ZFS_COOKIE * __cdecl buildcookie(char *param_1,_iobuf *param_2)

{
  size_t sVar1;
  ZFS_COOKIE *_Memory;
  int iVar2;
  ZFS_COOKIE *unaff_ESI;
  FILE *unaff_EDI;
  char *_Format;
  ZFS_FHEADER *extraout_var;
  ZFS_FHEADER *_Src;
  char local_24;
  char local_23;
  char local_22;
  char local_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  long local_10;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  fseek(unaff_EDI,0,0);
  _Src = extraout_var;
  sVar1 = fread(&local_24,0x1c,1,unaff_EDI);
  if (sVar1 == 0) {
    _Format = "Could not read header of file \"%s\"";
  }
  else {
    if ((((local_24 == 'Z') && (local_23 == 'F')) && (local_22 == 'S')) &&
       (((local_21 == 'F' && (local_20 == 1)) && ((local_1c == 0x10 && (local_18 == 100)))))) {
      _Memory = malloc(0x2c);
      if (_Memory == (ZFS_COOKIE *)0x0) {
                    /* WARNING: Subroutine does not return */
        I76FatalError((char *)0x0);
      }
      strcpy_s(_Memory->fname,0x10,_Src->filetag);
      _Memory->fp = (_iobuf *)unaff_EDI;
      _Memory->num_dtables = local_14 / 100 + 1;
      _Memory->num_rentries = local_14;
      _Memory->record_num = local_14;
      _Memory->encrypt_key = local_10;
      iVar2 = read_record_info(unaff_ESI,_Src);
      if (iVar2 == 0) {
        free(_Memory);
        return (ZFS_COOKIE *)0x0;
      }
      qsort(_Memory->entry_table,_Memory->num_rentries,0x24,rentry_compare);
      return _Memory;
    }
    _Format = "Invalid header in file \"%s\"";
  }
  sprintf(&zfserr,_Format);
  return (ZFS_COOKIE *)0x0;
}
