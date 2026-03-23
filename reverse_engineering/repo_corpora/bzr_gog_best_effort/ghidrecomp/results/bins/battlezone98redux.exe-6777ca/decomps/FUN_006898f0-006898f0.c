
undefined4 * FUN_006898f0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = malloc(0xc);
  *puVar1 = 0xffffffff;
  puVar1[1] = 0;
  uVar2 = FUN_0068bed0(param_1);
  puVar1[2] = uVar2;
  return puVar1;
}

