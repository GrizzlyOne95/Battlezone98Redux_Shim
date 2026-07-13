/*
 * Entry: 00548577
 * Name: in
 * Namespace: Global
 * Signature: bool in(_iobuf * param_1, void * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl in(_iobuf *param_1,void *param_2,uint param_3)

{
  char cVar1;
  bool bVar2;
  uchar uVar3;
  uchar uVar4;
  int iVar5;
  char *pcVar6;
  void *in_ECX;
  char cVar7;
  uint uVar8;
  
  if (binarySave) {
    bVar2 = in_data(0,(long)param_2,in_ECX);
    return bVar2;
  }
  in_prep();
  iVar5 = sscanf(inCurrent,"%*s =");
  cVar7 = '\x01' - (iVar5 != 0);
  do {
    cVar1 = *inCurrent;
    pcVar6 = inCurrent + 1;
    if (pcVar6 == inLast) break;
    inCurrent = pcVar6;
  } while (cVar1 != '=');
  in_char();
  if (cVar7 != '\0') {
    uVar8 = 0;
    if (param_3 != 0) {
      do {
        uVar3 = in_char();
        uVar4 = in_char();
        uVar3 = convert(uVar3,uVar4);
        *(uchar *)(uVar8 + (int)param_2) = uVar3;
        uVar8 = uVar8 + 1;
      } while (uVar8 < param_3);
    }
    pcVar6 = nextLine;
    *nextLine = '\r';
    inCurrent = pcVar6 + 2;
  }
  return (bool)cVar7;
}
