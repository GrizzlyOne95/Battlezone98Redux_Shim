
undefined4 * __thiscall FUN_004f5520(undefined4 *param_1,undefined4 param_2)

{
  FUN_00461580(param_2,0);
  *param_1 = Inst01Event::vftable;
  *(undefined1 *)(param_1 + 1) = 1;
  *(undefined1 *)(param_1 + 0xb) = 0;
  *(undefined1 *)((int)param_1 + 0x2d) = 0;
  *(undefined1 *)((int)param_1 + 0x2e) = 0;
  return param_1;
}

