
void FUN_006a1590(int param_1)

{
  float fVar1;
  char cVar2;
  uint uVar3;
  int *piVar4;
  void *pvVar5;
  float *pfVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  float10 fVar11;
  float10 fVar12;
  int local_40;
  int local_38;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fb0c;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  piVar4 = (int *)FUN_004200d0();
  local_38 = *piVar4;
  if (local_38 == 0) {
    pvVar5 = operator_new(0x38);
    local_8 = 0;
    if (pvVar5 == (void *)0x0) {
      local_40 = 0;
    }
    else {
      local_40 = FUN_006a1820();
    }
    local_8 = 0xffffffff;
    local_38 = local_40;
    piVar4 = (int *)FUN_004200d0();
    *piVar4 = local_40;
  }
  pfVar6 = (float *)(**(code **)(*(int *)(param_1 + 0x18) + 0xc))(uVar3);
  fVar1 = pfVar6[2];
  uVar7 = FUN_006a08c0((double)*pfVar6);
  *(undefined4 *)(local_38 + 0x10) = uVar7;
  uVar7 = FUN_006a0920((double)fVar1);
  *(undefined4 *)(local_38 + 0x14) = uVar7;
  uVar7 = FUN_004625b0();
  *(undefined4 *)(local_38 + 8) = uVar7;
  (*(code *)**(undefined4 **)(param_1 + 0x18))();
  cVar2 = FUN_006a07e0();
  if (cVar2 == '\0') {
    *(undefined4 *)(local_38 + 0x20) = 0;
  }
  else {
    cVar2 = FUN_004738b0();
    if (cVar2 == '\0') {
      *(undefined4 *)(local_38 + 0x20) = 0xb;
    }
    else {
      cVar2 = FUN_004723d0();
      if (cVar2 == '\0') {
        *(undefined4 *)(local_38 + 0x20) = 1;
      }
      else {
        *(undefined4 *)(local_38 + 0x20) = 3;
      }
    }
  }
  fVar11 = (float10)FUN_00822d80();
  fVar12 = (float10)FUN_0046d040();
  if ((float)fVar11 - (float)fVar12 < 2.0) {
    FUN_00462530();
    iVar8 = FUN_00462630();
    if ((iVar8 != 0) && (iVar9 = FUN_0045bdf0(), iVar9 != 0)) {
      pfVar6 = (float *)(**(code **)(*(int *)(iVar8 + 0x18) + 0xc))();
      fVar1 = pfVar6[2];
      uVar7 = FUN_006a08c0((double)*pfVar6);
      uVar10 = FUN_006a0920((double)fVar1);
      FUN_00696f00(*(undefined4 *)(local_38 + 4),*(undefined4 *)(local_38 + 0x10),
                   *(undefined4 *)(local_38 + 0x14),1,uVar7,uVar10,iVar8);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

