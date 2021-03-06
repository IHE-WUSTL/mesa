#!/usr/local/bin/perl
#
# Create the Post Processing tables in the specified database.
#

use Env;

$x = scalar(@ARGV);
if ($x == 0) {
  print "Usage: <Database Name> \n";
  exit 1;
}

$databaseName = $ARGV[0];

@scriptNames = ("createppwf.sql");

foreach $sc (@scriptNames) {
  print "psql $databaseName < $sc \n";
  print `psql $databaseName < $sc`;

  if ($?) {
    print "Could not clear Post Processing Work Flow tables ($databaseName $sc) \n";
    exit 1;
  }
}

