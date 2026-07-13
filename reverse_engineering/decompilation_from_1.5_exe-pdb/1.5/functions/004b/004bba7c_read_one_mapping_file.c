/*
 * Entry: 004bba7c
 * Name: read_one_mapping_file
 * Namespace: Global
 * Signature: int read_one_mapping_file(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl read_one_mapping_file(_iobuf *param_1)

{
  undefined4 *puVar1;
  FIELD_DESC *pFVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  char local_130 [124];
  undefined1 local_b4 [131];
  undefined4 uStack_31;
  undefined1 auStack_2a [34];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_b4;
LAB_004bbcfd:
  do {
    while( true ) {
      while( true ) {
        iVar5 = getNonBlankLine(local_130,0xff,param_1);
        if (iVar5 == 0) {
          return 1;
        }
        iVar5 = sscanf(local_130,"%s {",(int)&uStack_31 + 1);
        if (iVar5 == 1) break;
        DEBUG_systemWarning("%s line %d: read error.");
      }
      pFVar2 = get_field_pointer((char *)((int)&uStack_31 + 1));
      iVar5 = num_discrete_controls;
      if (pFVar2 != (FIELD_DESC *)0x0) break;
      DEBUG_systemWarning("%s line %d: unknown field \"%s\".");
      iVar5 = getNonBlankLine(local_130,0xff,param_1);
      while ((iVar5 != 0 && (local_130[0] != '}'))) {
        iVar5 = getNonBlankLine(local_130,0xff,param_1);
      }
    }
    if (pFVar2->type == 0) {
      iVar5 = read_analog(param_1,pFVar2);
      if (iVar5 == 0) {
        do {
          iVar5 = getNonBlankLine(local_130,0xff,param_1);
          if (iVar5 == 0) break;
        } while (local_130[0] != '}');
      }
      goto LAB_004bbcfd;
    }
    if (pFVar2->type != 1) {
      iVar3 = read_chord(param_1,&discrete_map[num_discrete_controls].chord_size,
                         discrete_map[num_discrete_controls].chord);
      if (iVar3 == 0) {
        do {
          iVar5 = getNonBlankLine(local_130,0xff,param_1);
          if (iVar5 == 0) break;
        } while (local_130[0] != '}');
      }
      else {
        num_discrete_controls = num_discrete_controls + 1;
        discrete_map[iVar5].to = pFVar2->field;
        discrete_map[iVar5].debounce = '\x01';
        iVar3 = strncmp(pFVar2->name,"menu_",5);
        discrete_map[iVar5].in_menu = (uint)(iVar3 == 0);
      }
      goto LAB_004bbcfd;
    }
    iVar3 = read_chord(param_1,&discrete_map[num_discrete_controls].chord_size,
                       discrete_map[num_discrete_controls].chord);
    if (iVar3 != 0) {
      num_discrete_controls = num_discrete_controls + 1;
      if (200 < num_discrete_controls) {
        DEBUG_systemWarning("%s line %d: too many discrete controls.");
        return 0;
      }
      discrete_map[iVar5].to = pFVar2->field;
      discrete_map[iVar5].debounce = '\0';
      iVar3 = strncmp(pFVar2->name,"menu_",5);
      discrete_map[iVar5].in_menu = (uint)(iVar3 == 0);
      pcVar4 = strstr((char *)((int)&uStack_31 + 1),"_plus");
      if ((pcVar4 != (char *)0x0) ||
         (pcVar4 = strstr((char *)((int)&uStack_31 + 1),"_minus"), pcVar4 != (char *)0x0)) {
        *pcVar4 = '\0';
        pFVar2 = get_field_pointer((char *)((int)&uStack_31 + 1));
        if (pFVar2 == (FIELD_DESC *)0x0) {
          puVar1 = &uStack_31;
          do {
            puVar6 = puVar1;
            puVar1 = (undefined4 *)((int)puVar6 + 1);
          } while (*(char *)((int)puVar6 + 1) != '\0');
          *(undefined4 *)((int)puVar6 + 1) = 0x6c65645f;
          *(undefined2 *)((int)puVar6 + 5) = 0x6174;
          *(undefined1 *)((int)puVar6 + 7) = 0;
          pFVar2 = get_field_pointer((char *)((int)&uStack_31 + 1));
          if (pFVar2 == (FIELD_DESC *)0x0) goto LAB_004bbcfd;
        }
        iVar5 = add_analog_channel(pFVar2,(char *)0x0,0);
        if (iVar5 < 0) {
          return 0;
        }
      }
      goto LAB_004bbcfd;
    }
    do {
      iVar5 = getNonBlankLine(local_130,0xff,param_1);
      if (iVar5 == 0) break;
    } while (local_130[0] != '}');
  } while( true );
}
