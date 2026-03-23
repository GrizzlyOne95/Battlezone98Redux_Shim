
void __fastcall FUN_0084475d(undefined4 param_1,int param_2)

{
  byte in_FPUControlWord;
  
  if ((param_2 == 8) || ((*(byte *)((int)&DAT_008a3078 + param_2 + 7) & in_FPUControlWord) == 0)) {
    except1(param_2,0);
  }
  return;
}

