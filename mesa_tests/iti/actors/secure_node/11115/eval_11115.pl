#!/usr/local/bin/perl -w

# Script evaluates test 11115.
# This is the test for generating an audit STARTUP message.

use Env;

#use lib "scripts";
use lib "../../../common/scripts";
#require secure;
require mesa_common;
require mesa_evaluate;

sub goodbye() {
  exit 1;
}

if (scalar(@ARGV) != 2) {
  die "Usage: <output level> <schema: INTERIM or IETF>";
  exit 1;
}
$outputLevel = $ARGV[0];
$testType = $ARGV[1];

open LOG, ">11115/grade_11115.txt" or die "Could not create grade file: 11115/grade_11115.txt";
$diff = 0;
my $mesaVersion = mesa_get::getMESAVersion();
print LOG "CTX: $mesaVersion \n";


print LOG "CTX: Secure Node test 11115\n";
print LOG "CTX: Test type: $testType\n";

if (! -e "$MESA_TARGET/logs/syslog/last_log.xml") {
  print LOG "ERR: $MESA_TARGET/logs/syslog/last_log.xml does not exist\n";
  print LOG "ERR: That means the MESA syslog server did not receiver your audit message.\n";
  print LOG "ERR: Please check: syslog server running? syslog server files for clues.\n";

  print "ERR: $MESA_TARGET/logs/syslog/last_log.xml does not exist\n";
  print "ERR: That means the MESA syslog server did not receiver your audit message.\n";
  print "ERR: Please check: syslog server running? syslog server files for clues.\n";
  exit 1;
}

if ($testType eq "INTERIM") {
  $diff += mesa_evaluate::validate_xml_schema($outputLevel, "$MESA_TARGET/runtime/IHE-syslog-audit-message-4.xsd", "$MESA_TARGET/logs/syslog/last_log.xml");
} elsif ($testType eq "IETF") {
  $diff += mesa_evaluate::validate_xml_schema($outputLevel, "$MESA_TARGET/runtime/IHE-ATNA-syslog-audit-message.xsd", "$MESA_TARGET/logs/syslog/last_log.xml");
} else {
  print LOG "ERR: Unrecognized test type: $testType\n";
  print LOG "ERR: Should be INTERIM or IETF\n";
  print "ERR: Test type should be INTERIM or IETF. Please insert another quarter.\n";
  $diff = 1;
}

print LOG "\nTotal Differences: $diff \n";
print "\nTotal Differences: $diff \n";

print "Logs stored in 11115/grade_11115.txt \n";

exit $diff;
