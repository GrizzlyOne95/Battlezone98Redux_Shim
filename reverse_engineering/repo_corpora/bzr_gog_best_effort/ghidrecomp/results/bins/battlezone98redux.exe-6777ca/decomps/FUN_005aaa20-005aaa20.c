
void __thiscall FUN_005aaa20(int param_1,undefined4 *param_2,int *param_3)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_34 [8];
  undefined1 local_2c [8];
  undefined4 local_24;
  undefined2 local_20;
  undefined4 local_1e;
  undefined2 local_1a;
  float local_14;
  float local_10;
  int local_c;
  undefined4 *local_8;
  
  local_8 = param_2;
  *param_3 = *param_3 + 0x12;
  local_c = param_1;
  puVar2 = (undefined4 *)
           FUN_006259c0(local_2c,*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x118),
                        *(undefined4 *)(param_1 + 0x11c));
  local_1e = *puVar2;
  local_1a = *(undefined2 *)(puVar2 + 1);
  *local_8 = local_1e;
  *(undefined2 *)(local_8 + 1) = local_1a;
  puVar2 = (undefined4 *)
           FUN_006259c0(local_34,*(undefined4 *)(local_c + 0x120),*(undefined4 *)(local_c + 0x124),
                        *(undefined4 *)(local_c + 0x128));
  local_24 = *puVar2;
  local_20 = *(undefined2 *)(puVar2 + 1);
  *(undefined4 *)((int)local_8 + 6) = local_24;
  *(undefined2 *)((int)local_8 + 10) = local_20;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x210) + 0xd0));
  *(undefined1 *)(local_8 + 3) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x210) + 0xc4));
  *(undefined1 *)((int)local_8 + 0xd) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x210) + 200));
  *(undefined1 *)((int)local_8 + 0xe) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x210) + 0xcc));
  *(undefined1 *)((int)local_8 + 0xf) = uVar1;
  *(undefined1 *)(local_8 + 4) = 0;
  if (*(int *)(*(int *)(local_c + 0x210) + 0xd4) != 0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 1;
  }
  if ((*(uint *)(*(int *)(local_c + 0x210) + 0x114) & 0x8000) != 0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 2;
  }
  if ((*(uint *)(*(int *)(local_c + 0x210) + 0x114) & 0x20) != 0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 4;
  }
  if ((*(uint *)(*(int *)(local_c + 0x210) + 0x114) & 1) != 0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 8;
  }
  if ((*(uint *)(*(int *)(local_c + 0x210) + 0x114) & 4) != 0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 0x10;
  }
  if ((*(uint *)(*(int *)(local_c + 0x210) + 0x114) & 8) != 0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 0x20;
  }
  fVar3 = (float10)FUN_0046fbd0();
  local_14 = (float)fVar3;
  if (local_14 < 0.0) {
    *(byte *)(local_8 + 4) = *(byte *)(local_8 + 4) | 0x80;
  }
  if (0.0 < *(float *)(local_c + 0x1e8)) {
    local_10 = *(float *)(local_c + 0x1e8);
    if (1.0 < local_10) {
      local_10 = 1.0;
    }
    FUN_0043d610(local_10 * 255.0);
    uVar1 = FUN_0083f040();
    *(undefined1 *)((int)local_8 + 0x11) = uVar1;
  }
  else {
    *(undefined1 *)((int)local_8 + 0x11) = 0;
  }
  return;
}

