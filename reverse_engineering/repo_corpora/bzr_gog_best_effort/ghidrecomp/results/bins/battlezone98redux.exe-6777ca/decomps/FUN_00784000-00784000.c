
byte FUN_00784000(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  
  bVar1 = param_1 - DAT_02ce99c0 < 0;
  bVar2 = param_2 - DAT_02cd9984 < 0;
  return ((bVar1 * '\x02' + ((param_1 + -1) - DAT_02ce99a0 < 0 || bVar1)) * '\x02' + bVar2) * '\x02'
         + ((param_2 + -1) - DAT_02ce99c4 < 0 || bVar2) ^ 5;
}

