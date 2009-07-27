#!/usr/local/bin/perl -w

use Env;

use lib "../../../rad/actors/common/scripts";
use lib "../../../common/scripts";
require evaluate_tfcte;
require mesa;
require mesa_common;
require mesa_evaluate;

sub goodbye() {
  exit 1;
}

sub dummy {}

die "Usage <log level: 1-4> " if (scalar(@ARGV) < 1);

$logLevel     = $ARGV[0];

open LOG, ">3003/grade_3003.txt" or die "Could not open output file: 3003/grade_3003.txt";
my $version = mesa_get::getMESANumericVersion();
my $numericVersion = mesa_get::getMESANumericVersion();
($x, $date, $timeMin, $timeToSec) = mesa_get::getDateTime(0);
dummy($x); dummy($timeMin); dummy($timeToSec);

print LOG "CTX: Test:    3003\n";
print LOG "CTX: Actor:   EXPORT_SELECTOR\n";
print LOG "CTX: Version: $numericVersion\n";
print LOG "CTX: Date:    $date\n";

$diff = 0;

#expmgr
# Search the database for the set of composite objects sent to MESA Export Manager by Test Export Slector.
($status, @filnam) = mesa::db_table_retrieval($logLevel,"expmgr", "sopins", "filnam");
dummy($status);
my $z1 = @filnam;
print LOG "CTX: During test 3003, the Test Export Selector has sent $z1 SOP instances.\n";

# define global varibles
$studyTag = "0020 000d";
$seriesTag = "0020 000e";
$instanceTag = "0008 0018";
$classUID = "1.2.840.10008.5.1.4.1.1.88.59";
dummy($studyTag, $seriesTag,$instanceTag,$classUID);

# Get the list of KON objects generated by Export Selector
@mgr_kons = evaluate_tfcte::getKON($logLevel,$classUID, @filnam);

# Seperate KON with Delay Modifier from the other 2 KONs
($delayKON, $identicalSeqKONs) = evaluate_tfcte::groupKONs(@mgr_kons);

# Get the list of Image Objects sent to MESA Export Manager.
@mgr_imgs = evaluate_tfcte::getIMG($logLevel, $classUID, @filnam);
#displayList("mgr_imgs",@mgr_imgs) if($logLevel >= 3);

print LOG "\n";
my $testNum = 1;

my $expectedValue = 3;
$diff += evaluate_tfcte::check_KON_number($logLevel,"Export Selector 3003.$testNum", $expectedValue, @mgr_kons);
$testNum++;

$diff += evaluate_tfcte::eval_KON_structure($logLevel,"Export Selector 3003.$testNum", @mgr_kons);
$testNum++;

$diff += evaluate_tfcte::eval_KON_attributes($logLevel,"Export Selector 3003.$testNum", "Testing KON Attribute - Title", "Title", @mgr_kons);
$testNum++;

#$diff += evaluate_tfcte::eval_IMG_Referenced_By_KON($logLevel,"Export Selector 3003.$testNum", $mgr_kons[0], \@mgr_imgs, 2);
$diff += evaluate_tfcte::eval_IMG_Referenced_By_KON($logLevel,"Export Selector 3003.$testNum", $mgr_kons[1], \@mgr_imgs, 2);
$diff += evaluate_tfcte::eval_IMG_Referenced_By_KON($logLevel,"Export Selector 3003.$testNum", $mgr_kons[2], \@mgr_imgs, 2);
$testNum++;

# Test content sequence images are the same for 2 kons
my %rcr_kon1_con_seq_imgs = evaluate_tfcte::getContentSeqImages($logLevel, $$identicalSeqKONs[0]);
my %rcr_kon2_con_seq_imgs = evaluate_tfcte::getContentSeqImages($logLevel, $$identicalSeqKONs[1]);
my @rcr_kon1_con_seq_imgs = %rcr_kon1_con_seq_imgs;
my @rcr_kon2_con_seq_imgs = %rcr_kon2_con_seq_imgs;
$testNum++;
$diff += evaluate_tfcte::testArrayEqual($logLevel, "Export Selector 3003.$testNum", "Testing Content Sequence Images are identical for 2 KONs", \@rcr_kon1_con_seq_imgs, \@rcr_kon2_con_seq_imgs);

# Test Content Sequence images and Evidence Sequence images are the same.
my ($s1,%rcr_kon1_evd_seq_imgs) =  mesa::getKONInstanceManifest($logLevel, $$identicalSeqKONs[0], 2);
$diff += evaluate_tfcte::testHashEqual($logLevel, "Export Selector 3003.$testNum", "Testing Images are identical in Content Sequence Images and Current Requested Procedure Evidence Sequence for KON <$$identicalSeqKONs[0]>.", \%rcr_kon1_con_seq_imgs, \%rcr_kon1_evd_seq_imgs);
$testNum++;

my ($s2,%rcr_kon2_evd_seq_imgs) =  mesa::getKONInstanceManifest($logLevel, $$identicalSeqKONs[1], 2);
$diff += evaluate_tfcte::testHashEqual($logLevel, "Export Selector 3003.$testNum", "Testing Images are identical in Content Sequence Images and Current Requested Procedure Evidence Sequence for KON <$$identicalSeqKONs[1]>.", \%rcr_kon2_con_seq_imgs, \%rcr_kon2_evd_seq_imgs);
$testNum++;

# Test two kons are identical except Study uid, series uid, sop instance uid are different and identical document sequence refer to each other.
$diff += evaluate_tfcte::evalSyncronizedKONs($logLevel, "Export Selector 3003.$testNum", "Testing two KONs are syncronized.", $$identicalSeqKONs[0], $$identicalSeqKONs[1]);
$testNum++;

$diff += evaluate_tfcte::eval_KON_Desc($logLevel,"Export Selector 3003.$testNum", "Testing KON Attribute - Key Object Description", \@mgr_kons,);
$testNum++;

$diff += evaluate_tfcte::eval_KON_Title_Modifier($logLevel, "Export Selector 3003.$testNum", "Testing KON Attribute - Document Title Modifier", $$delayKON[0]);

if ($logLevel != 4) {
  $diff += 1;
  print LOG "ERR: Log level for submission should be 4, not $logLevel. For results submission, this is considered a failure. Please rerun at log level 4.\n";
}

close LOG;

mesa_evaluate::copyLogWithXML("3003/grade_3003.txt", "3003/mir_mesa_3003.xml",
        $logLevel, "3003", "EXPORT_SELECTOR", $numericVersion, $date, $diff);

if ($diff == 0) {
  print "\nThis test completed with zero errors; that means successful test\n";
} else {
  print "Test detected $diff errors; this implies a failure\n";
  print " Please consult 3003/grade_3003.txt and 3003/mir_mesa_3003.xml\n";
}

print "If you are submitting a result file to Kudu, submit 3003/mir_mesa_3003.xml\n\n";

