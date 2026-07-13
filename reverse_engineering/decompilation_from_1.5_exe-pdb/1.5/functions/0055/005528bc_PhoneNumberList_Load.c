/*
 * Entry: 005528bc
 * Name: PhoneNumberList::Load
 * Namespace: PhoneNumberList
 * Signature: void Load(PhoneNumberList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PhoneNumberList::Load(PhoneNumberList *this,char *param_1)

{
  char cVar1;
  FILE *_File;
  char *pcVar2;
  char local_d0 [88];
  undefined1 local_78 [12];
  char local_6c [100];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  if ((param_1 != (char *)0x0) && (_File = fopen(param_1,"r"), _File != (FILE *)0x0)) {
    Init(this);
    pcVar2 = fgets(local_6c,100,_File);
    while ((pcVar2 != (char *)0x0 && (pcVar2 = fgets(local_d0,100,_File), pcVar2 != (char *)0x0))) {
      pcVar2 = local_6c;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      if (pcVar2[(int)(local_78 + (0xb - (int)(local_6c + 1)))] == '\n') {
        pcVar2 = local_6c;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        pcVar2[(int)(local_78 + (0xb - (int)(local_6c + 1)))] = '\0';
      }
      pcVar2 = local_d0;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      if (pcVar2[(int)(local_d0 + (-1 - (int)(local_d0 + 1)))] == '\n') {
        pcVar2 = local_d0;
        do {
          cVar1 = *pcVar2;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        pcVar2[(int)(local_d0 + (-1 - (int)(local_d0 + 1)))] = '\0';
      }
      Add(this,local_6c,local_d0);
      pcVar2 = fgets(local_6c,100,_File);
    }
    fclose(_File);
  }
  return;
}
