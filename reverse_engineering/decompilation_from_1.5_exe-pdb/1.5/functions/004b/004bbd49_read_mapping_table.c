/*
 * Entry: 004bbd49
 * Name: read_mapping_table
 * Namespace: Global
 * Signature: int read_mapping_table(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_mapping_table(void)

{
  char cVar1;
  FILE *pFVar2;
  int iVar3;
  undefined1 auVar4 [4];
  char *pcVar5;
  uint uVar6;
  undefined1 auVar7 [4];
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  bool bVar11;
  int local_110;
  undefined1 local_10c [4];
  undefined4 local_108;
  undefined2 auStack_104 [58];
  undefined1 local_90 [136];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_90;
  pFVar2 = fopen("input.map","r");
  if (pFVar2 == (FILE *)0x0) {
    DEBUG_systemWarning("%s: can\'t open file.");
    iVar3 = 0;
  }
  else {
    inmap_lineno = 0;
    inmap_filename = "input.map";
    read_one_mapping_file((_iobuf *)pFVar2);
    fclose(pFVar2);
    local_110 = 0;
    if (0 < num_input_devices) {
      local_10c = (undefined1  [4])input_names;
      do {
        if (input_enable[local_110] != 0) {
          local_108 = 0x64646967;
          auStack_104[0] = 0x69;
          pcVar9 = local_10c + 3;
          do {
            pcVar5 = pcVar9 + 1;
            pcVar9 = pcVar9 + 1;
          } while (*pcVar5 != '\0');
          *(char (*) [2])pcVar9 = (char  [2])0x5c;
          auVar4 = local_10c;
          do {
            cVar1 = *(char *)auVar4;
            auVar4 = (undefined1  [4])((int)auVar4 + 1);
          } while (cVar1 != '\0');
          pcVar9 = local_10c + 3;
          do {
            pcVar5 = pcVar9 + 1;
            pcVar9 = pcVar9 + 1;
          } while (*pcVar5 != '\0');
          auVar7 = local_10c;
          for (uVar6 = (uint)((int)auVar4 - (int)local_10c) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
            *(undefined4 *)pcVar9 = *(undefined4 *)auVar7;
            auVar7 = (undefined1  [4])((int)auVar7 + 4);
            pcVar9 = pcVar9 + 4;
          }
          pcVar5 = (char *)&local_108;
          for (uVar6 = (int)auVar4 - (int)local_10c & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
            *pcVar9 = *(char *)auVar7;
            auVar7 = (undefined1  [4])((int)auVar7 + 1);
            pcVar9 = pcVar9 + 1;
          }
          do {
            cVar1 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar1 != '\0');
          iVar3 = (int)pcVar5 - ((int)&local_108 + 1);
          while (iVar3 = isdigit((int)(char)local_10c[iVar3 + 3]), iVar3 != 0) {
            pcVar9 = (char *)&local_108;
            do {
              cVar1 = *pcVar9;
              pcVar9 = pcVar9 + 1;
            } while (cVar1 != '\0');
            pcVar9[(int)(local_10c + (3 - ((int)&local_108 + 1)))] = '\0';
            pcVar9 = (char *)&local_108;
            do {
              cVar1 = *pcVar9;
              pcVar9 = pcVar9 + 1;
            } while (cVar1 != '\0');
            iVar3 = (int)pcVar9 - ((int)&local_108 + 1);
          }
          puVar10 = (undefined4 *)(local_10c + 3);
          do {
            puVar8 = puVar10;
            puVar10 = (undefined4 *)((int)puVar8 + 1);
          } while (*(char *)((int)puVar8 + 1) != '\0');
          *(undefined4 *)((int)puVar8 + 1) = 0x6474732e;
          *(undefined1 *)((int)puVar8 + 5) = 0;
          pFVar2 = fopen((char *)&local_108,"r");
          if (pFVar2 != (FILE *)0x0) {
            inmap_filename = (char *)&local_108;
            inmap_lineno = 0;
            read_one_mapping_file((_iobuf *)pFVar2);
            fclose(pFVar2);
          }
        }
        local_10c = (undefined1  [4])((int)local_10c + 0x28);
        local_110 = local_110 + 1;
      } while (local_110 < num_input_devices);
    }
    local_108 = 0x64646967;
    auStack_104[0] = 0x69;
    pcVar9 = local_10c + 3;
    do {
      pcVar5 = pcVar9 + 1;
      pcVar9 = pcVar9 + 1;
    } while (*pcVar5 != '\0');
    *(char (*) [2])pcVar9 = (char  [2])0x5c;
    iVar3 = 5;
    bVar11 = true;
    pcVar9 = &currentJoystickMap;
    pcVar5 = "NULL";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar11 = *pcVar9 == *pcVar5;
      pcVar9 = pcVar9 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar11);
    pcVar9 = &currentJoystickMap;
    if (!bVar11) {
      do {
        pcVar5 = pcVar9;
        pcVar9 = pcVar5 + 1;
      } while (*pcVar5 != '\0');
      puVar10 = (undefined4 *)(local_10c + 3);
      do {
        pcVar9 = (char *)((int)puVar10 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      } while (*pcVar9 != '\0');
      puVar8 = (undefined4 *)&currentJoystickMap;
      for (uVar6 = (uint)(pcVar5 + -0x627247) >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar10 = puVar10 + 1;
      }
      for (uVar6 = (uint)(pcVar5 + -0x627247) & 3; pcVar9 = (char *)&local_108, uVar6 != 0;
          uVar6 = uVar6 - 1) {
        *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      do {
        pcVar5 = pcVar9;
        pcVar9 = pcVar5 + 1;
      } while (*pcVar5 != '\0');
      iVar3 = isdigit((int)pcVar5[-1]);
      while (iVar3 != 0) {
        pcVar9 = (char *)&local_108;
        do {
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        pcVar9[(int)(local_10c + (3 - ((int)&local_108 + 1)))] = '\0';
        pcVar9 = (char *)&local_108;
        do {
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        iVar3 = isdigit((int)pcVar9[(int)(local_10c + (3 - ((int)&local_108 + 1)))]);
      }
      puVar10 = (undefined4 *)(local_10c + 3);
      do {
        puVar8 = puVar10;
        puVar10 = (undefined4 *)((int)puVar8 + 1);
      } while (*(char *)((int)puVar8 + 1) != '\0');
      *(undefined4 *)((int)puVar8 + 1) = 0x6474732e;
      *(undefined1 *)((int)puVar8 + 5) = 0;
      pFVar2 = fopen((char *)&local_108,"r");
      if (pFVar2 != (FILE *)0x0) {
        inmap_filename = (char *)&local_108;
        inmap_lineno = 0;
        read_one_mapping_file((_iobuf *)pFVar2);
        fclose(pFVar2);
      }
    }
    iVar3 = 1;
  }
  return iVar3;
}
