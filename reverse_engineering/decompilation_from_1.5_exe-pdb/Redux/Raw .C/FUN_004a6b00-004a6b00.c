
void FUN_004a6b00(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined8 uVar5;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined8 local_34;
  undefined8 local_2c;
  int local_24;
  undefined1 local_20 [4];
  int local_1c;
  int *local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_004a6d50();
  local_24 = FUN_00461430();
  FID_conflict_begin(local_20);
  while( true ) {
    uVar2 = FID_conflict_end(local_38);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    FUN_0046b260(local_3c,0);
    local_18 = (int *)FUN_00421ec0();
    local_18 = (int *)*local_18;
    iVar3 = (**(code **)(local_18[6] + 4))();
    if (iVar3 == local_24) {
      iVar3 = FUN_0045bba0();
      if (-1 < iVar3) {
        cVar1 = (**(code **)(*local_18 + 0x38))();
        if (cVar1 != '\0') {
          puVar4 = (undefined4 *)(**(code **)(local_18[6] + 0xc))();
          local_14 = *puVar4;
          local_10 = puVar4[1];
          local_c = puVar4[2];
          uVar5 = FUN_00497780(&local_14,DAT_00917594,0);
          local_34 = uVar5;
          local_2c = uVar5;
          iVar3 = FUN_0049f100(uVar5,&stack0x00000004);
          if (iVar3 != 0) {
            FUN_0049f3c0(1);
            uVar2 = FUN_00462380();
            *(undefined4 *)(local_1c + 0x1c + *(int *)(local_1c + 0x188) * 4) = uVar2;
            *(int *)(local_1c + 0x188) = *(int *)(local_1c + 0x188) + 1;
          }
        }
      }
    }
  }
  *(undefined4 *)(local_1c + 0x117c) = 0xffffffff;
  *(undefined4 *)(local_1c + 0x1188) = 0;
  FUN_0083e885();
  return;
}

