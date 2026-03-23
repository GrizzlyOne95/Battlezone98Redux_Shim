
/* WARNING: Removing unreachable block (ram,0x0050b4fc) */

void __thiscall FUN_0050b460(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  char *pcVar4;
  char *local_24;
  char *local_20;
  char local_19;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20 = *(char **)(param_1 + 4);
  pcVar4 = local_20 + 1;
  do {
    cVar1 = *local_20;
    local_20 = local_20 + 1;
  } while (cVar1 != '\0');
  iVar2 = _strnicmp(param_2,*(char **)(param_1 + 4),(int)local_20 - (int)pcVar4);
  if (iVar2 != 0) {
    local_18[0] = '\0';
    local_18[1] = '\0';
    local_18[2] = '\0';
    local_18[3] = '\0';
    local_18[4] = '\0';
    local_18[5] = '\0';
    local_18[6] = '\0';
    local_18[7] = '\0';
    local_18[8] = '\0';
    local_18[9] = '\0';
    local_18[10] = '\0';
    local_18[0xb] = '\0';
    local_18[0xc] = '\0';
    local_18[0xd] = '\0';
    local_18[0xe] = '\0';
    local_18[0xf] = '\0';
    strncpy(local_18,&DAT_00915540,8);
                    /* WARNING: Ignoring partial resolution of indirect */
    local_18[8] = 0;
    puVar3 = (undefined1 *)FUN_00434140(local_18,0x2e);
    if (puVar3 != (undefined1 *)0x0) {
      *puVar3 = 0;
    }
    pcVar4 = &local_19;
    do {
      local_24 = pcVar4;
      local_19 = local_24[1];
      pcVar4 = local_24 + 1;
    } while (local_19 != '\0');
    builtin_strncpy(local_24 + 1,".lua",5);
    FUN_00481f10(local_18);
  }
  FUN_0083e885();
  return;
}

