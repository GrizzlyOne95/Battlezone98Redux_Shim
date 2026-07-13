
undefined4 FUN_00840c10(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 in_stack_00000014;
  uint in_stack_00000018;
  int in_stack_0000001c;
  int in_stack_00000020;
  void *in_stack_00000024;
  undefined4 in_stack_00000034;
  uint in_stack_00000038;
  int in_stack_0000003c;
  int in_stack_00000040;
  undefined4 *in_stack_00000044;
  undefined4 in_stack_00000054;
  uint in_stack_00000058;
  int in_stack_0000005c;
  int in_stack_00000060;
  void *in_stack_00000064;
  uint in_stack_00000078;
  int in_stack_0000007c;
  int in_stack_00000080;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_008657e0;
  local_c = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffffec;
  ExceptionList = &local_c;
  local_4 = 3;
  while( true ) {
    if (((in_stack_0000001c == in_stack_0000003c) && (in_stack_00000020 == in_stack_00000040)) ||
       ((in_stack_0000005c == in_stack_0000007c && (in_stack_00000060 == in_stack_00000080)))) {
      if ((in_stack_0000001c == in_stack_0000003c) && (in_stack_00000020 == in_stack_00000040)) {
        if ((in_stack_0000005c == in_stack_0000007c) && (in_stack_00000060 == in_stack_00000080)) {
          uVar4 = 0;
          goto LAB_00840d2e;
        }
        if (in_stack_00000020 == in_stack_00000040) {
          uVar4 = 0xffffffff;
          goto LAB_00840d2e;
        }
      }
      uVar4 = 1;
      goto LAB_00840d2e;
    }
    puVar3 = &stack0x00000044;
    if (7 < in_stack_00000058) {
      puVar3 = in_stack_00000044;
    }
    iVar2 = FUN_00840080(0,in_stack_00000014,puVar3,in_stack_00000054);
    if (iVar2 < 0) {
      uVar4 = 0xffffffff;
      goto LAB_00840d2e;
    }
    puVar3 = &param_1;
    if (7 < in_stack_00000018) {
      puVar3 = param_1;
    }
    iVar2 = FUN_00840080(0,in_stack_00000054,puVar3,in_stack_00000014);
    if (iVar2 < 0) break;
    FUN_00840f20(&param_1,uVar1);
    FUN_00840f20(&stack0x00000044);
  }
  uVar4 = 1;
LAB_00840d2e:
  if (7 < in_stack_00000018) {
    operator_delete(param_1);
  }
  in_stack_00000018 = 7;
  in_stack_00000014 = 0;
  param_1 = (undefined4 *)((uint)param_1 & 0xffff0000);
  if (7 < in_stack_00000038) {
    operator_delete(in_stack_00000024);
  }
  in_stack_00000038 = 7;
  in_stack_00000034 = 0;
  in_stack_00000024 = (void *)((uint)in_stack_00000024 & 0xffff0000);
  if (7 < in_stack_00000058) {
    operator_delete(in_stack_00000044);
  }
  in_stack_00000058 = 7;
  in_stack_00000054 = 0;
  in_stack_00000044 = (undefined4 *)((uint)in_stack_00000044 & 0xffff0000);
  if (7 < in_stack_00000078) {
    operator_delete(in_stack_00000064);
  }
  ExceptionList = local_c;
  return uVar4;
}

