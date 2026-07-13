/*
 * Entry: 00528617
 * Name: get_nonblank_line
 * Namespace: Global
 * Signature: int get_nonblank_line(char * param_1, int param_2, _iobuf * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl get_nonblank_line(char *param_1,int param_2,_iobuf *param_3)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  char local_108 [112];
  undefined1 local_98 [144];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_98;
  bVar2 = false;
  bVar1 = true;
  do {
    do {
      pcVar5 = fgets(local_108,param_2,(FILE *)param_3);
      if (pcVar5 == (char *)0x0) {
        return 0;
      }
      pcVar5 = local_108;
      pcVar6 = param_1;
    } while (local_108[0] == '\0');
    do {
      cVar3 = *pcVar5;
      if (cVar3 == '\'') {
        bVar1 = !bVar1;
      }
      if ((cVar3 == '\n') || (cVar3 == '#')) {
        *pcVar5 = '\0';
        break;
      }
      if (bVar2) {
        if (bVar1) {
          iVar4 = tolower((int)cVar3);
          cVar3 = (char)iVar4;
        }
LAB_005286c3:
        *pcVar6 = cVar3;
        pcVar6 = pcVar6 + 1;
      }
      else {
        iVar4 = isspace((int)cVar3);
        if (iVar4 == 0) {
          if (bVar1) {
            iVar4 = tolower((int)*pcVar5);
            cVar3 = (char)iVar4;
          }
          else {
            cVar3 = *pcVar5;
          }
          bVar2 = true;
          goto LAB_005286c3;
        }
      }
      pcVar5 = pcVar5 + 1;
    } while (*pcVar5 != '\0');
    if (bVar2) {
      *pcVar6 = '\0';
      return 1;
    }
  } while( true );
}
