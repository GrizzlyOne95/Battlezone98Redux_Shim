
undefined4 FUN_006da220(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = param_4;
  pcVar1 = (char *)FUN_0042eee0(param_3);
  pcVar2 = (char *)FUN_0042eee0(param_2);
  pcVar3 = std::_Find_unchecked<char_const*,char>(pcVar2,pcVar1,pcVar3);
  FUN_006e8130(param_1,&param_2,pcVar3);
  return param_1;
}

