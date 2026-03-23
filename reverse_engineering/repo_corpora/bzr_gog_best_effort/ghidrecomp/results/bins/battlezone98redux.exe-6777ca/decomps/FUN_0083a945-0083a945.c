
void FUN_0083a945(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x14) = *puVar1;
  FUN_0083b0a4(*(undefined4 *)(param_1 + 0xc),*(undefined1 *)(puVar1 + 2));
  if (*(char *)((int)puVar1 + 9) != '\0') {
    FUN_0083c5d2(param_1,0x23,*(undefined1 *)(puVar1 + 2),0,0);
  }
  *(uint *)(param_1 + 0x24) = (uint)*(byte *)(param_1 + 0x32);
  FUN_0083cadc(param_1,puVar1[1]);
  return;
}

