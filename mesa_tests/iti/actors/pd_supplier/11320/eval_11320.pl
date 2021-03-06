#!/usr/local/bin/perl -w

# This script evaluates RSP^K22 messages sent by a
# PD Supplier for test 11320.

use Env;
use lib "scripts";
use lib "../../../common/scripts";
require pd_supplier;
require mesa_common;
require mesa_evaluate;

sub dummy {}

#sub x_11320_1 {
#  print LOG "CTX: PD Supplier 11320.1\n";
#  print LOG "CTX: Evaluate RSP K22 response to query 11320.\n";
#  print LOG "CTX: Evaluate ACK message.\n";
#  $diff += mesa::evaluate_PDQ_ACK (
#	$logLevel,
#	"11320/mesa/1000.hl7",
#	"11320/test/1000.hl7");
#  print LOG "\n";
#}

sub x_11320_2 {
  print LOG "CTX: PD Supplier 11320.2\n";
  print LOG "CTX: Evaluate RSP K22 response to query 11320.\n";
  print LOG "CTX: Evaluate baseline response.\n";
  $diff += mesa::evaluate_PDQ_RSP_K22_baseline(
	$logLevel,
	"11320/mesa/1000.hl7",
	"11320/test/1000.hl7");
  print LOG "\n";
}


### Main starts here

# Compare input RSP K22 messages with expected values.
die "Usage: perl 11320/eval_11320.pl <log level (1-4)>\n" if (scalar(@ARGV) < 1);
$logLevel = $ARGV[0];

open LOG, ">11320/grade_11320.txt" or die "Cout not open output file 11320/grade_11320.txt";
my $version = mesa_get::getMESANumericVersion();
my $numericVersion = mesa_get::getMESANumericVersion();
($x, $date, $timeMin, $timeToSec) = mesa_get::getDateTime(0);
dummy($x); dummy($timeMin); dummy($timeToSec);

print LOG "CTX: Test:    11320\n";
print LOG "CTX: Actor:   PDS\n";
print LOG "CTX: Version: $numericVersion\n";
print LOG "CTX: Date:    $date\n";

$diff = 0;

#x_11320_1;
x_11320_2;

if ($logLevel != 4) {
  $diff += 1;
  print LOG "ERR: Log level for submission should be 4, not $logLevel. For results submission, this is considered a failure. Please rerun at log level 4.\n";
}

close LOG;

mesa_evaluate::copyLogWithXML("11320/grade_11320.txt", "11320/mir_mesa_11320.xml",
        $logLevel, "11320", "PDS", $numericVersion, $date, $diff);

if ($diff == 0) {
  print "\nThis test completed with zero errors; that means successful test\n";
} else {
  print "Test detected $diff errors; this implies a failure\n";
  print " Please consult 11320/grade_11320.txt and 11320/mir_mesa_11320.xml\n";
}

print "If you are submitting a result file to Kudu, submit 11320/mir_mesa_11320.xml\n\n";

