
undefined1 * __thiscall
FUN_006f72a0(undefined1 *param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,int param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 local_14 [8];
  undefined1 *local_c;
  undefined1 local_5;
  
  if (param_6 == 0) {
    local_5 = 1;
  }
  else {
    local_5 = param_2;
  }
  *param_1 = local_5;
  local_c = param_1;
  puVar2 = (undefined4 *)FUN_006ae430(local_14,param_3,param_6);
  uVar1 = puVar2[1];
  *(undefined4 *)(local_c + 4) = *puVar2;
  *(undefined4 *)(local_c + 8) = uVar1;
  *(undefined4 *)(local_c + 0xc) = param_4;
  *(undefined4 *)(local_c + 0x10) = param_5;
  *(undefined4 *)(local_c + 0x14) = 0;
  *(int *)(local_c + 0x18) = param_6;
  return local_c;
}

