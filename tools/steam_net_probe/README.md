# Standalone Steam networking probe

Run `./build.ps1` with Visual Studio C++ tools and the Steam BZR install present.
The build needs network access on first use to fetch public Valve headers at
`d534c19aa760df3fb75fd20db13ba1932b8a5463`; cached headers are reused.
This diagnostic is not part of the shipped OpenShim build or package. It stages
the shipped Steam DLL beside its own executable without replacing game files.

A successful listener/config/relay probe is not a two-account connection test.
Publisher configuration requirements for appid 301650 remain UNKNOWN.
