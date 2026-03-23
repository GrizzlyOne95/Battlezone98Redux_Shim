
void __thiscall FUN_0074c470(int param_1,undefined4 param_2)

{
  short sVar1;
  char cVar2;
  short sVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined1 *puVar7;
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  undefined1 local_90 [4];
  int local_8c;
  undefined1 local_88 [4];
  undefined1 local_84 [4];
  int local_80;
  undefined1 local_79;
  undefined1 local_78 [28];
  undefined1 local_5c [28];
  undefined1 local_40 [28];
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_79 = 0;
  local_8c = param_1;
  FUN_00578c20(local_84,param_1 + 0x28);
  uVar5 = FID_conflict_begin(local_9c);
  cVar2 = FUN_00420f10(uVar5);
  if (cVar2 != '\0') {
    puVar7 = local_88;
    uVar5 = param_2;
    FUN_00422150(puVar7,param_2);
    FUN_00578c20(puVar7,uVar5);
    puVar7 = local_90;
    FUN_00422150(puVar7);
    uVar5 = FID_conflict_begin(puVar7);
    cVar2 = FUN_00420f10(uVar5);
    if (cVar2 != '\0') {
      local_80 = FUN_00746690(param_2);
      if (local_80 != 0) {
        iVar6 = FUN_00422150();
        FUN_0075cf00(local_24,iVar6 + 0x54);
        FUN_006cac80(local_5c);
        cVar2 = FUN_004c85a0();
        if (cVar2 != '\0') {
          puVar7 = local_98;
          FUN_006cac80(local_78);
          FUN_006b32b0(puVar7);
          iVar6 = FUN_006b2e30();
          if ((*(int *)(local_80 + 0x90) == iVar6) && (*(char *)(local_80 + 0x8c) == '\0')) {
            sVar1 = *(short *)(local_80 + 0x94);
            sVar3 = FUN_006cac60();
            if (sVar1 == sVar3) goto LAB_0074c60a;
          }
          *(undefined1 *)(local_80 + 0x8c) = 0;
          puVar7 = local_94;
          FUN_006cac80(local_40);
          FUN_006b32b0(puVar7);
          uVar5 = FUN_006b2e30();
          *(undefined4 *)(local_80 + 0x90) = uVar5;
          uVar4 = FUN_006cac60();
          *(undefined2 *)(local_80 + 0x94) = uVar4;
          local_79 = 1;
        }
      }
    }
  }
LAB_0074c60a:
  FUN_0083e885();
  return;
}

