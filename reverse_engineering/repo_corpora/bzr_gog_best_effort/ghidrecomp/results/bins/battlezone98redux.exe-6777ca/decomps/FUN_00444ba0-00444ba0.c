
void FUN_00444ba0(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int in_stack_00000014;
  undefined1 local_ec [72];
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined1 local_74 [12];
  undefined4 local_68 [6];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 local_44 [36];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_00440000(local_8c,0,0,0);
  local_14 = *puVar1;
  local_10 = puVar1[1];
  local_c = puVar1[2];
  for (; in_stack_00000014 != 0; in_stack_00000014 = FUN_00618b60(in_stack_00000014)) {
    puVar1 = (undefined4 *)FUN_0062bf70(local_ec,in_stack_00000014);
    puVar3 = local_68;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = (undefined4 *)FUN_004440d0(local_98,&stack0x00000008,local_44);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440130(local_74,local_20,local_1c,local_18,local_14,local_10,local_c);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    puVar1 = (undefined4 *)
             FUN_00440210(local_a4,&local_20,in_stack_00000014 + 0x20,local_50,local_4c,local_48);
    puVar1 = (undefined4 *)FUN_00440130(local_80,*puVar1,puVar1[1],puVar1[2]);
    local_14 = *puVar1;
    local_10 = puVar1[1];
    local_c = puVar1[2];
    FUN_00820180(&stack0x00000008,&stack0x00000008,1,in_stack_00000014 + 0x20);
  }
  *param_1 = local_14;
  param_1[1] = local_10;
  param_1[2] = local_c;
  FUN_0083e885();
  return;
}

