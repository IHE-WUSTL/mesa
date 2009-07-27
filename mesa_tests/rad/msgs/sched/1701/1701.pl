#!/usr/local/bin/perl -w

use Env;
use File::Copy;
use lib "../../common";
require mesa_msgs;

# Generate HL7 messages for Case 1701
my $base = "1701.106.o01";

if (scalar(@ARGV) == 0) {
  copy("$base.var", "$base.xxx");
} else {
# This was done by an external program.
}

mesa_msgs::create_text_file_2_var_files("$base.txt", "../templates/o01.tpl",
	"../../adt/1701/black.txt", "$base.xxx");
mesa_msgs::create_hl7($base);
