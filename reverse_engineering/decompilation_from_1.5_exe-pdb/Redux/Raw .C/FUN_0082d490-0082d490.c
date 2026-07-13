
undefined4 FUN_0082d490(undefined4 param_1,undefined4 param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)FUN_0082c4a6(param_1,param_2);
  if (puVar1 == &DAT_0086ed18) {
    return 0xffffffff;
  }
  return *(undefined4 *)(puVar1 + 8);
}

