
/* WARNING: Removing unreachable block (ram,0x004e1868) */
/* WARNING: Removing unreachable block (ram,0x004e19a6) */

void FUN_004e17a0(void)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_bc [12];
  undefined1 local_b0 [12];
  undefined4 local_a4;
  undefined4 local_a0;
  int local_9c;
  int local_98;
  undefined4 *local_94;
  undefined4 *local_90;
  char local_8a;
  char local_89;
  int local_88;
  int local_84 [21];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c [4];
  char local_18 [4];
  undefined1 local_14 [4];
  undefined1 uStack_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_84[0] = FUN_0062ccc0(0,"fun3d\\GameObjectClass.cpp");
  *(undefined4 *)(local_84[0] + 8) = *(undefined4 *)(local_88 + 0x30);
  *(undefined4 *)(local_84[0] + 0xc) = *(undefined4 *)(local_88 + 0x34);
  FUN_0062b940(local_84[0],*(undefined4 *)(local_88 + 0x1c));
  local_98 = *(int *)(local_84[0] + 0x84) + -1;
  switch(*(int *)(local_84[0] + 0x84)) {
  case 1:
  case 3:
  case 4:
  case 6:
    strncpy(local_18,(char *)(local_88 + 0x28),8);
    local_a0 = 8;
    uStack_10 = 0;
    puVar1 = (undefined4 *)(local_1c + 3);
    do {
      local_94 = puVar1;
      local_89 = *(char *)((int)local_94 + 1);
      puVar1 = (undefined4 *)((int)local_94 + 1);
    } while (local_89 != '\0');
    *puVar1 = 0x6664762e;
    *(undefined1 *)((int)local_94 + 5) = 0;
    local_94 = puVar1;
    local_9c = FUN_008258d0(0,local_84,local_18);
    FUN_0062e650(local_84[0],local_88 + 0x10c,local_88 + 0x118);
    puVar1 = (undefined4 *)FUN_004e0040(local_bc,local_84[0]);
    local_30 = *puVar1;
    local_2c = puVar1[1];
    local_28 = puVar1[2];
    *(undefined4 *)(local_88 + 0x124) = local_30;
    *(undefined4 *)(local_88 + 0x128) = local_2c;
    *(undefined4 *)(local_88 + 300) = local_28;
    fVar2 = (float10)FUN_0062e590(local_84[0],*(undefined4 *)(local_88 + 0x124),
                                  *(undefined4 *)(local_88 + 0x128),*(undefined4 *)(local_88 + 300))
    ;
    *(float *)(local_88 + 0x130) = (float)fVar2;
    break;
  case 2:
  case 5:
  case 7:
  case 8:
  case 10:
  case 0xf:
    strncpy(local_18,(char *)(local_88 + 0x28),8);
    local_a4 = 8;
    uStack_10 = 0;
    puVar1 = (undefined4 *)(local_1c + 3);
    do {
      local_90 = puVar1;
      local_8a = *(char *)((int)local_90 + 1);
      puVar1 = (undefined4 *)((int)local_90 + 1);
    } while (local_8a != '\0');
    *puVar1 = 0x6664732e;
    *(undefined1 *)((int)local_90 + 5) = 0;
    local_90 = puVar1;
    local_9c = FUN_008253f0(0,local_84,local_18);
    FUN_0062e650(local_84[0],local_88 + 0x10c,local_88 + 0x118);
    puVar1 = (undefined4 *)FUN_004e0040(local_b0,local_84[0]);
    local_24 = *puVar1;
    local_20 = puVar1[1];
    local_1c = (undefined1  [4])puVar1[2];
    *(undefined4 *)(local_88 + 0x124) = local_24;
    *(undefined4 *)(local_88 + 0x128) = local_20;
    *(undefined1 (*) [4])(local_88 + 300) = local_1c;
    fVar2 = (float10)FUN_0062e590(local_84[0],*(undefined4 *)(local_88 + 0x124),
                                  *(undefined4 *)(local_88 + 0x128),*(undefined4 *)(local_88 + 300))
    ;
    *(float *)(local_88 + 0x130) = (float)fVar2;
    break;
  default:
    local_9c = 0;
  }
  if (local_9c == 0) {
    FUN_007d6c70("GameObject \"%s\" could not load \"%s\"\n",local_88 + 0x38,local_18);
  }
  FUN_0062bb50();
  FUN_0062d200(local_84[0],"fun3d\\GameObjectClass.cpp");
  FUN_0083e885();
  return;
}

