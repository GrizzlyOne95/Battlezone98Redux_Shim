
void FUN_00826df0(undefined4 *param_1,int param_2)

{
  void *pvVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  long local_e2c;
  int local_e28;
  int local_e24;
  int local_e20;
  int local_e1c;
  char acStack_e18 [32];
  uint auStack_df8 [892];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pvVar1 = malloc(param_1[5] << 2);
  param_1[9] = pvVar1;
  if (pvVar1 != (void *)0x0) {
    pvVar1 = malloc(*(int *)(param_2 + 0x10) * 0x24);
    param_1[10] = pvVar1;
    if (pvVar1 != (void *)0x0) {
      local_e2c = *(long *)(param_2 + 0x18);
      local_e20 = 0;
      local_e28 = 0;
      do {
        fseek((FILE *)*param_1,local_e2c,0);
        sVar2 = fread(&local_e1c,0xe14,1,(FILE *)*param_1);
        if (sVar2 == 0) {
          sprintf(&DAT_009467c0,"Could not read dtable %d of file \"%s\"",local_e20,param_1 + 1);
          goto LAB_00826ffa;
        }
        *(long *)(param_1[9] + local_e20 * 4) = local_e2c;
        local_e20 = local_e20 + 1;
        for (local_e24 = 0; (local_e24 < 100 && (acStack_e18[local_e24 * 0x24] != '\0'));
            local_e24 = local_e24 + 1) {
          if ((auStack_df8[local_e24 * 9] & 1) == 0) {
            pcVar4 = acStack_e18 + local_e24 * 0x24;
            puVar5 = (undefined4 *)(param_1[10] + local_e28 * 0x24);
            for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar5 = *(undefined4 *)pcVar4;
              pcVar4 = pcVar4 + 4;
              puVar5 = puVar5 + 1;
            }
            local_e28 = local_e28 + 1;
          }
        }
        local_e2c = local_e1c;
      } while (local_e1c != 0);
      param_1[6] = local_e28;
      if (local_e20 != param_1[5]) {
        sprintf(&DAT_009467c0,"Header has %ld dtables; actually %d dtables in file \"%s\"",
                param_1[5],local_e20,param_1 + 1);
      }
    }
  }
LAB_00826ffa:
  FUN_0083e885();
  return;
}

