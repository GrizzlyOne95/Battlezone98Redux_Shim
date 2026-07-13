/*
 * Entry: 00529580
 * Name: resolve_path
 * Namespace: Global
 * Signature: char * resolve_path(ZIX_PATH_TYPE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl resolve_path(ZIX_PATH_TYPE *param_1,char *param_2)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  char *unaff_ESI;
  char *_Format;
  
  if (in_EAX == (char *)0x0) {
    return (char *)0x0;
  }
  if (*(int *)(in_EAX + 0x100) == 0) {
    if (zixCDMode == 0) {
      iVar2 = *(int *)(in_EAX + 0x104) * 0x300 + 0xc93200;
      _Format = "%s\\%s";
    }
    else {
      cVar1 = CDDriveLetter();
      iVar2 = (int)cVar1;
      _Format = "%c:\\%s";
    }
    sprintf(unaff_ESI,_Format,iVar2);
  }
  else {
    iVar2 = (int)unaff_ESI - (int)in_EAX;
    do {
      cVar1 = *in_EAX;
      in_EAX[iVar2] = cVar1;
      in_EAX = in_EAX + 1;
    } while (cVar1 != '\0');
  }
  return unaff_ESI;
}
