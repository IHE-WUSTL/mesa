#!/usr/local/bin/perl -w
use Env;
use File::Copy;
use lib "../../common";
require mesa_msgs;

# Generate HL7 Order messages for Case 103
# This directory is for order messages and does not
# include scheduling messages.

  if (scalar(@ARGV) == 0) {
    copy("103.104.o01.var", "103.104.o01.xxx");
  } else {
  }


  mesa_msgs::create_text_file_2_var_files(
	"103.104.o01.txt",		# This is the output
	"../templates/o01.tpl",		# Template for an O01 message
	"../../adt/103/doej1.txt",	# Demographics, PV1 information
	"103.104.o01.xxx");		# Input with order information
  mesa_msgs::create_hl7("103.104.o01");
