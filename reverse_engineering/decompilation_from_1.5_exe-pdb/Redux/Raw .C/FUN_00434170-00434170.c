
void FUN_00434170(int param_1)

{
  if (DAT_008e706c != 9) {
    if (DAT_008e706c != param_1) {
      FUN_007d6a70("SetRunning: was %s, now %s\n",(&PTR_s_RUN_WAS_FAILURE_00871690)[DAT_008e706c],
                   (&PTR_s_RUN_WAS_FAILURE_00871690)[param_1]);
    }
    DAT_008e706c = param_1;
  }
  return;
}

