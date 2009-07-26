#!/bin/csh
#
# CreateSyslogTables
#
if ($1 == "") then
  echo " "
  echo Usage: "$0 <Database Name>"
  echo " "
  exit 1
endif


psql $1 < createsyslogentry.sql
if ($status != 0) exit 1

