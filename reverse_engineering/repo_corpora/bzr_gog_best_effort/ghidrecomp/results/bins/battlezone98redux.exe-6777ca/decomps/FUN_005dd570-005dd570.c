
void __thiscall FUN_005dd570(int param_1,float param_2)

{
  float *pfVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_50 [44];
  undefined4 *local_24;
  int *local_20;
  float local_1c;
  float local_18;
  float local_14;
  int *local_10;
  int *local_c;
  int local_8;
  
  local_8 = param_1;
  if ((-1 < *(int *)(param_1 + 0x238)) && ((iVar3 = FUN_0062a540(), iVar3 != 0 || (*local_20 != 1)))
     ) {
    FUN_0062a5d0(*(undefined4 *)(local_8 + 0x238));
    *(undefined4 *)(local_8 + 0x238) = 0xffffffff;
    fVar6 = (float10)FUN_0062e590();
    *(float *)(*(int *)(local_8 + 0xf0) + 0x14) = (float)fVar6;
    FUN_004db100();
  }
  *(float *)(local_8 + 0x23c) = *(float *)(local_8 + 0x23c) + param_2;
  pfVar1 = (float *)(*(int *)(local_8 + 0xf8) + 0x164);
  if (*pfVar1 <= *(float *)(local_8 + 0x23c) && *(float *)(local_8 + 0x23c) != *pfVar1) {
    *(float *)(local_8 + 0x23c) =
         *(float *)(local_8 + 0x23c) - *(float *)(*(int *)(local_8 + 0xf8) + 0x164);
    local_14 = *(float *)(*(int *)(local_8 + 0xf8) + 0x160);
    FUN_005b28e0((double)*(float *)(local_8 + 0x108),(double)*(float *)(local_8 + 0x110),
                 (double)local_14,local_50);
    local_10 = (int *)0x0;
    local_1c = local_14 * local_14;
LAB_005dd6e3:
    do {
      cVar2 = FUN_00462710(&local_24);
      if (cVar2 == '\0') goto LAB_005dd7d8;
      local_c = (int *)FUN_004da060(*local_24);
      if (local_c != (int *)0x0) {
        uVar4 = (**(code **)(local_c[6] + 4))();
        cVar2 = FUN_004db600(uVar4);
        if (cVar2 != '\0') {
          uVar4 = FUN_004625b0();
          cVar2 = FUN_004db600(uVar4);
          if (cVar2 != '\0') goto LAB_005dd6e3;
        }
        iVar3 = FUN_00417c80();
        iVar5 = FUN_0046d060();
        if (iVar3 < iVar5) {
          (**(code **)(local_c[6] + 0xc))
                    (*(undefined4 *)(local_8 + 0x108),*(undefined4 *)(local_8 + 0x10c),
                     *(undefined4 *)(local_8 + 0x110));
          fVar6 = (float10)FUN_004620b0();
          local_18 = (float)fVar6;
          if (local_18 < local_1c) {
            local_10 = local_c;
            local_1c = local_18;
          }
        }
      }
    } while( true );
  }
LAB_005dd827:
  FUN_0047fcb0(param_2);
  return;
LAB_005dd7d8:
  if (local_10 != (int *)0x0) {
    (**(code **)(*local_10 + 0x18))(*(undefined4 *)(*(int *)(local_8 + 0xf8) + 0x168));
    uVar4 = (**(code **)(local_10[6] + 0x30))();
    FUN_004376c0(*(int *)(local_8 + 0xf8) + 0x16c,uVar4);
  }
  goto LAB_005dd827;
}

