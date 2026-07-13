/*
 * Entry: 00510e00
 * Name: IParse_Is_OK_Char_Not_Float
 * Namespace: Global
 * Signature: int IParse_Is_OK_Char_Not_Float(char param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Is_OK_Char_Not_Float(char param_1)

{
  int iVar1;
  
  iVar1 = isalnum((int)param_1);
  if (iVar1 != 0) {
    return 1;
  }
  if (((((((param_1 != ';') && (param_1 != '\"')) && (param_1 != '{')) &&
        (((param_1 != '}' && (param_1 != '\'')) &&
         ((param_1 != '=' && ((param_1 != '!' && (param_1 != '<')))))))) &&
       ((param_1 != '>' && (((param_1 != '.' && (param_1 != ',')) && (param_1 != '(')))))) &&
      (((param_1 != ')' && (param_1 != '[')) &&
       (((param_1 != ']' && ((param_1 != '*' && (param_1 != '^')))) && (param_1 != '+')))))) &&
     (((param_1 != '/' && (param_1 != '-')) && (param_1 != '#')))) {
    return (uint)(param_1 == '_');
  }
  return 2;
}
