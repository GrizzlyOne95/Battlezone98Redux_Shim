/*
 * Entry: 004ebd15
 * Name: GetObjectiveText
 * Namespace: Global
 * Signature: long GetObjectiveText(char * * param_1, long param_2, long * param_3, char * * param_4, long param_5, long * param_6, long * param_7, long param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __cdecl
GetObjectiveText(char **param_1,long param_2,long *param_3,char **param_4,long param_5,long *param_6
                ,long *param_7,long param_8)

{
  char **ppcVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *in_ECX;
  int *in_EDX;
  int *unaff_EBX;
  char *_Str1;
  char *local_120;
  long local_11c;
  char **local_114;
  char **local_10c;
  char local_108 [8];
  char local_100;
  char local_ff [91];
  undefined1 local_a4 [156];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_a4;
  *unaff_EBX = 0;
  local_114 = param_4;
  bVar3 = false;
  *in_EDX = 0;
  if ((((in_ECX != (undefined4 *)0x0) && (param_4 != (char **)0x0)) && (param_1 != (char **)0x0)) &&
     (param_5 != 0)) {
    if (npTextFilename == '\0') {
      return 0;
    }
    local_120 = UseItem(&npTextFilename);
    if (local_120 == (char *)0x0) {
      DEBUG_systemWarning("Can\'t find objective text file %s. The Notepad will be unavailable.");
      return -1;
    }
    local_11c = GetItemSize(&npTextFilename);
    local_10c = param_1;
    iVar4 = sgets(&local_120,local_108,&local_11c,param_5);
    while ((iVar4 != 0 && (ppcVar1 = (char **)((int)local_10c + -1), local_10c != (char **)0x0))) {
      _Str1 = local_108;
      if (bVar3) {
LAB_004ebe3a:
        pcVar5 = _Str1;
        do {
          cVar2 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');
        pcVar5 = malloc((size_t)(pcVar5 + (1 - (int)(_Str1 + 1))));
        *in_ECX = pcVar5;
        if (pcVar5 == (char *)0x0) {
          return 0;
        }
        do {
          cVar2 = *_Str1;
          _Str1 = _Str1 + 1;
          *pcVar5 = cVar2;
          pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');
        in_ECX = in_ECX + 1;
        *in_EDX = *in_EDX + 1;
        local_10c = ppcVar1;
        if (!bVar3) {
          local_114 = local_114 + 1;
        }
      }
      else {
        iVar4 = _strnicmp(_Str1,"(hidden)",8);
        if (iVar4 == 0) {
          *local_114 = (char *)0x1;
          _Str1 = &local_100;
          cVar2 = local_100;
          while (iVar4 = isspace((int)cVar2), iVar4 != 0) {
            _Str1 = _Str1 + 1;
            cVar2 = *_Str1;
          }
          goto LAB_004ebe3a;
        }
        iVar4 = _strnicmp(local_108,"(failure)",9);
        if (iVar4 != 0) goto LAB_004ebe3a;
        local_10c = (char **)param_3;
        bVar3 = true;
        in_ECX = (undefined4 *)param_2;
        in_EDX = unaff_EBX;
        if (param_2 == 0) break;
      }
      iVar4 = sgets(&local_120,local_108,&local_11c,param_5);
    }
    UnlockItem(&npTextFilename);
  }
  return 1;
}
