/*
 * Entry: 004ba38a
 * Name: write_input_map_key
 * Namespace: Global
 * Signature: int write_input_map_key(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl write_input_map_key(char *param_1,char *param_2)

{
  byte bVar1;
  FILE *_File;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  char local_188 [4];
  FILE *local_184;
  undefined1 local_180 [40];
  char local_158 [72];
  undefined1 local_110 [184];
  char local_58 [40];
  byte local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_110;
  _File = fopen("input.map","r");
  local_184 = fopen("temp.map","w");
  inmap_lineno = 0;
  inmap_filename = "input.map";
  iVar2 = getInputMapLine(local_158,0xff,(_iobuf *)_File);
  do {
    if (iVar2 == 0) {
      fclose(local_184);
      fclose(_File);
      write_temp_to_input();
      return 1;
    }
    iVar2 = sscanf(local_158,"%s {",local_30);
    if (iVar2 != 1) {
      DEBUG_systemWarning("%s line %d: read error.");
      return 0;
    }
    fprintf(local_184,"%s\n",local_158);
    pbVar3 = local_30;
    pbVar4 = (byte *)param_1;
    do {
      bVar1 = *pbVar3;
      bVar7 = bVar1 < *pbVar4;
      if (bVar1 != *pbVar4) {
LAB_004ba463:
        iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004ba468;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar7 = bVar1 < pbVar4[1];
      if (bVar1 != pbVar4[1]) goto LAB_004ba463;
      pbVar3 = pbVar3 + 2;
      pbVar4 = pbVar4 + 2;
    } while (bVar1 != 0);
    iVar2 = 0;
LAB_004ba468:
    if (iVar2 == 0) {
      while (iVar2 = getInputMapLine(local_158,0xff,(_iobuf *)_File), iVar2 != 0) {
        if (local_158[0] == '}') {
          fprintf(local_184,"%s\n",local_158);
          fprintf(local_184,"\n");
          break;
        }
        iVar2 = sscanf(local_158," %1[+-] %s %s",local_188,local_58,local_180);
        if (iVar2 != 3) {
          DEBUG_systemWarning("%s line %d: read error - \"%s\"");
          return 0;
        }
        iVar2 = 9;
        bVar7 = true;
        pcVar5 = local_58;
        pcVar6 = "keyboard";
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar7 = *pcVar5 == *pcVar6;
          pcVar5 = pcVar5 + 1;
          pcVar6 = pcVar6 + 1;
        } while (bVar7);
        if (bVar7) {
          iVar2 = 2;
          bVar7 = true;
          pcVar5 = local_188;
          pcVar6 = "+";
          do {
            if (iVar2 == 0) break;
            iVar2 = iVar2 + -1;
            bVar7 = *pcVar5 == *pcVar6;
            pcVar5 = pcVar5 + 1;
            pcVar6 = pcVar6 + 1;
          } while (bVar7);
          if (!bVar7) goto LAB_004ba4ef;
          fprintf(local_184,"\t%s %s %s\n",local_188,local_58,param_2);
        }
        else {
LAB_004ba4ef:
          fprintf(local_184,"%s\n",local_158);
        }
      }
    }
    iVar2 = getInputMapLine(local_158,0xff,(_iobuf *)_File);
  } while( true );
}
