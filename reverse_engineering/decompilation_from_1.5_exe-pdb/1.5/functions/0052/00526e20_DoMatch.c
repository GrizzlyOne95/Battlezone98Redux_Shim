/*
 * Entry: 00526e20
 * Name: DoMatch
 * Namespace: Global
 * Signature: int DoMatch(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DoMatch(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  bool bVar6;
  
  do {
    cVar2 = *param_2;
    if (cVar2 == '\0') {
      return (uint)(*param_1 == '\0');
    }
    cVar1 = *param_1;
    if (cVar1 == '\0') {
      if ((*param_2 == '*') && (param_2[1] == '\0')) {
        return 1;
      }
      return -1;
    }
    if (cVar2 == '*') {
      if (param_2[1] == '\0') {
        return 1;
      }
      do {
        iVar3 = DoMatch(param_1,param_2 + 1);
        if (iVar3 != 0) {
          return 1;
        }
        param_1 = param_1 + 1;
      } while (*param_1 != '\0');
      return -1;
    }
    if (cVar2 != '?') {
      if (cVar2 == '[') {
        bVar6 = param_2[1] == '!';
        if (bVar6) {
          param_2 = param_2 + 1;
        }
        bVar5 = false;
        iVar3 = 0x100;
        pcVar4 = param_2;
        while( true ) {
          param_2 = pcVar4 + 1;
          cVar2 = *param_2;
          if ((cVar2 == '\0') || (cVar2 == ']')) break;
          if (cVar2 == '-') {
            param_2 = pcVar4 + 2;
            cVar2 = *param_2;
            if ((cVar1 <= cVar2) && (iVar3 <= cVar1)) {
LAB_00526ea0:
              bVar5 = true;
            }
          }
          else if (cVar1 == cVar2) goto LAB_00526ea0;
          iVar3 = (int)cVar2;
          pcVar4 = param_2;
        }
        if (bVar5 == bVar6) {
          return 0;
        }
      }
      else {
        if (cVar2 == '\\') {
          param_2 = param_2 + 1;
        }
        if (cVar1 != *param_2) {
          return 0;
        }
      }
    }
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while( true );
}
