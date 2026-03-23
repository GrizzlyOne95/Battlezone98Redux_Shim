
void __thiscall FUN_006773d0(char *param_1,char *param_2)

{
  char *pcVar1;
  undefined4 *puVar2;
  undefined4 local_14;
  undefined4 local_10;
  char *local_c;
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  local_c = param_1;
  if (*(uint *)(param_1 + 0x14) < 0x10) {
    if (*(uint *)(param_2 + 0x14) < 0x10) {
      FUN_00677900(param_1,param_2);
    }
    else {
      local_14 = *(undefined4 *)param_2;
      pcVar1 = param_2;
      Getal(&local_7);
      destroy<>(pcVar1);
      std::char_traits<char>::copy(param_2,local_c,*(int *)(local_c + 0x10) + 1);
      puVar2 = &local_14;
      pcVar1 = local_c;
      Getal(&local_8);
      construct<>(pcVar1,puVar2);
    }
  }
  else if (*(uint *)(param_2 + 0x14) < 0x10) {
    local_10 = *(undefined4 *)param_1;
    Getal(&local_5);
    destroy<>(param_1);
    std::char_traits<char>::copy(local_c,param_2,*(int *)(param_2 + 0x10) + 1);
    puVar2 = &local_10;
    Getal(&local_6);
    construct<>(param_2,puVar2);
  }
  else {
    _Swap_adl<>(param_1,param_2);
  }
  return;
}

