
CDC * __fastcall FUN_005c3220(CDC *param_1)

{
  CDC::CDC(param_1);
  *(undefined ***)param_1 = ScavengerProcess::vftable;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0x7149f2ca;
  *(undefined4 *)(param_1 + 0x54) = 0;
  return param_1;
}

