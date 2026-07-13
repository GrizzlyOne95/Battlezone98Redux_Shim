
void FUN_0062f1c0(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_48 [64];
  undefined4 *local_8;
  
  if ((*(uint *)(param_1 + 0x14) & 0x200) == 0) {
    local_8 = *(undefined4 **)(param_1 + 0x88);
    fVar4 = (float10)FUN_00822d60();
    puVar1 = (undefined4 *)
             FUN_00444d50(local_48,param_1 + 0x20,*local_8,local_8[1],local_8[2],(float)fVar4);
    puVar3 = (undefined4 *)(param_1 + 0x20);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_00681a00(param_1,param_1 + 0x20);
  }
  return;
}

