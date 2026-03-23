
void __thiscall FUN_005b9540(int param_1,float param_2)

{
  float *pfVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  undefined1 local_5c [44];
  float local_30;
  float local_2c;
  float local_28;
  undefined4 *local_24;
  int *local_20;
  float local_1c;
  float local_18;
  float local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = param_1;
  if ((-1 < *(int *)(param_1 + 0x238)) && ((iVar3 = FUN_0062a540(), iVar3 != 0 || (*local_20 != 1)))
     ) {
    FUN_0062a5d0(*(undefined4 *)(local_8 + 0x238));
    *(undefined4 *)(local_8 + 0x238) = 0xffffffff;
    fVar5 = (float10)FUN_0062e590();
    *(float *)(*(int *)(local_8 + 0xf0) + 0x14) = (float)fVar5;
    FUN_004db100();
  }
  *(float *)(local_8 + 0x23c) = *(float *)(local_8 + 0x23c) + param_2;
  pfVar1 = (float *)(*(int *)(local_8 + 0xf8) + 0x164);
  if (*pfVar1 <= *(float *)(local_8 + 0x23c) && *(float *)(local_8 + 0x23c) != *pfVar1) {
    *(float *)(local_8 + 0x23c) =
         *(float *)(local_8 + 0x23c) - *(float *)(*(int *)(local_8 + 0xf8) + 0x164);
    local_14 = *(float *)(*(int *)(local_8 + 0xf8) + 0x160);
    FUN_005b28e0((double)*(float *)(local_8 + 0x108),(double)*(float *)(local_8 + 0x110),
                 (double)local_14,local_5c);
    local_10 = 0;
    local_1c = local_14 * local_14;
LAB_005b96b2:
    do {
      cVar2 = FUN_00462710(&local_24);
      if (cVar2 == '\0') goto LAB_005b97bc;
      local_c = FUN_004da060(*local_24);
      if (local_c != 0) {
        uVar4 = (**(code **)(*(int *)(local_c + 0x18) + 4))();
        cVar2 = FUN_004db600(uVar4);
        if (cVar2 != '\0') {
          uVar4 = FUN_004625b0();
          cVar2 = FUN_004db600(uVar4);
          if (cVar2 != '\0') goto LAB_005b96b2;
        }
        fVar5 = (float10)FUN_0046fbd0();
        local_2c = (float)fVar5;
        local_28 = local_2c;
        fVar5 = (float10)FUN_004624f0();
        local_30 = (float)fVar5;
        if (local_2c < local_30) {
          (**(code **)(*(int *)(local_c + 0x18) + 0xc))
                    (*(undefined4 *)(local_8 + 0x108),*(undefined4 *)(local_8 + 0x10c),
                     *(undefined4 *)(local_8 + 0x110));
          fVar5 = (float10)FUN_004620b0();
          local_18 = (float)fVar5;
          if (local_18 < local_1c) {
            local_10 = local_c;
            local_1c = local_18;
          }
        }
      }
    } while( true );
  }
LAB_005b9816:
  FUN_0047fcb0(param_2);
  return;
LAB_005b97bc:
  if (local_10 != 0) {
    (**(code **)(*(int *)(local_10 + 0x18) + 0x28))
              (*(undefined4 *)(*(int *)(local_8 + 0xf8) + 0x168));
    uVar4 = (**(code **)(*(int *)(local_10 + 0x18) + 0x30))();
    FUN_004376c0(*(int *)(local_8 + 0xf8) + 0x16c,uVar4);
  }
  goto LAB_005b9816;
}

