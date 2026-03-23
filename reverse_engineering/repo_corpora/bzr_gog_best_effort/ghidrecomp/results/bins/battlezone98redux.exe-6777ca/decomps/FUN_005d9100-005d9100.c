
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_005d9100(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int aiStack_38 [3];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  int local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = 0;
  if (DAT_00918338 != 0) {
    aiStack_38[2] = 0x5d912f;
    cVar1 = FUN_0041fc90();
    if (cVar1 == '\0') {
      aiStack_38[2] = 0x5d9145;
      iVar2 = size();
      aiStack_38[2] = 0x5d914d;
      iVar6 = iVar2 * -4;
      local_1c = local_2c + iVar6;
      local_14 = local_2c + iVar6;
      local_10 = 0;
      *(undefined4 *)(local_2c + iVar6 + -4) = 0x5d9165;
      FUN_00422170();
      *(undefined1 **)(local_2c + iVar6 + -4) = local_24;
      aiStack_38[1 - iVar2] = 0x5d9174;
      puVar3 = (undefined4 *)FID_conflict_begin();
      local_c = *puVar3;
      while( true ) {
        *(undefined1 **)(local_2c + iVar6 + -4) = local_2c;
        aiStack_38[1 - iVar2] = 0x5d9198;
        uVar4 = FID_conflict_end();
        *(undefined4 *)(local_2c + iVar6 + -4) = uVar4;
        aiStack_38[1 - iVar2] = 0x5d91a1;
        cVar1 = FID_conflict_operator__();
        if (cVar1 == '\0') break;
        *(undefined4 *)(local_2c + iVar6 + -4) = 0x5d91b0;
        piVar5 = (int *)FUN_00421ec0();
        if (*(int *)(*piVar5 + 0x10) == 0) {
          *(undefined4 *)(local_2c + iVar6 + -4) = 0x5d91c0;
          piVar5 = (int *)FUN_00421ec0();
          if (*(int *)(*piVar5 + 0xc) != 0) {
            *(undefined4 *)(local_2c + iVar6 + -4) = 0x5d91d0;
            piVar5 = (int *)FUN_00421ec0();
            if (*(int *)(*piVar5 + 0xc) != param_1) goto LAB_005d917b;
          }
          *(undefined4 *)(local_2c + iVar6 + -4) = 0x5d91e2;
          puVar3 = (undefined4 *)FUN_00421ec0();
          *(undefined4 *)(local_14 + local_10 * 4) = *puVar3;
          local_10 = local_10 + 1;
        }
LAB_005d917b:
        *(undefined4 *)(local_2c + iVar6 + -4) = 0;
        aiStack_38[1 - iVar2] = (int)local_28;
        aiStack_38[-iVar2] = 0x5d9189;
        FUN_0046b260();
      }
      if (0 < local_10) {
        *(undefined4 *)(local_2c + iVar6 + -4) = 0x5d9204;
        iVar6 = rand();
        local_20 = (iVar6 * local_10) / 0x7fff;
        local_18 = *(undefined4 *)(local_14 + local_20 * 4);
      }
    }
  }
  aiStack_38[2] = 0x5d922f;
  FUN_0083e885();
  return;
}

