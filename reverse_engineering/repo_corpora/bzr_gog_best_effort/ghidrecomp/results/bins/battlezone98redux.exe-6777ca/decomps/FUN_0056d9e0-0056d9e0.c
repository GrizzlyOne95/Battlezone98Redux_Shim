
void __fastcall FUN_0056d9e0(int param_1)

{
  float *pfVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined1 local_88;
  undefined1 local_87;
  undefined1 local_86;
  undefined1 local_84;
  undefined1 local_83;
  undefined1 local_82;
  uint local_80;
  uint local_7c;
  int local_78;
  undefined4 local_74 [10];
  double local_4c;
  double local_44;
  double local_3c;
  float local_34;
  undefined4 local_30;
  float local_2c;
  char local_28 [20];
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined4 local_11;
  undefined2 local_d;
  undefined1 local_b;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_78 = param_1;
  if (DAT_00917f4c == '\0') {
    if (*(int *)(param_1 + 0x40c) != 0) {
      *(undefined4 *)(param_1 + 0x40c) = 0;
      *(undefined4 *)(param_1 + 0x3f8) = 1;
      iVar3 = FUN_00417c70();
      if (iVar3 != 0) {
        sprintf(local_28,"team%da");
        iVar3 = FUN_00460fc0();
        local_34 = **(float **)(iVar3 + 8);
        local_30 = 0;
        local_2c = (*(float **)(iVar3 + 8))[1];
        puVar4 = (undefined4 *)FUN_0045c4d0();
        puVar6 = local_74;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar6 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar6 = puVar6 + 1;
        }
        local_4c = (double)local_34;
        local_3c = (double)local_2c;
        fVar7 = (float10)FUN_007855e0((double)local_34,(double)local_2c);
        local_44 = (double)fVar7;
        FUN_0056d6a0();
      }
    }
    if (*(int *)(local_78 + 0x3f8) != 0) {
      *(undefined4 *)(local_78 + 0x3f8) = 0;
      FUN_004f6ae0();
    }
    cVar2 = FUN_00571c30();
    if (cVar2 != '\0') {
      if (*(int *)(local_78 + 0x18) == 0) {
        *(undefined4 *)(local_78 + 0x3fc) = 1;
        *(undefined4 *)(local_78 + 0x400) = 1;
        *(undefined4 *)(local_78 + 0x404) = 1;
        *(undefined4 *)(local_78 + 0x408) = 1;
        *(undefined4 *)(local_78 + 0x18) = 1;
        for (local_80 = 0; local_80 < 0x1e; local_80 = local_80 + 1) {
          if (*(char *)(local_78 + local_80 * 0x20 + 0x30) == 'a') {
            uVar5 = FUN_005c8250("apammo",0,local_78 + 0x30 + local_80 * 0x20,0,0);
            *(undefined4 *)(local_78 + 0x28 + local_80 * 0x20) = uVar5;
          }
          else {
            uVar5 = FUN_005c8250("aprepa",0,local_78 + 0x30 + local_80 * 0x20,0,0);
            *(undefined4 *)(local_78 + 0x28 + local_80 * 0x20) = uVar5;
          }
          *(undefined1 *)(local_78 + 0x44 + local_80 * 0x20) = 0;
        }
        uVar5 = FUN_005c8250("abstor",1,"goal1a",0,0);
        *(undefined4 *)(local_78 + 1000) = uVar5;
        uVar5 = FUN_005c8250("abstor",1,"goal1b",0,0);
        *(undefined4 *)(local_78 + 0x3ec) = uVar5;
        uVar5 = FUN_005c8250("abstor",2,"goal2a",0,0);
        *(undefined4 *)(local_78 + 0x3f0) = uVar5;
        uVar5 = FUN_005c8250("abstor",2,"goal2b",0,0);
        *(undefined4 *)(local_78 + 0x3f4) = uVar5;
      }
      else {
        if ((*(int *)(local_78 + 0x3fc) != 0) && (cVar2 = FUN_005c84d0(), cVar2 == '\0')) {
          FUN_0081cb40("multi_message","team_1_flag_1");
          FUN_00572da0();
          FUN_0056fcb0();
          *(undefined4 *)(local_78 + 0x3fc) = 0;
        }
        if ((*(int *)(local_78 + 0x400) != 0) && (cVar2 = FUN_005c84d0(), cVar2 == '\0')) {
          FUN_0081cb40("multi_message","team_1_flag_2");
          FUN_00572da0();
          FUN_0056fcb0();
          *(undefined4 *)(local_78 + 0x400) = 0;
        }
        if ((*(int *)(local_78 + 0x404) != 0) && (cVar2 = FUN_005c84d0(), cVar2 == '\0')) {
          FUN_0081cb40("multi_message","team_2_flag_1");
          FUN_00572da0();
          FUN_0056fcb0();
          *(undefined4 *)(local_78 + 0x404) = 0;
        }
        if ((*(int *)(local_78 + 0x408) != 0) && (cVar2 = FUN_005c84d0(), cVar2 == '\0')) {
          FUN_0081cb40("multi_message","team_2_flag_2");
          FUN_00572da0();
          FUN_0056fcb0();
          *(undefined4 *)(local_78 + 0x408) = 0;
        }
        iVar3 = FUN_004f6b10();
        if (iVar3 < 1) {
          local_14 = 0x23;
          local_13 = 0x52;
          local_12 = 0;
          local_11 = 0;
          local_d = 0;
          local_b = 0;
          FUN_00575890(&local_14,3,1,1);
          *(undefined4 *)(local_78 + 0x40c) = 1;
          FUN_00572da0();
          FUN_0056fcb0();
          FUN_0056d8b0();
        }
        cVar2 = FUN_005c84d0();
        if ((cVar2 == '\0') && (cVar2 = FUN_005c84d0(), cVar2 == '\0')) {
          local_84 = 0x23;
          local_83 = 0x52;
          local_82 = 1;
          FUN_00575890(&local_84,3,1,1);
          *(undefined4 *)(local_78 + 0x40c) = 1;
          FUN_00572da0();
          FUN_0056fcb0();
          FUN_0056d8b0();
        }
        cVar2 = FUN_005c84d0();
        if ((cVar2 == '\0') && (cVar2 = FUN_005c84d0(), cVar2 == '\0')) {
          local_88 = 0x23;
          local_87 = 0x52;
          local_86 = 2;
          FUN_00575890(&local_88,3,1,1);
          *(undefined4 *)(local_78 + 0x40c) = 1;
          FUN_00572da0();
          FUN_0056fcb0();
          FUN_0056d8b0();
        }
        for (local_7c = 0; local_7c < 0x1e; local_7c = local_7c + 1) {
          iVar3 = FUN_00462630();
          if ((iVar3 == 0) && (*(char *)(local_78 + 0x44 + local_7c * 0x20) == '\0')) {
            *(undefined1 *)(local_78 + 0x44 + local_7c * 0x20) = 1;
            fVar7 = (float10)FUN_00822da0();
            *(float *)(local_78 + 0x2c + local_7c * 0x20) = (float)fVar7 + 10.0;
          }
          if ((*(char *)(local_78 + 0x44 + local_7c * 0x20) != '\0') &&
             (fVar7 = (float10)FUN_00822da0(), pfVar1 = (float *)(local_78 + 0x2c + local_7c * 0x20)
             , *pfVar1 <= (float)fVar7 && (float)fVar7 != *pfVar1)) {
            if (*(char *)(local_78 + local_7c * 0x20 + 0x30) == 'a') {
              uVar5 = FUN_005c8250("apammo",0,local_78 + 0x30 + local_7c * 0x20,0,0);
              *(undefined4 *)(local_78 + 0x28 + local_7c * 0x20) = uVar5;
            }
            else {
              uVar5 = FUN_005c8250("aprepa",0,local_78 + 0x30 + local_7c * 0x20,0,0);
              *(undefined4 *)(local_78 + 0x28 + local_7c * 0x20) = uVar5;
            }
            *(undefined1 *)(local_78 + 0x44 + local_7c * 0x20) = 0;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

