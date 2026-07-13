/*
 * Entry: 004ba5c7
 * Name: read_input_map_key
 * Namespace: Global
 * Signature: int read_input_map_key(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_input_map_key(char *param_1,char *param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  byte *pbVar4;
  FIELD_DESC *pFVar5;
  char *pcVar6;
  byte *pbVar7;
  char *pcVar8;
  bool bVar9;
  char local_188 [4];
  FILE *local_184;
  char local_180 [116];
  undefined1 local_10c [140];
  char local_80 [40];
  char local_58 [40];
  byte local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_10c;
  local_184 = fopen("input.map","r");
  inmap_lineno = 0;
  inmap_filename = "input.map";
  iVar3 = getNonBlankLine(local_180,0xff,(_iobuf *)local_184);
  do {
    if (iVar3 == 0) {
      fclose(local_184);
      return 1;
    }
    iVar3 = sscanf(local_180,"%s {",local_30);
    if (iVar3 != 1) {
      DEBUG_systemWarning("%s line %d: read error.");
      return 0;
    }
    pbVar4 = local_30;
    pbVar7 = (byte *)param_1;
    do {
      bVar1 = *pbVar4;
      bVar9 = bVar1 < *pbVar7;
      if (bVar1 != *pbVar7) {
LAB_004ba673:
        iVar3 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
        goto LAB_004ba678;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar9 = bVar1 < pbVar7[1];
      if (bVar1 != pbVar7[1]) goto LAB_004ba673;
      pbVar4 = pbVar4 + 2;
      pbVar7 = pbVar7 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_004ba678:
    if (iVar3 == 0) {
      pFVar5 = get_field_pointer((char *)local_30);
      if (pFVar5->type == 1) {
LAB_004ba72f:
        while ((iVar3 = getNonBlankLine(local_180,0xff,(_iobuf *)local_184), iVar3 != 0 &&
               (local_180[0] != '}'))) {
          iVar3 = sscanf(local_180," %1[+-] %s %s",local_188,local_80,local_58);
          if (iVar3 != 3) {
            DEBUG_systemWarning("%s line %d: read error - \"%s\"");
            return 0;
          }
          iVar3 = 9;
          bVar9 = true;
          pcVar6 = local_80;
          pcVar8 = "keyboard";
          do {
            if (iVar3 == 0) break;
            iVar3 = iVar3 + -1;
            bVar9 = *pcVar6 == *pcVar8;
            pcVar6 = pcVar6 + 1;
            pcVar8 = pcVar8 + 1;
          } while (bVar9);
          if (bVar9) {
            iVar3 = 2;
            bVar9 = true;
            pcVar6 = local_188;
            pcVar8 = "+";
            do {
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              bVar9 = *pcVar6 == *pcVar8;
              pcVar6 = pcVar6 + 1;
              pcVar8 = pcVar8 + 1;
            } while (bVar9);
            if (bVar9) {
              pcVar6 = local_58;
              iVar3 = (int)param_2 - (int)pcVar6;
              do {
                cVar2 = *pcVar6;
                pcVar6[iVar3] = cVar2;
                pcVar6 = pcVar6 + 1;
              } while (cVar2 != '\0');
            }
          }
        }
      }
      else if (pFVar5->type == 2) {
        iVar3 = 0xd;
        bVar9 = true;
        pbVar4 = local_30;
        pbVar7 = (byte *)"weapon_cycle";
        do {
          if (iVar3 == 0) break;
          iVar3 = iVar3 + -1;
          bVar9 = *pbVar4 == *pbVar7;
          pbVar4 = pbVar4 + 1;
          pbVar7 = pbVar7 + 1;
        } while (bVar9);
        if (bVar9) goto LAB_004ba72f;
      }
    }
    iVar3 = getNonBlankLine(local_180,0xff,(_iobuf *)local_184);
  } while( true );
}
