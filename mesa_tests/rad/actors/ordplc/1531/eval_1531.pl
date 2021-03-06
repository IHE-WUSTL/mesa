#!/usr/local/bin/perl -w

use Env;
use lib "scripts";
require ordplc;

sub x_1531_1 {
  print LOG "CTX: Order Placer 1531.1\n";
  $diff += mesa::evaluate_hl7(
		$logLevel,
		$verbose,
		"../../msgs/order/131", "131.104.o01.hl7",
		"$MESA_STORAGE/ordfil", "1002.hl7",
		"ini_files/orm_o01_format.ini", "ini_files/orm_o01_compare.ini");
  print LOG "\n";
}

### Main starts here

die "Usage: <log level: 1-4>" if (scalar(@ARGV) < 1);
$logLevel = $ARGV[0];

open LOG, ">1531/grade_1531.txt" or die "Could not open output file: 1531/grade_1531.txt";
my $mesaVersion = mesa::getMESAVersion();
print LOG "CTX: $mesaVersion \n";
$diff = 0;
$verbose = 0;

x_1531_1;

print LOG "\nTotal Differences: $diff \n";
print "\nTotal Differences: $diff \n";
print "Logs stored in 1531/grade_1531.txt \n";

exit $diff;
