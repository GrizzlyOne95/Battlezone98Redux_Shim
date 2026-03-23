
void __fastcall FUN_0047c0d0(int param_1)

{
  int iVar1;
  int local_c;
  char local_6;
  char local_5;
  
  local_5 = 'a';
  iVar1 = FUN_00417c70();
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0xec) == 0) {
      iVar1 = (*(code *)**(undefined4 **)(iVar1 + 0x18))();
      local_5 = *(char *)(iVar1 + 0xcc);
    }
    else {
      local_5 = *(char *)(*(int *)(iVar1 + 0xec) + 0xcc);
    }
  }
  if (local_5 == 'c') {
    local_6 = 's';
  }
  else {
    local_6 = 'a';
  }
  for (local_c = 0; local_c < 0xe; local_c = local_c + 1) {
    sprintf((char *)(param_1 + 0x130 + local_c * 0x10),"%cbetty%d.wav",(int)local_5,local_c + 1);
    iVar1 = FUN_00481f10(param_1 + 0x130 + local_c * 0x10);
    if (iVar1 == 0) {
      sprintf((char *)(param_1 + 0x130 + local_c * 0x10),"%cbetty%d.wav",(int)local_6,local_c + 1);
    }
  }
  *(int *)(param_1 + 0x128) = param_1 + 0x28;
  *(int *)(param_1 + 300) = param_1 + 0x28;
  DAT_00915565 = 1;
  *(undefined4 *)(param_1 + 0x210) = 0xf149f2ca;
  return;
}

