
void FUN_0061ec80(undefined4 param_1,int *param_2,int param_3)

{
  int iVar1;
  uint local_158;
  char local_14c [4];
  int local_148;
  char local_144 [256];
  undefined1 local_44 [40];
  undefined1 local_1c [20];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_148 = 0;
  *param_2 = 0;
  while( true ) {
    while( true ) {
      iVar1 = FUN_0061e470(local_144,0xff,param_1);
      if ((iVar1 == 0) || (local_144[0] == '}')) goto LAB_0061ee24;
      iVar1 = sscanf(local_144," %1[+-] %s %s",local_14c,local_44,local_1c);
      if (iVar1 == 3) break;
      FUN_007d6830("%s line %d: invalid chord entry",DAT_0091a454,DAT_0091fef8);
    }
    if (7 < *param_2) break;
    if (local_148 != -1) {
      iVar1 = FUN_0061e1c0(local_44);
      local_148 = FUN_0061e330(iVar1,local_1c);
      if (local_148 != -1) {
        local_158 = (uint)(local_14c[0] == '-');
        *(uint *)(param_3 + 8 + *param_2 * 0xc) = local_158;
        *(undefined **)(param_3 + *param_2 * 0xc) =
             &DAT_02a14320 + (local_148 >> 5) * 4 + iVar1 * 0x50;
        *(int *)(param_3 + 4 + *param_2 * 0xc) = 1 << ((byte)local_148 & 0x1f);
        *param_2 = *param_2 + 1;
      }
    }
  }
  FUN_007d6830("%s line %d: chord too big",DAT_0091a454,DAT_0091fef8);
LAB_0061ee24:
  FUN_0083e885();
  return;
}

