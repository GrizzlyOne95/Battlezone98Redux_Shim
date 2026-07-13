/*
 * Entry: 004ba7c3
 * Name: read_text_label
 * Namespace: Global
 * Signature: int read_text_label(char * param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_text_label(char *param_1,char *param_2,char *param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  byte *pbVar7;
  char cVar8;
  int iVar9;
  bool bVar10;
  undefined1 local_464 [4];
  int local_460;
  _iobuf *local_45c;
  undefined1 local_458 [112];
  undefined1 local_3e8 [144];
  byte local_358 [256];
  char local_258 [336];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_3e8;
  local_460 = 0;
  local_45c = (_iobuf *)fopen("label.map","r");
  if (local_45c == (_iobuf *)0x0) {
    return 0;
  }
  inmap_lineno = 0;
  inmap_filename = "label.map";
LAB_004ba9b2:
  iVar9 = 0;
  iVar6 = getNonBlankLine(local_108,0xff,local_45c);
  if (iVar6 != 0) {
    iVar6 = sscanf(local_108,"%s {",local_358);
    if (iVar6 != 1) {
      DEBUG_systemWarning("label.map line %d: read error.");
      return 0;
    }
    pbVar3 = local_358;
    pbVar7 = (byte *)param_1;
    do {
      bVar1 = *pbVar3;
      bVar10 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_004ba878:
        iVar6 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
        goto LAB_004ba87d;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar10 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_004ba878;
      pbVar3 = pbVar3 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar6 = 0;
LAB_004ba87d:
    if (iVar6 == 0) {
      do {
        iVar6 = getNonBlankLine(local_108,0xff,local_45c);
        if ((iVar6 == 0) || (local_108[0] == '}')) goto LAB_004ba9aa;
        iVar6 = sscanf(local_108," %1[+-] %s {%s} ",local_464,local_258 + 0x100,local_458);
        if (iVar6 != 3) {
          DEBUG_systemWarning("label.map line %d: read error - \"%s\"");
          return 0;
        }
        pbVar3 = (byte *)(local_258 + 0x100);
        pbVar7 = (byte *)param_2;
        do {
          bVar1 = *pbVar3;
          bVar10 = bVar1 < *pbVar7;
          if (bVar1 != *pbVar7) {
LAB_004ba8e7:
            iVar6 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
            goto LAB_004ba8ec;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar3[1];
          bVar10 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_004ba8e7;
          pbVar3 = pbVar3 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar1 != 0);
        iVar6 = 0;
LAB_004ba8ec:
      } while (iVar6 != 0);
      iVar6 = 0;
      while (local_108[iVar6] != '{') {
        iVar6 = iVar6 + 1;
        if (0xff < iVar6) goto LAB_004ba98c;
      }
      cVar8 = local_108[iVar6 + 1];
      iVar6 = iVar6 + 1;
      iVar4 = IsJapanese();
      if (iVar4 != 0) goto LAB_004ba938;
      for (; ((cVar8 != '}' && (iVar9 < 0x100)) && (iVar6 < 0x100)); iVar6 = iVar6 + 1) {
        local_258[iVar9] = cVar8;
        cVar8 = local_108[iVar6 + 1];
        iVar9 = iVar9 + 1;
      }
      goto LAB_004ba978;
    }
    goto LAB_004ba9aa;
  }
  goto LAB_004ba9ca;
  while( true ) {
    local_258[iVar9] = cVar8;
    cVar8 = local_108[iVar6 + 1];
    iVar9 = iVar9 + 1;
    iVar6 = iVar6 + 1;
    if (0xff < iVar9) break;
LAB_004ba938:
    if ((0xff < iVar6) ||
       ((cVar8 == '}' &&
        (((cVar2 = local_108[iVar6 + 1], cVar2 == '\0' || (cVar2 == ' ')) ||
         ((cVar2 == '\t' || ((cVar2 == '\r' || (cVar2 == '\n')))))))))) break;
  }
LAB_004ba978:
  local_258[iVar9] = '\0';
  local_460 = 1;
LAB_004ba98c:
  if (local_460 != 0) {
    pcVar5 = local_258;
    iVar6 = (int)param_3 - (int)pcVar5;
    do {
      cVar8 = *pcVar5;
      pcVar5[iVar6] = cVar8;
      pcVar5 = pcVar5 + 1;
    } while (cVar8 != '\0');
LAB_004ba9aa:
    if (local_460 != 0) {
LAB_004ba9ca:
      fclose((FILE *)local_45c);
      return local_460;
    }
  }
  goto LAB_004ba9b2;
}
