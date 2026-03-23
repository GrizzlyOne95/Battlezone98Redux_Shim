
void FUN_00444970(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined1 local_10 [12];
  
  *param_1 = 0;
  param_1[1] = 0x7149f2ca;
  param_1[2] = 0;
  param_1[3] = 0x7149f2ca;
  param_1[4] = 0x3f800000;
  param_1[5] = 0;
  puVar1 = (undefined4 *)FUN_00440000(local_10,0,0,0);
  param_1[0xf] = *puVar1;
  param_1[0x10] = puVar1[1];
  param_1[0x11] = puVar1[2];
  param_1[0xc] = param_1[0xf];
  param_1[0xd] = param_1[0x10];
  param_1[0xe] = param_1[0x11];
  param_1[9] = param_1[0xc];
  param_1[10] = param_1[0xd];
  param_1[0xb] = param_1[0xe];
  param_1[6] = param_1[9];
  param_1[7] = param_1[10];
  param_1[8] = param_1[0xb];
  return;
}

