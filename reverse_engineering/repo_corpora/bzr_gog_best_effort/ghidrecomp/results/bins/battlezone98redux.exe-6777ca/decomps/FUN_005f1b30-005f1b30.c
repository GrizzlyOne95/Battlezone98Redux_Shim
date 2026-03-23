
void __thiscall FUN_005f1b30(int param_1,undefined4 *param_2,int *param_3)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_1c [10];
  undefined4 local_12;
  undefined2 local_e;
  int local_c;
  undefined4 *local_8;
  
  local_8 = param_2;
  *param_3 = *param_3 + 10;
  local_c = param_1;
  puVar2 = (undefined4 *)
           FUN_006259c0(local_1c,*(undefined4 *)(param_1 + 0x120),*(undefined4 *)(param_1 + 0x124),
                        *(undefined4 *)(param_1 + 0x128));
  local_12 = *puVar2;
  local_e = *(undefined2 *)(puVar2 + 1);
  *local_8 = local_12;
  *(undefined2 *)(local_8 + 1) = local_e;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x218) + 0xc4));
  *(undefined1 *)((int)local_8 + 6) = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x218) + 200));
  *(undefined1 *)((int)local_8 + 7) = uVar1;
  *(undefined1 *)(local_8 + 2) = 0;
  if (*(int *)(*(int *)(local_c + 0x218) + 0xd8) != 0) {
    *(byte *)(local_8 + 2) = *(byte *)(local_8 + 2) | 1;
  }
  if (*(int *)(*(int *)(local_c + 0x218) + 0xd4) != 0) {
    *(byte *)(local_8 + 2) = *(byte *)(local_8 + 2) | 2;
  }
  if (*(int *)(*(int *)(local_c + 0x218) + 0xdc) != 0) {
    *(byte *)(local_8 + 2) = *(byte *)(local_8 + 2) | 4;
  }
  if ((*(uint *)(*(int *)(local_c + 0x218) + 0x114) & 0x20) != 0) {
    *(byte *)(local_8 + 2) = *(byte *)(local_8 + 2) | 8;
  }
  if ((*(uint *)(*(int *)(local_c + 0xdc) + 0x14) & 0x10) != 0) {
    iVar3 = FUN_004e96a0();
    if (iVar3 != 0) {
      *(byte *)(local_8 + 2) = *(byte *)(local_8 + 2) | 0x40;
    }
  }
  FUN_004ae6f0((int)local_8 + 10,param_3);
  return;
}

