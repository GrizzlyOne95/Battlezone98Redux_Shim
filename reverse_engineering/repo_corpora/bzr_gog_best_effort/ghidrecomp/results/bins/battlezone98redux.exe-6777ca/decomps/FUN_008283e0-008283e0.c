
undefined4 FUN_008283e0(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  bool bVar3;
  uint local_28;
  byte *local_24;
  byte *local_20;
  byte *local_1c;
  size_t local_18;
  FILE *local_14;
  int local_10;
  byte *local_c;
  byte local_6;
  byte local_5;
  
  local_c = (byte *)0x0;
  local_18 = 0;
  local_14 = (FILE *)0x0;
  local_c = (byte *)FUN_008279c0(&local_18);
  if (local_18 == 0) {
    DAT_009468cc = (undefined4 *)0x0;
    uVar1 = 0;
  }
  else {
    qsort(local_c,local_18,0x20,FUN_00828180);
    DAT_009468cc = calloc(1,local_18 << 5);
    if (DAT_009467bc != 0) {
      local_14 = fopen("zixindex.log","wt");
    }
    puVar2 = DAT_009468cc;
    DAT_009468c0 = 0;
    *DAT_009468cc = 0;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    strncpy((char *)(DAT_009468cc + DAT_009468c0 * 8),(char *)local_c,0x10);
    if (local_14 != (FILE *)0x0) {
      uVar1 = FUN_008296a0(*(undefined2 *)(local_c + 0x10));
      fprintf(local_14,"%16s @ %s\n",local_c,uVar1);
    }
    local_24 = local_c;
    for (local_10 = 1; local_10 < (int)local_18; local_10 = local_10 + 1) {
      local_20 = local_c + local_10 * 0x20;
      local_1c = local_24;
      do {
        local_5 = *local_1c;
        bVar3 = local_5 < *local_20;
        if (local_5 != *local_20) {
LAB_00828586:
          local_28 = -(uint)bVar3 | 1;
          goto LAB_0082858e;
        }
        if (local_5 == 0) break;
        local_6 = local_1c[1];
        bVar3 = local_6 < local_20[1];
        if (local_6 != local_20[1]) goto LAB_00828586;
        local_1c = local_1c + 2;
        local_20 = local_20 + 2;
      } while (local_6 != 0);
      local_28 = 0;
LAB_0082858e:
      if (local_28 == 0) {
        if (local_14 != (FILE *)0x0) {
          uVar1 = FUN_008296a0(*(undefined2 *)(local_c + local_10 * 0x20 + 0x10));
          fprintf(local_14,"                 ! %s\n",uVar1);
        }
      }
      else {
        DAT_009468c0 = DAT_009468c0 + 1;
        puVar2 = DAT_009468cc + DAT_009468c0 * 8;
        *puVar2 = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        puVar2[3] = 0;
        strncpy((char *)(DAT_009468cc + DAT_009468c0 * 8),(char *)(local_c + local_10 * 0x20),0x10);
        if (local_14 != (FILE *)0x0) {
          uVar1 = FUN_008296a0(*(undefined2 *)(local_c + local_10 * 0x20 + 0x10));
          fprintf(local_14,"%16s @ %s\n",local_c + local_10 * 0x20,uVar1);
        }
        local_24 = local_c + local_10 * 0x20;
      }
      FUN_008278b0(DAT_009468cc + DAT_009468c0 * 8 + 4,
                   *(undefined2 *)(local_c + local_10 * 0x20 + 0x10));
    }
    if (local_14 != (FILE *)0x0) {
      fclose(local_14);
    }
    DAT_009468c0 = DAT_009468c0 + 1;
    DAT_009468cc = realloc(DAT_009468cc,DAT_009468c0 * 0x20);
    free(local_c);
    uVar1 = 1;
  }
  return uVar1;
}

