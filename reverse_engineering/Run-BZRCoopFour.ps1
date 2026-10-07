# Focused four-player qualification; regenerate misn05-coop from current CR/EXU
# before running. Each case prepares four isolated clients and closes them.
param([string]$BZRCoopRoot = 'C:\BZRCoop', [string]$Only = '')
$cases = @(
    'misn05 four-services Override=misn05-coop',
    'misn05 win Override=misn05-coop',
    'misn05 win Override=misn05-coop GuestClient=2',
    'misn05 win Override=misn05-coop GuestClient=3',
    'misn05 win Override=misn05-coop Skipper=host',
    'misn05 win Override=misn05-coop Skipper=none',
    'misn05 lose Override=misn05-coop Destroyed=factory',
    'misn05 lose Override=misn05-coop Destroyed=recycler',
    'misn05 host-leaves Override=misn05-coop'
)
& "$PSScriptRoot\Run-BZRCoopSuite.ps1" -Clients 4 -StopOnFailure -Cases $cases -Only $Only -BZRCoopRoot $BZRCoopRoot
exit $LASTEXITCODE
