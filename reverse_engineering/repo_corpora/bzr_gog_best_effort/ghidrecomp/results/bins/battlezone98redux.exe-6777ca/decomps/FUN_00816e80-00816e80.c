
bool FUN_00816e80(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_20 [16];
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  local_c = *param_1;
  local_5 = 0;
  puVar2 = (undefined4 *)
           make_input_adapter_character_source<>(local_20,&local_c,param_2,param_3,param_4,0);
  cVar1 = FUN_00817170(local_10,local_6,*puVar2,puVar2[1],puVar2[2],puVar2[3]);
  if (cVar1 == '\0') {
    *param_1 = local_c;
  }
  return cVar1 == '\0';
}

