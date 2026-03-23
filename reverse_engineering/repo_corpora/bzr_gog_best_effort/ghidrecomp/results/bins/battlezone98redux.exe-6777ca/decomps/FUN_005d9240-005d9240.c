
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_005d9240(int param_1)

{
  allocator<char> *paVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  int extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  float10 fVar9;
  float afStack_60 [5];
  float fStack_4c;
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  float local_30;
  float local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  float local_18;
  undefined1 *local_14;
  int local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = 0;
  if (DAT_00918338 != 0) {
    fStack_4c = 8.593227e-39;
    FUN_00422170();
    fStack_4c = 8.593243e-39;
    iVar4 = size();
    fStack_4c = 8.593254e-39;
    iVar2 = iVar4 * -4;
    local_28 = local_48 + iVar2;
    local_14 = local_48 + iVar2;
    local_1c = 0.0;
    local_10 = 0;
    *(undefined1 **)(local_48 + iVar2 + -4) = local_3c;
    afStack_60[4 - iVar4] = 8.593316e-39;
    puVar5 = (undefined4 *)FID_conflict_begin();
    local_c = *puVar5;
    while( true ) {
      *(undefined1 **)(local_48 + iVar2 + -4) = local_44;
      afStack_60[4 - iVar4] = 8.593379e-39;
      uVar6 = FID_conflict_end();
      *(undefined4 *)(local_48 + iVar2 + -4) = uVar6;
      afStack_60[4 - iVar4] = 8.593391e-39;
      cVar3 = FID_conflict_operator__();
      if (cVar3 == '\0') break;
      *(undefined4 *)(local_48 + iVar2 + -4) = 0x5d92f4;
      piVar7 = (int *)FUN_00421ec0();
      if (*(int *)(*piVar7 + 0x10) == 0) {
        *(undefined4 *)(local_48 + iVar2 + -4) = 0x5d9308;
        piVar7 = (int *)FUN_00421ec0();
        iVar8 = extraout_ECX;
        if (*(int *)(*piVar7 + 0xc) != 0) {
          *(undefined4 *)(local_48 + iVar2 + -4) = 0x5d9318;
          piVar7 = (int *)FUN_00421ec0();
          iVar8 = *(int *)(*piVar7 + 0xc);
          if (iVar8 != param_1) goto LAB_005d93e6;
        }
        *(int *)(local_48 + iVar2 + -4) = iVar8;
        *(undefined4 *)(local_48 + iVar2 + -4) = 0x47afc800;
        afStack_60[4 - iVar4] = (float)param_1;
        afStack_60[3 - iVar4] = 8.593524e-39;
        puVar5 = (undefined4 *)FUN_00421ec0();
        paVar1 = (allocator<char> *)*puVar5;
        afStack_60[3 - iVar4] = 8.593534e-39;
        puVar5 = (undefined4 *)std::allocator<char>::allocator<char>(paVar1);
        afStack_60[1 - iVar4] = (float)*puVar5;
        afStack_60[2 - iVar4] = (float)puVar5[1];
        afStack_60[3 - iVar4] = (float)puVar5[2];
        afStack_60[-iVar4] = 8.593571e-39;
        fVar9 = (float10)FUN_005d8f00();
        local_30 = (float)fVar9;
        *(undefined4 *)(local_48 + iVar2 + -4) = extraout_ECX_00;
        *(undefined4 *)(local_48 + iVar2 + -4) = 0x47afc800;
        afStack_60[4 - iVar4] = 8.59361e-39;
        puVar5 = (undefined4 *)FUN_00421ec0();
        paVar1 = (allocator<char> *)*puVar5;
        afStack_60[4 - iVar4] = 8.59362e-39;
        puVar5 = (undefined4 *)std::allocator<char>::allocator<char>(paVar1);
        afStack_60[2 - iVar4] = (float)*puVar5;
        afStack_60[3 - iVar4] = (float)puVar5[1];
        afStack_60[4 - iVar4] = (float)puVar5[2];
        afStack_60[1 - iVar4] = 8.593656e-39;
        fVar9 = (float10)FUN_005d9020();
        local_2c = (float)fVar9;
        *(undefined4 *)(local_48 + iVar2 + -4) = extraout_ECX_01;
        *(float *)(local_48 + iVar2 + -4) = local_2c;
        afStack_60[4 - iVar4] = (float)extraout_ECX_01;
        afStack_60[4 - iVar4] = local_30;
        afStack_60[3 - iVar4] = 8.593702e-39;
        fVar9 = (float10)FUN_00456080();
        local_20 = (float)fVar9;
        *(float *)(local_14 + local_10 * 4) = local_20;
        local_1c = local_1c + local_20;
      }
      else {
LAB_005d93e6:
        *(undefined4 *)(local_14 + local_10 * 4) = 0;
      }
      *(undefined4 *)(local_48 + iVar2 + -4) = 0;
      afStack_60[4 - iVar4] = (float)local_34;
      afStack_60[3 - iVar4] = 8.593345e-39;
      FUN_0046b260();
      local_10 = local_10 + 1;
    }
    *(undefined4 *)(local_48 + iVar2 + -4) = 0x5d9404;
    iVar8 = rand();
    local_18 = ((float)iVar8 * local_1c) / 32767.0;
    local_10 = 0;
    *(undefined1 **)(local_48 + iVar2 + -4) = local_38;
    afStack_60[4 - iVar4] = 8.593861e-39;
    puVar5 = (undefined4 *)FID_conflict_begin();
    local_c = *puVar5;
    while( true ) {
      *(undefined1 **)(local_48 + iVar2 + -4) = local_48;
      afStack_60[4 - iVar4] = 8.593924e-39;
      uVar6 = FID_conflict_end();
      *(undefined4 *)(local_48 + iVar2 + -4) = uVar6;
      afStack_60[4 - iVar4] = 8.593936e-39;
      cVar3 = FID_conflict_operator__();
      if (cVar3 == '\0') break;
      local_18 = local_18 - *(float *)(local_14 + local_10 * 4);
      if (local_18 < 0.0) {
        *(undefined4 *)(local_48 + iVar2 + -4) = 0x5d9498;
        puVar5 = (undefined4 *)FUN_00421ec0();
        local_24 = *puVar5;
        break;
      }
      *(undefined4 *)(local_48 + iVar2 + -4) = 0;
      afStack_60[4 - iVar4] = (float)local_40;
      afStack_60[3 - iVar4] = 8.59389e-39;
      FUN_0046b260();
      local_10 = local_10 + 1;
    }
  }
  fStack_4c = 8.594042e-39;
  FUN_0083e885();
  return;
}

