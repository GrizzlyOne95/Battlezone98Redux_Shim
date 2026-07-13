
void FUN_00442900(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  *param_1 = 0;
  param_1[1] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_10,0,0,0);
  param_1[0x1b] = *puVar1;
  param_1[0x1c] = puVar1[1];
  param_1[0x1d] = puVar1[2];
  FUN_00444970(param_1 + 2);
  return;
}

