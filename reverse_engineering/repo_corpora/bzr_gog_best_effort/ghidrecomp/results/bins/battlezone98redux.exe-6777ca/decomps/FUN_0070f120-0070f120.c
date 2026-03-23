
undefined4 FUN_0070f120(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 *puVar4;
  
  pcVar3 = param_3;
  pcVar1 = (char *)FUN_00417780(param_2);
  pcVar2 = (char *)FUN_00417780(param_1);
  pcVar3 = std::_Find_unchecked<char_const*,char>(pcVar2,pcVar1,pcVar3);
  puVar4 = (undefined4 *)FUN_0042ef30(&param_1,pcVar3);
  return *puVar4;
}

