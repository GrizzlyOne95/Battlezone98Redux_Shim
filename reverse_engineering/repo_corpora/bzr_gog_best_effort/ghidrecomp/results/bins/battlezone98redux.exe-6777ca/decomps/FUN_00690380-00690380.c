
void FUN_00690380(int param_1,undefined4 param_2)

{
  FUN_006a5fd0("AIPSwitch %d to %0x\n",param_1,param_2);
  FUN_00695560(*(undefined4 *)(DAT_00920f04 + param_1 * 4),param_2);
  FUN_006a5fd0("AIPSwitch over\n");
  return;
}

