
void __fastcall FUN_0047c5f0(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  int iVar3;
  float10 fVar4;
  undefined1 local_50 [16];
  undefined4 local_40;
  code *local_28;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((((DAT_00915565 != '\0') && (*(int *)(param_1 + 300) != *(int *)(param_1 + 0x128))) &&
      (cVar2 = FUN_00437da0(), cVar2 == '\0')) && (iVar3 = FUN_0061a050(), iVar3 == 0)) {
    FUN_0043a990(local_50);
    local_28 = FUN_0047c5d0;
    local_40 = 5;
    FUN_0043a9e0(local_24);
    local_20 = 100;
    if (**(int **)(param_1 + 0x128) == param_1 + 0x1b0) {
      iVar3 = FUN_00417c70();
      fVar4 = (float10)(**(code **)(*(int *)(iVar3 + 0x18) + 0x1c))();
      if (0.25 <= (float)fVar4) {
        *(int *)(param_1 + 0x128) = *(int *)(param_1 + 0x128) + 4;
        if (param_1 + 0x128U <= *(uint *)(param_1 + 0x128)) {
          *(int *)(param_1 + 0x128) = param_1 + 0x28;
        }
        goto LAB_0047c77c;
      }
    }
    uVar1 = **(undefined4 **)(param_1 + 0x128);
    *(int *)(param_1 + 0x128) = *(int *)(param_1 + 0x128) + 4;
    iVar3 = FUN_0043aa30(uVar1,0,local_50,local_24);
    if (iVar3 != 0) {
      DAT_00915565 = '\0';
    }
    if (param_1 + 0x128U <= *(uint *)(param_1 + 0x128)) {
      *(int *)(param_1 + 0x128) = param_1 + 0x28;
    }
  }
LAB_0047c77c:
  FUN_0083e885();
  return;
}

