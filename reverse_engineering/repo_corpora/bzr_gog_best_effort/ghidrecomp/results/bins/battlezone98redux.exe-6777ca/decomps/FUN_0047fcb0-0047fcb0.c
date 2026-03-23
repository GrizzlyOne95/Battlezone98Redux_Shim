
void __fastcall FUN_0047fcb0(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  float10 fVar5;
  undefined1 local_5c [16];
  undefined4 local_4c;
  undefined1 local_30 [4];
  undefined4 local_2c;
  undefined4 local_24;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar2 = FUN_004b9830();
  if (cVar2 == '\0') {
    if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x1000000) != 0) {
      (**(code **)(*(int *)(param_1 + 0x18) + 0x14))();
      goto LAB_0047febc;
    }
    if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) != 0) {
      (**(code **)(*(int *)(param_1 + 0x18) + 0x10))();
      goto LAB_0047febc;
    }
  }
  iVar1 = *(int *)(param_1 + 0xf8);
  if (((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) == 0) &&
     (*(char *)(iVar1 + 0x150) != '\0')) {
    iVar3 = FUN_00439e60();
    local_14 = (float)((double)*(float *)(param_1 + 0x108) - *(double *)(iVar3 + 0x160));
    local_10 = (float)((double)*(float *)(param_1 + 0x10c) - *(double *)(iVar3 + 0x168));
    local_c = (float)((double)*(float *)(param_1 + 0x110) - *(double *)(iVar3 + 0x170));
    fVar5 = (float10)FUN_004428b0(&local_14,&local_14);
    if (2500.0 <= (float)fVar5) {
      if (*(int *)(param_1 + 0x230) != 0) {
        FUN_0043aaa0(*(undefined4 *)(param_1 + 0x230));
        *(undefined4 *)(param_1 + 0x230) = 0;
      }
    }
    else if ((*(int *)(param_1 + 0x230) == 0) && (*(char *)(iVar1 + 0x150) != '\0')) {
      FUN_0043a990(local_5c);
      local_4c = 1;
      FUN_0043a9e0(local_30);
      local_24 = 1;
      local_2c = 10;
      uVar4 = FUN_0043aa30(iVar1 + 0x150,*(undefined4 *)(param_1 + 0xf4),local_5c,local_30);
      *(undefined4 *)(param_1 + 0x230) = uVar4;
    }
  }
  FUN_004db100();
LAB_0047febc:
  FUN_0083e885();
  return;
}

