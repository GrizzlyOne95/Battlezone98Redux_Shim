
void __thiscall FUN_0083d5d0(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  int iVar4;
  
  if (param_3 != 0) {
    uVar3 = param_3 + 3U & 0xfffffffc;
    *(uint *)(param_1 + 0x28) = uVar3;
    *(int *)(param_1 + 0x2c) = param_2;
    if ((uVar3 != 0) && (param_4 == 0)) {
      param_4 = (uVar3 + 0x3f) / uVar3;
    }
    *(uint *)(param_1 + 0x30) = param_4;
    if (param_4 < 8) {
      *(undefined4 *)(param_1 + 0x30) = 8;
    }
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    if (param_2 != 0) {
      *(undefined1 *)(param_1 + 0x40) = 1;
      pvVar2 = _aligned_malloc(uVar3 * param_2,0x10);
      *(void **)(param_1 + 0x3c) = pvVar2;
      uVar3 = 0;
      if (param_2 != 1) {
        do {
          iVar1 = uVar3 + 1;
          iVar4 = *(int *)(param_1 + 0x28) * uVar3;
          uVar3 = uVar3 + 1;
          *(int *)(iVar4 + *(int *)(param_1 + 0x3c)) =
               iVar1 * *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x3c);
        } while (uVar3 < *(int *)(param_1 + 0x2c) - 1U);
      }
      *(undefined4 *)
       ((*(int *)(param_1 + 0x2c) + -1) * *(int *)(param_1 + 0x28) + *(int *)(param_1 + 0x3c)) = 0;
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x3c);
    }
  }
  return;
}

