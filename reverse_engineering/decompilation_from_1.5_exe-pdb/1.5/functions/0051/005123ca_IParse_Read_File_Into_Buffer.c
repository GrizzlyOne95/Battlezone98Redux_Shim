/*
 * Entry: 005123ca
 * Name: IParse_Read_File_Into_Buffer
 * Namespace: Global
 * Signature: void IParse_Read_File_Into_Buffer(_iobuf * param_1, char * * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Read_File_Into_Buffer(_iobuf *param_1,char **param_2,int *param_3)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  int iVar6;
  size_t _Size;
  char *pcVar7;
  
  bVar2 = false;
  bVar3 = false;
  bVar1 = false;
  bVar4 = false;
  iVar6 = fseek((FILE *)param_1,0,2);
  if (iVar6 != 0) {
    IParse_Report("Unable to seek to end of file while preprocessing script",2);
  }
  _Size = ftell((FILE *)param_1);
  pcVar7 = calloc(1,_Size);
  *param_2 = pcVar7;
  if (pcVar7 == (char *)0x0) {
    IParse_Report("Unable to allocate memory for buffer while preprocessing script",2);
  }
  pcVar7 = *param_2;
  iVar6 = fseek((FILE *)param_1,0,0);
  if (iVar6 != 0) {
    IParse_Report("Unable to seek to start of file",2);
  }
LAB_0051244e:
  while( true ) {
    iVar6 = getc((FILE *)param_1);
    cVar5 = (char)iVar6;
    iVar6 = IParse_Find_Char_Type(cVar5);
    if (!bVar1) break;
    bVar1 = false;
    if (cVar5 != '/') {
      if (cVar5 == '*') {
        bVar3 = true;
      }
      else {
        *pcVar7 = '/';
        pcVar7 = pcVar7 + 1;
        bVar2 = false;
        bVar3 = false;
      }
      break;
    }
    bVar2 = true;
  }
  if (bVar2) {
    if ((cVar5 != '\n') && (cVar5 != '\r')) goto LAB_0051244e;
    bVar2 = false;
  }
  else {
    if (bVar3) {
      if (bVar4) {
        if (cVar5 == '/') {
          bVar3 = false;
          goto LAB_0051244e;
        }
        bVar4 = false;
      }
      if (cVar5 == '*') {
        bVar4 = true;
      }
      goto LAB_0051244e;
    }
    if (iVar6 == 2) {
      if (cVar5 == '/') {
        bVar1 = true;
        goto LAB_0051244e;
      }
    }
    else if (iVar6 == 3) {
      *param_3 = (int)pcVar7 - (int)*param_2;
      return;
    }
  }
  *pcVar7 = cVar5;
  pcVar7 = pcVar7 + 1;
  goto LAB_0051244e;
}
