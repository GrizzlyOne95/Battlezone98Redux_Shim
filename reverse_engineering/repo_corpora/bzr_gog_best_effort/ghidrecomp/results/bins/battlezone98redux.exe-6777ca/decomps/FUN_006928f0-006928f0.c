
void __thiscall FUN_006928f0(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  FUN_006a5fd0("CreditDump Non Zero Accounts Team %d\n",*param_2,param_1);
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    if (param_2[iVar1 + 0x2f] != 0) {
      FUN_006a5fd0("   #%d %d\n",iVar1,param_2[iVar1 + 0x2f]);
    }
  }
  FUN_006a5fd0("   Prespent Allowance %d\n",param_2[0x2e]);
  FUN_006a5fd0("   Actual Cash      %d\n",*(undefined4 *)(&DAT_02ce9aa4 + *param_2 * 0x1e0));
  return;
}

