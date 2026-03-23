
bool FUN_0080b8c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_30 [20];
  undefined1 local_1c [16];
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_007ff1f0(param_5);
  local_8 = *param_1;
  uVar2 = make_input_adapter_character_source<>(local_1c,&local_8,param_2,param_3,param_4,param_5);
  puVar3 = (undefined4 *)FUN_0080bfe0(local_30,uVar2);
  cVar1 = FUN_0080c060(local_c,*puVar3,puVar3[1],puVar3[2],puVar3[3],puVar3[4]);
  if (cVar1 == '\0') {
    *param_1 = local_8;
  }
  return cVar1 == '\0';
}

