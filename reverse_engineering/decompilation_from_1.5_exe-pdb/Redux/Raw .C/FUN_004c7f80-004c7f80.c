
void __thiscall FUN_004c7f80(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined2 *puVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint local_20;
  int local_1c;
  int local_14;
  int local_c;
  int local_8;
  
  if (((-1 < *(int *)(param_1 + 0x1c460)) && (-1 < *(int *)(param_1 + 0x1c464))) &&
     (DAT_009454ac != 0)) {
    FUN_004c6ee0(&local_c,&local_8,param_2);
    iVar4 = local_c - *(int *)(param_1 + 0xec) / 2;
    iVar1 = iVar4 + *(int *)(param_1 + 0xec);
    iVar6 = local_8 - *(int *)(param_1 + 0xf0) / 2;
    iVar5 = iVar6 + *(int *)(param_1 + 0xf0);
    uVar7 = 1;
    puVar2 = (undefined2 *)FUN_00492d60(iVar4,iVar6,1);
    FUN_004c10a0(iVar4,iVar6,*puVar2,uVar7);
    local_14 = 0;
    for (local_8 = iVar6; local_8 <= iVar5; local_8 = local_8 + 1) {
      local_1c = 0;
      for (local_c = iVar4; local_c <= iVar1; local_c = local_c + 1) {
        puVar3 = (ushort *)FUN_00492d60(local_c,local_8);
        local_20 = (*puVar3 & 0xfff) +
                   (int)*(short *)(param_1 + 0x1c468 + local_14 * 0x80 + local_1c * 2);
        if ((int)local_20 < 0) {
          local_20 = 0;
        }
        if (0xfff < (int)local_20) {
          local_20 = 0xfff;
        }
        if ((*puVar3 & 0xfff) != local_20) {
          FUN_004c10d0(local_c,local_8,*puVar3);
          *puVar3 = (ushort)local_20;
        }
        local_1c = local_1c + 1;
      }
      local_14 = local_14 + 1;
    }
    local_14 = 0;
    for (local_8 = iVar6; local_8 <= iVar5; local_8 = local_8 + 1) {
      local_1c = 0;
      for (local_c = iVar4; local_c <= iVar1; local_c = local_c + 1) {
        puVar3 = (ushort *)FUN_004c0fe0(local_c,local_8);
        if ((*puVar3 & 0xfff) != (int)*(short *)(param_1 + 0x1e468 + local_14 * 0x80 + local_1c * 2)
           ) {
          FUN_004c73b0(local_c,local_8,*puVar3,0,1);
          *puVar3 = *(ushort *)(param_1 + 0x1e468 + local_14 * 0x80 + local_1c * 2);
        }
        local_1c = local_1c + 1;
      }
      local_14 = local_14 + 1;
    }
    FUN_00780b80(iVar4 + -2,iVar6 + -2,iVar1 + 2,iVar5 + 2);
  }
  return;
}

