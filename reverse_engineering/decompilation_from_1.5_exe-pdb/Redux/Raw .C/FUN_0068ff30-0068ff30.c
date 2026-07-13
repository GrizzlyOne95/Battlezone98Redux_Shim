
void FUN_0068ff30(int param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(DAT_00920f04 + param_1 * 4);
  if (param_2 == 0) {
    FUN_00690150(*puVar1,param_3);
  }
  else {
    puVar1[param_2 + 0x2f] = puVar1[param_2 + 0x2f] - param_3;
    puVar1[0x2f] = puVar1[0x2f] - param_3;
  }
  return;
}

