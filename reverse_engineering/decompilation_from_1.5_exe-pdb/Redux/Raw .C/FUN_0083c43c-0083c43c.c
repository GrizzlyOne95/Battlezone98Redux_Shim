
void FUN_0083c43c(undefined4 param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)FUN_0083c410(param_1,*(undefined4 *)(param_2 + 8));
  *puVar1 = *puVar1 ^ ((uint)((*puVar1 & 0x3fc0) == 0) * 0x40 ^ *puVar1) & 0x3fc0;
  return;
}

