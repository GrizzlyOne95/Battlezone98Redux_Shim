
void FUN_0061fb20(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  uint local_14c;
  uint local_148;
  char *local_144;
  undefined4 *local_140;
  int local_134;
  char local_130 [255];
  undefined4 uStack_31;
  undefined1 local_2a [34];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
LAB_0061fb34:
  do {
    iVar1 = FUN_0061e470(local_130,0xff,param_1);
    if (iVar1 == 0) goto LAB_0061ff98;
    iVar1 = sscanf(local_130,"%s {",(int)&uStack_31 + 1);
    if (iVar1 != 1) {
      FUN_007d6830("%s line %d: read error.",DAT_0091a454,DAT_0091fef8);
      goto LAB_0061fb34;
    }
    puVar2 = (undefined4 *)FUN_0061e420((int)&uStack_31 + 1);
    iVar1 = DAT_0091843c;
    if (puVar2 == (undefined4 *)0x0) {
      FUN_007d6830("%s line %d: unknown field \"%s\".",DAT_0091a454,DAT_0091fef8,(int)&uStack_31 + 1
                  );
      do {
        iVar1 = FUN_0061e470(local_130,0xff,param_1);
        if (iVar1 == 0) break;
      } while (local_130[0] != '}');
    }
    else if (puVar2[2] == 0) {
      iVar1 = FUN_0061ee60(param_1,puVar2);
      if (iVar1 == 0) {
        do {
          iVar1 = FUN_0061e470(local_130,0xff,param_1);
          if (iVar1 == 0) break;
        } while (local_130[0] != '}');
      }
    }
    else if (puVar2[2] == 1) {
      iVar3 = FUN_0061ec80(param_1,&DAT_0091a464 + DAT_0091843c * 0x74,
                           &DAT_0091a46c + DAT_0091843c * 0x74);
      if (iVar3 == 0) {
        do {
          iVar1 = FUN_0061e470(local_130,0xff,param_1);
          if (iVar1 == 0) break;
        } while (local_130[0] != '}');
      }
      else {
        DAT_0091843c = DAT_0091843c + 1;
        if (200 < DAT_0091843c) {
          FUN_007d6830("%s line %d: too many discrete controls.",DAT_0091a454,DAT_0091fef8);
          goto LAB_0061ff98;
        }
        *(undefined4 *)(&DAT_0091a45c + iVar1 * 0x74) = puVar2[1];
        *(undefined4 *)(&DAT_0091a458 + iVar1 * 0x74) = *puVar2;
        (&DAT_0091a460)[iVar1 * 0x74] = 0;
        iVar3 = strncmp((char *)*puVar2,"menu_",5);
        local_14c = (uint)(iVar3 == 0);
        *(uint *)(&DAT_0091a468 + iVar1 * 0x74) = local_14c;
        local_144 = strstr((char *)((int)&uStack_31 + 1),"_plus");
        if (local_144 == (char *)0x0) {
          local_144 = strstr((char *)((int)&uStack_31 + 1),"_minus");
        }
        if (local_144 != (char *)0x0) {
          *local_144 = '\0';
          local_134 = FUN_0061e420((int)&uStack_31 + 1);
          if (local_134 == 0) {
            puVar2 = &uStack_31;
            do {
              local_140 = puVar2;
              puVar2 = (undefined4 *)((int)local_140 + 1);
            } while (*(char *)((int)local_140 + 1) != '\0');
            *(undefined4 *)((int)local_140 + 1) = 0x6c65645f;
            *(undefined2 *)((int)local_140 + 5) = 0x6174;
            *(undefined1 *)((int)local_140 + 7) = 0;
            local_134 = FUN_0061e420((int)&uStack_31 + 1);
          }
          if ((local_134 != 0) && (iVar1 = FUN_0061ea90(local_134,0,0), iVar1 < 0)) {
LAB_0061ff98:
            FUN_0083e885();
            return;
          }
        }
      }
    }
    else {
      iVar3 = FUN_0061ec80(param_1,&DAT_0091a464 + DAT_0091843c * 0x74,
                           &DAT_0091a46c + DAT_0091843c * 0x74);
      if (iVar3 == 0) {
        do {
          iVar1 = FUN_0061e470(local_130,0xff,param_1);
          if (iVar1 == 0) break;
        } while (local_130[0] != '}');
      }
      else {
        DAT_0091843c = DAT_0091843c + 1;
        *(undefined4 *)(&DAT_0091a45c + iVar1 * 0x74) = puVar2[1];
        *(undefined4 *)(&DAT_0091a458 + iVar1 * 0x74) = *puVar2;
        (&DAT_0091a460)[iVar1 * 0x74] = 1;
        iVar3 = strncmp((char *)*puVar2,"menu_",5);
        local_148 = (uint)(iVar3 == 0);
        *(uint *)(&DAT_0091a468 + iVar1 * 0x74) = local_148;
      }
    }
  } while( true );
}

