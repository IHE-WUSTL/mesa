REM This script drops Information Source tables.
REM Arguments: <database name> <login> <password> <server>

isql -S %4 -E -U%2 -P%3 -d %1 < dropinfosrctables.sql




