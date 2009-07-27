#!/usr/local/bin/perl -w

# Runs the Image Manager exam interactively.

use Env;
use lib "scripts";
require ordfil;

$SIG{INT} = \&goodbye;


sub goodbye () {
  print "Exiting...\n";

  exit 1;
}

sub send_CFIND_X102_3DRECON {
  if ($MESA_OS eq "WINDOWS_NT") {
    $resultsDir = "1421\\gpsps_x102";
    $resultsDirMESA = "1421\\gpsps_x102_mesa";
  } else {
    $resultsDir = "1421/gpsps_x102";
    $resultsDirMESA = "1421/gpsps_x102_mesa";
  }

  ordfil::delete_directory($resultsDir);
  ordfil::delete_directory($resultsDirMESA);

  ordfil::create_directory($resultsDir);
  ordfil::create_directory($resultsDirMESA);

#  $x = "$MESA_TARGET/bin/dcm_create_object " .
#       " -i ../../msgs/ppm/142x/gpspsquery_delaware.txt" .
#       " ../../msgs/ppm/142x/gpspsquery_delaware.dcm";
#  if( $MESA_OS eq "WINDOWS_NT") {
#     $x =~ s(/)(\\)g;
#  }
#  print "$x\n";
#  # print `$x`;
#  `$x`;

  $x = "$MESA_TARGET/bin/cfind -a MODALITY1 -c $test_ppmAE" .
       " -f ../../msgs/ppm/142x/gpspsquery_delaware.dcm -o $resultsDir" .
       " -x GPWL $test_ppmHost $test_ppmPort";
  if( $MESA_OS eq "WINDOWS_NT") {
     $x =~ s(/)(\\)g;
  }
   print "$x\n";
   print `$x`;

  $x = "$MESA_TARGET/bin/cfind -a MODALITY1 " .
       " -f ../../msgs/ppm/142x/gpspsquery_delaware.dcm -o $resultsDirMESA" .
       " -x GPWL $mesa_ppmHost $mesa_ppmPort";
  if( $MESA_OS eq "WINDOWS_NT") {
     $x =~ s(/)(\\)g;
  }
   print "$x\n";
   print `$x`;

}

sub send_CFIND_again {
  if ($MESA_OS eq "WINDOWS_NT") {
    $resultsDir = "1421\\gpsps_x102_2";
  } else {
    $resultsDir = "1421/gpsps_x102_2";
  }

  ordfil::delete_directory($resultsDir);
  ordfil::delete_directory($resultsDirMESA);

  ordfil::create_directory($resultsDir);
  ordfil::create_directory($resultsDirMESA);

  $x = "$MESA_TARGET/bin/cfind -a MODALITY1 -c $test_ppmAE" .
       " -f ../../msgs/ppm/142x/gpspsquery_delaware.dcm -o $resultsDir" .
       " -x GPWL $test_ppmHost $test_ppmPort";
  if( $MESA_OS eq "WINDOWS_NT") {
     $x =~ s(/)(\\)g;
  }
   print "$x\n";
   print `$x`;

}

sub send_firstclaim {
  my $test_sopuid = shift(@_);
  my $mesa_sopuid = shift(@_);
  my $resultsDir = shift(@_);

  if ($MESA_OS eq "WINDOWS_NT") {
    $outfile = "$resultsDir\\claim1response.txt";
  } else {
    $outfile = "$resultsDir/claim1response.txt";
  }

  open OUTPUT, ">$outfile" or die "could not open file $outfile";

#  $x = "$MESA_TARGET/bin/dcm_create_object " .
#       "-i ../../msgs/ppm/142x/spsclaim.txt" .
#       " ../../msgs/ppm/142x/spsclaim.dcm";
#  if( $MESA_OS eq "WINDOWS_NT") {
#     $x =~ s(/)(\\)g;
#  }
#  print "$x\n";
#  # print `$x`;

  $x = "$MESA_TARGET/bin/naction -a CT_3DRECON1 -c $test_ppmAE" .
       " $test_ppmHost $test_ppmPort GPSPS " .
       " ../../msgs/ppm/142x/spsclaim.dcm $test_sopuid";
  if( $MESA_OS eq "WINDOWS_NT") {
     $x =~ s(/)(\\)g;
  }
  print "$x\n";
  # print `$x`;
  print OUTPUT `$x`;

#  $x = "$MESA_TARGET/bin/naction -a CT_3DRECON1 " .
#       " $mesa_ppmHost $mesa_ppmPort GPSPS " .
#       " ../../msgs/ppm/142x/spsclaim.dcm $mesa_sopuid";
#  if( $MESA_OS eq "WINDOWS_NT") {
#     $x =~ s(/)(\\)g;
#  }
#   print "$x\n";
#   print `$x`;

  close OUTPUT;
}

