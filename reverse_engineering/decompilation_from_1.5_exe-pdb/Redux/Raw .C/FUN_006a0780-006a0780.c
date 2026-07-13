
void FUN_006a0780(uint param_1,int param_2)

{
  if (param_2 == 0) {
    DAT_009310b4 = ~param_1 & DAT_009310b4;
  }
  else {
    DAT_009310b4 = DAT_009310b4 | param_1;
  }
  return;
}

