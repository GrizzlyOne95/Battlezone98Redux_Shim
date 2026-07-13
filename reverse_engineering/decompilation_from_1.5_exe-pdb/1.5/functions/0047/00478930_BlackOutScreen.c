/*
 * Entry: 00478930
 * Name: BlackOutScreen
 * Namespace: Global
 * Signature: void BlackOutScreen(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BlackOutScreen(long param_1)

{
  (*Device.Refresh.BlitFill)(&Device,param_1);
  (*Device.Refresh.Blit)(&Device);
  return;
}
