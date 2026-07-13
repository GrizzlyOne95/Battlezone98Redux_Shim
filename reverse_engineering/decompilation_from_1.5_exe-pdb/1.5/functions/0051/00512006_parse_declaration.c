/*
 * Entry: 00512006
 * Name: parse_declaration
 * Namespace: Global
 * Signature: int parse_declaration(char * param_1, int * param_2, int param_3, _domain * param_4, int param_5, char * param_6, char * * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl
parse_declaration(char *param_1,int *param_2,int param_3,_domain *param_4,int param_5,char *param_6,
                 char **param_7)

{
  int iVar1;
  double adStack_17714 [1000];
  int aiStack_157d4 [1000];
  int aiStack_14834 [1000];
  char *pcStack_13894;
  int *piStack_13890;
  int iStack_1388c;
  char acStack_13888 [80004];
  
  pcStack_13894 = param_1;
  piStack_13890 = param_2;
  if (param_5 == 6) {
    return 0;
  }
  IParse_Save_Only_Alpha_Numeric(param_7,IParse_Find_Char_Type);
  IParse_Parse_New_Command
            (*param_7,&iStack_1388c,aiStack_157d4,adStack_17714,(char (*) [80])acStack_13888,
             aiStack_14834);
  if (param_5 < 8) {
    if (param_5 == 7) {
      iVar1 = IParse_Parse_Pound_Define
                        (param_4,iStack_1388c,aiStack_157d4,adStack_17714,
                         (char (*) [80])acStack_13888,aiStack_14834);
      return iVar1;
    }
    if (param_5 == 1) {
      iVar1 = IParse_Parse_Int(param_4,iStack_1388c,aiStack_157d4,adStack_17714,
                               (char (*) [80])acStack_13888,aiStack_14834);
      return iVar1;
    }
    if (param_5 == 2) {
      iVar1 = 2;
    }
    else {
      if (param_5 != 3) {
        if (param_5 == 4) {
          iVar1 = IParse_Parse_Char(param_4,iStack_1388c,aiStack_157d4,adStack_17714,
                                    (char (*) [80])acStack_13888,aiStack_14834);
          return iVar1;
        }
        if (param_5 == 5) {
          iVar1 = IParse_Parse_Struct(param_4,iStack_1388c,aiStack_157d4,adStack_17714,
                                      (char (*) [80])acStack_13888,aiStack_14834);
          return iVar1;
        }
        goto LAB_005121a6;
      }
      iVar1 = 3;
    }
    iVar1 = IParse_Parse_Double(param_4,iStack_1388c,aiStack_157d4,adStack_17714,
                                (char (*) [80])acStack_13888,aiStack_14834,iVar1);
  }
  else {
    if (param_5 == 8) {
      iVar1 = IParse_Parse_Struct_Array
                        (param_4,param_6,iStack_1388c,aiStack_157d4,adStack_17714,
                         (char (*) [80])acStack_13888,aiStack_14834);
      return iVar1;
    }
    if (param_5 == 9) {
      iVar1 = IParse_Assign_To_Variable
                        (param_4,param_6,iStack_1388c,aiStack_157d4,adStack_17714,
                         (char (*) [80])acStack_13888,aiStack_14834);
      return iVar1;
    }
    if (param_5 == 0xb) {
      iVar1 = IParse_Parse_Conditional_Code
                        (pcStack_13894,piStack_13890,param_3,param_4,iStack_1388c,aiStack_157d4,
                         adStack_17714,(char (*) [80])acStack_13888,aiStack_14834);
      return iVar1;
    }
    if (param_5 == 0x10) {
      iVar1 = IParse_Parse_Include
                        (param_4,iStack_1388c,aiStack_157d4,adStack_17714,
                         (char (*) [80])acStack_13888,aiStack_14834);
      return iVar1;
    }
LAB_005121a6:
    iVar1 = -2;
  }
  return iVar1;
}
