#!/usr/local/bin/perl -w

# Self test script for Modality 50201 test.

use Env;
use lib "scripts";
require mod;

mod::cstore("50201/x1.dcm", "",
	"MESA_IMG_MGR", "localhost", "2350");

$x = "$MESA_TARGET/bin/ncreate -a MESA_MODALITY localhost 2350 mpps " .
     " 50201/mpps.crt " .
     " 1.113654.50201.1";
print "$x \n";
print `$x`;

$x = "$MESA_TARGET/bin/nset -a MESA_MODALITY localhost 2350 mpps " .
     " 50201/mpps.set " .
     " 1.113654.50201.1";
print "$x\n";
print `$x`;

