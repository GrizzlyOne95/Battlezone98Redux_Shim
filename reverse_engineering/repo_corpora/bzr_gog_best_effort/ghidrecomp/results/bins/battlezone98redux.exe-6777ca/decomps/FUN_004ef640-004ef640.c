
void __thiscall FUN_004ef640(int param_1,undefined4 *param_2,int *param_3)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined4 local_18;
  undefined2 local_14;
  undefined4 local_12;
  undefined2 local_e;
  undefined4 *local_c;
  int local_8;
  
  local_c = param_2;
  *param_3 = *param_3 + 0x12;
  local_8 = param_1;
  puVar2 = (undefined4 *)
           FUN_006259c0(local_20,*(undefined4 *)(param_1 + 0x114),*(undefined4 *)(param_1 + 0x118),
                        *(undefined4 *)(param_1 + 0x11c));
  local_12 = *puVar2;
  local_e = *(undefined2 *)(puVar2 + 1);
  *local_c = local_12;
  *(undefined2 *)(local_c + 1) = local_e;
  puVar2 = (undefined4 *)
           FUN_006259c0(local_28,*(undefined4 *)(local_8 + 0x120),*(undefined4 *)(local_8 + 0x124),
                        *(undefined4 *)(local_8 + 0x128));
  local_18 = *puVar2;
  local_14 = *(undefined2 *)(puVar2 + 1);
  *(undefined4 *)((int)local_c + 6) = local_18;
  *(undefined2 *)((int)local_c + 10) = local_14;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_8 + 0x218) + 0xc4));
  *(undefined1 *)(local_c + 3) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_8 + 0x218) + 200));
  *(undefined1 *)((int)local_c + 0xd) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_8 + 0x218) + 0xcc));
  *(undefined1 *)((int)local_c + 0xe) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_8 + 0x218) + 0xd0));
  *(undefined1 *)((int)local_c + 0xf) = uVar1;
  *(undefined1 *)(local_c + 4) = 0;
  if (*(int *)(*(int *)(local_8 + 0x218) + 0xd8) != 0) {
    *(byte *)(local_c + 4) = *(byte *)(local_c + 4) | 1;
  }
  if (*(int *)(*(int *)(local_8 + 0x218) + 0xd4) != 0) {
    *(byte *)(local_c + 4) = *(byte *)(local_c + 4) | 2;
  }
  if (*(int *)(*(int *)(local_8 + 0x218) + 0xdc) != 0) {
    *(byte *)(local_c + 4) = *(byte *)(local_c + 4) | 4;
  }
  if ((*(uint *)(*(int *)(local_8 + 0xdc) + 0x14) & 1) != 0) {
    *(byte *)(local_c + 4) = *(byte *)(local_c + 4) | 8;
  }
  if ((*(uint *)(*(int *)(local_8 + 0xdc) + 0x14) & 0x400) != 0) {
    *(byte *)(local_c + 4) = *(byte *)(local_c + 4) | 0x10;
  }
  if ((*(uint *)(*(int *)(local_8 + 0xdc) + 0x14) & 0x10) != 0) {
    iVar3 = FUN_004e96a0();
    if (iVar3 != 0) {
      *(byte *)(local_c + 4) = *(byte *)(local_c + 4) | 0x40;
    }
  }
  FUN_004ae6f0((int)local_c + 0x12,param_3);
  *(undefined4 *)(local_8 + 0x2c4) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 0xcc);
  *(undefined4 *)(local_8 + 0x2c8) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 0xc4);
  *(undefined4 *)(local_8 + 0x2cc) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 200);
  *(undefined4 *)(local_8 + 0x2d0) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 0xd0);
  *(undefined4 *)(local_8 + 0x2d8) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 0xd8);
  *(undefined4 *)(local_8 + 0x2dc) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 0xd4);
  *(undefined4 *)(local_8 + 0x2e0) = *(undefined4 *)(*(int *)(local_8 + 0x218) + 0xdc);
  return;
}

