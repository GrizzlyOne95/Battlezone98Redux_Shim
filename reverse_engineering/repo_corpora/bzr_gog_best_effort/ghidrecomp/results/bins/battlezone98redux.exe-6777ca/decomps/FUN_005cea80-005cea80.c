
undefined4 * __thiscall
FUN_005cea80(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c960;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00586440(param_2,param_3,param_4);
  local_8 = 0;
  *param_1 = SeismicWaveClass::vftable;
  FUN_00589430(param_1 + 8);
  local_8._0_1_ = 1;
  FUN_00589800(0x7ff8e41b,0x6ba8d14a,param_1 + 0x1e,*(undefined4 *)(param_2 + 0x78));
  if ((float)param_1[0x1e] <= 0.0001 && (float)param_1[0x1e] != 0.0001) {
    param_1[0x1e] = 0x38d1b717;
  }
  param_1[0x1f] = 1.0 / (float)param_1[0x1e];
  param_1[0x20] = (float)param_1[0x1f] * -2.5 * (float)param_1[0x1f];
  FUN_00589800(0x7ff8e41b,0x5ad61a27,param_1 + 0x21,*(undefined4 *)(param_2 + 0x84));
  FUN_00589800(0x7ff8e41b,0x971beda4,param_1 + 0x22,*(undefined4 *)(param_2 + 0x88));
  FUN_00589800(0x7ff8e41b,0x3a74c50d,param_1 + 0x23,*(undefined4 *)(param_2 + 0x8c));
  param_1[0x24] = 1.0 / (float)param_1[0x23];
  FUN_00589800(0x7ff8e41b,0x5ba4f6b0,param_1 + 0x25,*(undefined4 *)(param_2 + 0x94));
  param_1[0x26] = 1.0 / (float)param_1[0x25];
  FUN_00589800(0x7ff8e41b,0xad935b02,param_1 + 0x27,*(undefined4 *)(param_2 + 0x9c));
  FUN_00589800(0x7ff8e41b,0xbe57c368,param_1 + 0x28,*(undefined4 *)(param_2 + 0xa0));
  FUN_00589800(0x7ff8e41b,0xdee4f011,param_1 + 0x29,*(undefined4 *)(param_2 + 0xa4));
  FUN_00589800(0x7ff8e41b,0xce21ecf8,param_1 + 0x2a,*(undefined4 *)(param_2 + 0xa8));
  FUN_00589800(0x7ff8e41b,0xf57df3d2,param_1 + 0x2b,*(undefined4 *)(param_2 + 0xac));
  FUN_00589800(0x7ff8e41b,0x9ebf26a7,param_1 + 0x2c,*(undefined4 *)(param_2 + 0xb0));
  FUN_00589800(0x7ff8e41b,0x3b226d18,param_1 + 0x2d,*(undefined4 *)(param_2 + 0xb4));
  FUN_00589800(0x7ff8e41b,0x2fc331e2,param_1 + 0x2e,*(undefined4 *)(param_2 + 0xb8));
  FUN_00589800(0x7ff8e41b,0x762c10d0,param_1 + 0x2f,*(undefined4 *)(param_2 + 0xbc));
  FUN_00589800(0x7ff8e41b,&DAT_02168f61,param_1 + 0x30,*(undefined4 *)(param_2 + 0xc0));
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00589530();
  ExceptionList = local_10;
  return param_1;
}

