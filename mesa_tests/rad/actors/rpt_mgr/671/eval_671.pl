#!/usr/local/bin/perl -w

use Env;

use lib "scripts";
require rpt_mgr;

sub goodbye() {
  exit 1;
}

# Search for all SR objects that match on accession number

sub find_candidate_files {
  my $tag = shift(@_);
  my $val = shift(@_);
  print LOG "Report Manager 671\n";
  print LOG " Tag = $tag, val = $val \n";

 @srFiles = rpt_mgr::find_matching_composite_objs ($verbose, $tag, $val);

 $s = scalar(@srFiles);
 print LOG "Matching SR files: $s\n";
 if ($s == 0) {
  print "No files found in MESA Report Repository that match $tag $val \n";
  print LOG "No files found in MESA Report Repository that match $tag $val \n";
 }

 print LOG "\n";
}

sub evaluate_candidate_files {
  $rtnValueEval = 1;
  $rtnValueCompare = 1;

  foreach $f (@srFiles) {
    print LOG "\nEvaluating $f\n";
    $x = "$MESA_TARGET/bin/mesa_sr_eval ";
    $x .= " -v " if $verbose;
    $x .= " -p ../../msgs/sr/611/sr_611_final.dcm -t 2000:DCMR $f";

    print LOG "$x \n";
    print LOG `$x`;
    if ($? == 0) {
      $rtnValueEval = 0;
    } else {
      print LOG "SR object $f does not pass SR evaluation.\n";
    }

    $x = "$MESA_TARGET/bin/compare_dcm -m 671/sr_671.ini";
    $x .= " -o " if $verbose;
    $x .= " ../../msgs/sr/611/sr_611_final.dcm $f";
    print LOG "$x \n";
    print LOG `$x`;
    if ($? == 0) {
      $rtnValueCompare = 0;
    } else {
      print LOG "SR object $f does not pass SR compare test.\n";
    }

    print LOG "\n";

  }

  $diff += $rtnValueEval + $rtnValueCompare;
}


$verbose = grep /^-v/, @ARGV;

open LOG, ">671/grade_671.txt" or die "?!";
$diff = 0;

find_candidate_files("0008 0050", "2001C611");
evaluate_candidate_files;

print LOG "\nTotal Differences: $diff \n";
print "\nTotal Differences: $diff \n";

print "Logs stored in 671/grade_671.txt \n";

exit $diff;