sub send_secondclaim {
  my $test_sopuid = shift(@_);
  my $mesa_sopuid = shift(@_);
  my $resultsDir = shift(@_);

  if ($MESA_OS eq "WINDOWS_NT") {
    $outfile = "$resultsDir\\claim2response.txt";
  } else {
    $outfile = "$resultsDir/claim2response.txt";
  }

  open OUTPUT, ">$outfile" or die "could not open file $outfile";

  $x = "$MESA_TARGET/bin/naction -a CT_3DRECON1 -c $test_ppmAE" .
       " $test_ppmHost $test_ppmPort GPSPS " .
       " ../../msgs/ppm/142x/spsclaim.dcm $test_sopuid";
  if( $MESA_OS eq "WINDOWS_NT") {
     $x =~ s(/)(\\)g;
  }
   print "$x\n";
   # print `$x`;
   print OUTPUT `$x`;

#  $x = "$MESA_TARGET/bin/naction -a CT_3DRECON1 " .
#       " $mesa_ppmHost $mesa_ppmPort GPSPS " .
#       " ../../msgs/ppm/142x/spsclaim.dcm $mesa_sopuid";
#  if( $MESA_OS eq "WINDOWS_NT") {
#     $x =~ s(/)(\\)g;
#  }
#   print "$x\n";
#   print `$x`;

  close OUTPUT;
}

# End of subroutines, beginning of the main code

#Setup commands
$host = `hostname`; chomp $host;


# ($mesaOFPortDICOM, $mesaOFPortHL7, $mesaImgMgrPortDICOM, $mesaImgMgrPortHL7,
#  $mesaModPortDICOM,
#  $mppsHost, $mppsPort, $mppsAE,
#  $imCStoreHost, $imCStorePort, $imCStoreAE,
#  $imCFindHost, $imCFindPort, $imCFindAE,
#  $imCommitHost, $imCommitPort, $imCommitAE,
#  $imHL7Host, $imHL7Port
# ) = ordfil::read_config_params("ordfil_test.cfg");

( $mesa_ppmHost, $mesa_ppmPort, $mesa_ppmAE,
  $test_ppmHost, $test_ppmPort, $test_ppmAE,
) = ordfil::read_ppm_config_params("ordfil_test.cfg");

# die "Illegal MESA Image Mgr HL7 Port: $mesaImgMgrPortHL7 \n" if ($mesaImgMgrPortHL7 == 0);


# announce test

print "\n" .
  "This is MESA Image Manager test 1421.  It tests post-processing\n" .
  "transactions for patient DELAWARE generated by script 142x.\n" .
  "This tests a post-processing manager's response to a double claim.\n\n";

# Post-processing workstation queries test and MESA PPMs for its worklist.

print "\n" .
  "The MESA CAD station will send a C-Find to query for its worklist.\n" .
  "The current workitem code is: X102_3DRECON \n" .
  "Press <enter> when ready to continue or <q> to quit: ";
$response = <STDIN>;
goodbye if ($response =~ /^q/);

send_CFIND_X102_3DRECON;

$mesa_spsSOPUID = ordfil::getSOPUID("1421/gpsps_x102_mesa/msg1_result.dcm");
chomp $mesa_spsSOPUID;
print "mesa_spsSOPUID: " . $mesa_spsSOPUID . "\n";

$test_spsSOPUID = ordfil::getSOPUID("1421/gpsps_x102/msg1_result.dcm");
chomp $test_spsSOPUID;
print "test_spsSOPUID: " . $test_spsSOPUID . "\n";


# claim the workitem.

print "\n" .
  "The MESA CAD station will send a GPSPS NACTION to claim the scheduled \n" .
  "procedure step.\n" .
  "Press <enter> when ready to continue or <q> to quit: ";
$response = <STDIN>;
goodbye if ($response =~ /^q/);

if ($MESA_OS eq "WINDOWS_NT") {
  $claimResultsDir = "1421\\results";
} else {
  $claimResultsDir = "1421/results";
}

ordfil::delete_directory($claimResultsDir);
ordfil::create_directory($claimResultsDir);

send_firstclaim($test_spsSOPUID, $mesa_spsSOPUID, $claimResultsDir);

print "\n" .
  "The MESA CAD station will send a second C-Find to query for its worklist.\n" .
  "The status should now be \"IN PROGRESS\"\n" .
  "Press <enter> when ready to continue or <q> to quit: ";
$response = <STDIN>;
goodbye if ($response =~ /^q/);

send_CFIND_again;

# attempt to claim the workitem again.

print "\n" .
  "The MESA CAD station will send a GPSPS NACTION to attempt to claim \n" .
  "the scheduled procedure step again.\n" .
  "Press <enter> when ready to continue or <q> to quit: ";
$response = <STDIN>;
goodbye if ($response =~ /^q/);

send_secondclaim($test_spsSOPUID, $mesa_spsSOPUID, $claimResultsDir);

print "\n" .
  "The Image Manager test 1421 is complete.  To evaluate \n" .
  "your responses:  \n" .
  "   perl 1421/eval_1421.pl [-v] \n";

goodbye;
