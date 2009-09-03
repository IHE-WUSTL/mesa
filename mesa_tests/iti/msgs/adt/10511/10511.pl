#!/usr/local/bin/perl -w

use Env;
use File::Copy;
use lib "../../common";
require mesa_msgs;


# Generate HL7 messages for Case 10512

if (scalar(@ARGV) == 0) {
  copy("alpha_domain1.var",   "alpha_domain1.txt");
  copy("alpha_domain2.var",   "alpha_domain2.txt");
  copy("simpson_domain1.var", "simpson_domain1.txt");
} else {
# The files would have been produced externally
#  alpha_domain1.txt
#  alpha_domain2.txt
#  simpson_domain1.txt
}

  mesa_msgs::create_text_file_2_var_files (
	"10511.102.a01.txt",	# The output file
	"../templates/a01_iti8.tpl",	# Template for an A04: ITI-8
	"alpha_domain1.txt",	# PID, PV1 data
	"10511.102.a01.var"	# A04 variables not in PID, PV1
  );
  mesa_msgs::create_hl7("10511.102.a01");

  mesa_msgs::create_text_file_2_var_files (
	"10511.104.a01.txt",	# The output file
	"../templates/a01_iti8.tpl",	# Template for an A04: ITI-8
	"simpson_domain1.txt",	# PID, PV1 data
	"10511.104.a01.var"	# A04 variables not in PID, PV1
  );
  mesa_msgs::create_hl7("10511.104.a01");

  mesa_msgs::create_text_file_2_var_files (
	"10511.106.a01.txt",	# The output file
	"../templates/a01_iti8.tpl",	# Template for an A04: ITI-8
	"alpha_domain2.txt",	# PID, PV1 data
	"10511.106.a01.var"	# A04 variables not in PID, PV1
  );
  mesa_msgs::create_hl7("10511.106.a01");