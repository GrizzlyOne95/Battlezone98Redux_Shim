
undefined4 * FUN_0082d752(code *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = (undefined4 *)(*param_1)(param_2,0,0,0x178);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    *(undefined1 *)(puVar1 + 1) = 8;
    *(undefined1 *)(puVar1 + 0x23) = 0x21;
    *(undefined1 *)((int)puVar1 + 5) = 0x61;
    FUN_0082d824(puVar1,puVar1 + 0x1e);
    puVar1[0x21] = param_1;
    puVar1[0x22] = param_2;
    puVar1[0x40] = puVar1 + 0x3c;
    puVar1[0x41] = puVar1 + 0x3c;
    puVar1[0x3a] = puVar1;
    puVar1[0x2e] = 0;
    puVar1[0x20] = 0;
    puVar1[0x1f] = 0;
    puVar1[0x1e] = 0;
    *(undefined4 *)(puVar1[4] + 0x68) = 0;
    puVar1[0x26] = puVar1 + 0x25;
    puVar1[0x25] = puVar1;
    puVar1[0x32] = 200;
    puVar1[0x33] = 200;
    puVar1[0x2b] = 0;
    puVar1[0x2d] = 0;
    puVar1[0x34] = 0;
    *(undefined1 *)((int)puVar1 + 0x8d) = 0;
    puVar1[0x24] = 0;
    puVar1[0x27] = 0;
    puVar1[0x28] = 0;
    puVar1[0x29] = 0;
    puVar1[0x2a] = 0;
    puVar1[0x2f] = 0x178;
    puVar1[0x31] = 0;
    puVar3 = puVar1 + 0x44;
    for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    iVar2 = FUN_0082f4cb(puVar1,FUN_0082d5cb,0);
    if (iVar2 != 0) {
      FUN_0082d56c(puVar1);
      puVar1 = (undefined4 *)0x0;
    }
  }
  return puVar1;
}

