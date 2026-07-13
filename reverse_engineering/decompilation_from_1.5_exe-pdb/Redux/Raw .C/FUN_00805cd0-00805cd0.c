
bool FUN_00805cd0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  undefined4 *puVar2;
  undefined1 local_24 [16];
  undefined4 local_14;
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined1 local_5;
  
  local_c = *param_1;
  FUN_0068f260(param_5);
  local_5 = 0;
  puVar2 = (undefined4 *)
           make_input_adapter_character_source<>(local_24,&local_c,param_2,param_3,param_4,0);
  cVar1 = FUN_00806be0(local_14,local_10,*puVar2,puVar2[1],puVar2[2],puVar2[3]);
  if (cVar1 == '\0') {
    *param_1 = local_c;
  }
  return cVar1 == '\0';
}

