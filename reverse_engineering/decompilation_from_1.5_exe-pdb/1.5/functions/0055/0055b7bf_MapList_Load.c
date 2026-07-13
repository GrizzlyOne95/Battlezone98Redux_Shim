/*
 * Entry: 0055b7bf
 * Name: MapList::Load
 * Namespace: MapList
 * Signature: void Load(MapList * this, char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall MapList::Load(MapList *this,char *param_1)

{
  code *pcVar1;
  FILE *_File;
  char *pcVar2;
  char *pcVar3;
  char *_Str;
  char *_Str_00;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  char cVar9;
  char local_d0 [88];
  undefined1 local_78 [112];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_78;
  if ((param_1 != (char *)0x0) && (_File = fopen(param_1,"r"), _File != (FILE *)0x0)) {
    Init(this);
    pcVar2 = fgets(local_d0,200,_File);
    pcVar1 = atoi_exref;
    while (pcVar2 != (char *)0x0) {
      pcVar2 = strtok(local_d0," \t");
      pcVar3 = strtok((char *)0x0," \t");
      _Str = strtok((char *)0x0," \t");
      _Str_00 = strtok((char *)0x0," \t");
      pcVar4 = strtok((char *)0x0," \t");
      pcVar5 = strtok((char *)0x0," \t");
      pcVar6 = strtok((char *)0x0,"\r\n");
      if ((((((pcVar2 == (char *)0x0) || (pcVar3 == (char *)0x0)) || (_Str == (char *)0x0)) ||
           ((_Str_00 == (char *)0x0 || (pcVar4 == (char *)0x0)))) ||
          ((pcVar5 == (char *)0x0 ||
           ((pcVar6 == (char *)0x0 || (iVar7 = (*pcVar1)(_Str), iVar7 < 2)))))) ||
         ((iVar7 = (*pcVar1)(_Str_00), iVar7 < 2 ||
          ((iVar7 = (*pcVar1)(_Str), 0x16 < iVar7 || (iVar7 = (*pcVar1)(_Str_00), 0x16 < iVar7))))))
      break;
      iVar7 = (*pcVar1)(_Str_00);
      iVar8 = (*pcVar1)(_Str);
      pcVar1 = atoi_exref;
      if (iVar7 < iVar8) break;
      cVar9 = *pcVar5;
      iVar7 = atoi(_Str_00);
      iVar8 = atoi(_Str);
      Add(this,pcVar2,iVar8,iVar7,pcVar6,cVar9);
      pcVar2 = fgets(local_d0,200,_File);
    }
    fclose(_File);
  }
  doSyncTimer();
  SendMessageA((HWND)this->hwnd,0x186,0,0);
  return;
}
