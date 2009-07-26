<?php
    require "global.inc";
    require "common_functions.inc";
    $nativedb = "webop";
    $source = $_GET["source"];
    $printSource = $actor{$source};
    $actorLink = $actor_link{$source};
    $successLink = $create_order_link{$source};
    $title = "<a href=\"index.php\">MESA RIS Mall</a>:: <a href=\"$actorLink\">$printSource</a>:: Create an Order";
    $title_no_link = "MESA RIS Mall:: ". $printSource . " :: Create an Order";
    $header = "MESA RIS Mall";
	
	if (!empty($_POST["cancel"])) {
        header("Location:$actorLink");
    }
    check_user_is_logged_in();
	global $visitList;
?>

<html>
<head>
  <title><?=$title_no_link?></title>
  <link href="include/general.css" type="text/css" rel="Stylesheet" rev="Stylesheet" media="all">
</head>
<body>

<?php
    print_header($header);
# process_form tells us later if this form is ready to be processed.
# first confirm all the info is here.
    $process_form = false;
	$visitList = getVisitList($_POST["viskey"], $nativedb);
    $submit = $_POST["submit"];
    if ($submit == "Create") {
        //if (empty($viskey)) {
        if (empty($_POST["viskey"])) {
            print_user_error("Please select visit."); 
        } else {
            $process_form = true;
        }
    }
	
    if ($submit == "Search Patients") {
        $lName = $_POST["last_name"];
        if (empty($lName)) {
            print_user_error("Please enter few letters from Patient's last name.");
        } else {
            $lName = strtoupper($lName);
            list ($rows, $visitList) = getVisitListByLname($lName, $_POST["viskey"], $nativedb);
            if ($rows == 0) {
                print_user_error($visitList);
                $visitList = getVisitList($_POST["viskey"], $nativedb);
            }
        }
    }

// Constants -- needed for DB as well as for form
    $quatim = "1^once^^^^S";
    $entby = "^ROSEWOOD^RANDOLPH";
    $entorg = "922229-10^IHE-RAD^IHE-CODE-231";
    $ordcalphonum = "314-555-1212";

    if ($submit == "Create" && $process_form == "true") {
        $verbose = $_POST["verbose"];

        $viskey = rtrim($_POST["viskey"]);
        $patient_visit = get_patient_visit_by_viskey($viskey, $nativedb);

        $cmd = "$mesaTarget/bin/mesa_identifier webop pon 2>&1";
        $plaordnum = execute_piped_command($cmd, $verbose, true);
        $plaordnum = rtrim($plaordnum);

        $filordnum = "";
        $uniserid = rtrim($_POST["uniserid"]);
        $visnum = rtrim($patient_visit["visnum"]);

        // orduid is generated by db upon insert
        $ordcon = "NW";
        $plagronum = "";
        $ordsta = "";
        $messta = "REQUESTED";
        $par = "";
        $dattimtra = rtrim($_POST["dattimtra"]);
        $ordpro = rtrim($_POST["ordpro"]);
        $refdoc = $patient_visit["refdoc"];
        $ordeffdattim = $dattimtra;
        $spesou = rtrim($_POST["spesou"]);
        $traarrres = "";
        $reaforstu = rtrim($_POST["reaforstu"]);
        $obsval = "";
        $dancod = rtrim($_POST["dancod"]);
        $relcliinf = rtrim($_POST["relcliinf"]);

        $query = "INSERT INTO ordr " .
            "(plaordnum, filordnum, uniserid, visnum, ordcon, plagronum, " . 
            "ordsta, messta, quatim, par, dattimtra, entby, ordpro, refdoc, " .
            "ordeffdattim, entorg, spesou, ordcalphonum, traarrres, " .
            "reaforstu, obsval, dancod, relcliinf) VALUES " .    
            "('$plaordnum', '$filordnum', '$uniserid', '$visnum', '$ordcon', " .
            "'$plagronum', '$ordsta', '$messta', '$quatim', '$par', " .
            "'$dattimtra', '$entby', '$ordpro', '$refdoc', '$ordeffdattim', " .
            "'$entorg', '$spesou', '$ordcalphonum', '$traarrres', " .
            "'$reaforstu', '$obsval', '$dancod', '$relcliinf')";


        if ($_POST["verbose"]) {
            echo "<pre>SQL Query:\n";
            echo "$query\n</pre>";
        }

        $db_connection = connectDB($nativedb);
        pg_exec($db_connection, $query) or 
            die("Error in query: $query" . pg_errormessage($db_connection));
        $orduid = getCurrentOrderUID($db_connection);

        logCreateOrder($orduid, $nativedb, true);
        pg_close($db_connection);
	
		//$link = "Click <a href=\"$actorLink?source=$source\">here</a> to go back to $printSource test control page.";
        #print_success_message($title, "Successfully Created Order Record", $successLink);
		echo "<script>document.location.href='send_order.php?source=acqmod'</script>";
    } else {

?>

<form action="<?php $PHP_SELF;?>" method="post">
<table width="820" bgcolor="FFF8CE" border="0" cellspacing="2" cellpadding="2">
		<tr>
            <td bgcolor="#FFD557" colspan="3">
            <?php print_top_nav($title); ?>
            </td>
        </tr>
		<tr>
            <td colspan="3"><b><u>Search for Patients:</u></b></td>
        </tr>
        <tr>
            <td align="left">Patient's lastname begins with </td>
            <td width="5">&nbsp;</td>
            <td align=left><input type=text name="last_name" value="<?=$_POST["last_name"]?>">  </td>
        </tr>
        <tr>
            <td align="left">&nbsp;</td>
            <td width="5">&nbsp;</td>
            <td align=left><input type="submit" name="submit" value="Search Patients"></td>
        </tr>
        <tr>
            <td colspan="3">&nbsp;</td>
        </tr>
        <tr>
            <td align="left" valign="top">Please select visit record</td>
			<td width="5">&nbsp;</td>
            <td align=left>
            <?= $visitList ?>
			</td>
        <tr>
            <td align="left">Placer Order Number</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>Automatically Assigned</b></td>
        <tr>
            <td align="left">Filler Order Number</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>&quot &quot</b></td>
        <tr>
            <td align="left">Universal Service ID</td>
			<td width="5">&nbsp;</td>
            <td align=left><select name="uniserid"> 
                <?php  
                    $fn = "../config/uniserid.txt";
                    configFileOptions($fn, $_POST["uniserid"]);
                ?>
            </select>  
			</td>
        <tr>
            <td align="left">Visit Number</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>From Selected Visit</b></td>
        <tr>
            <td align="left">Order UID</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>Automatically Assigned</b></td>
        <tr>
            <td align="left">Order Control</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>NW</b></td>
        <tr>
            <td align="left">Placer Group Number</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>&quot &quot</b></td>
        <tr>
            <td align="left">Order Status</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>&quot &quot</b></td>
        <tr>
            <td align="left">MESA Status</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>REQUESTED</b></td>
        <tr>
            <td align="left">Quantity/Timing</td>
			<td width="5">&nbsp;</td>
            <td align=left><b><?=$quatim?></b></td>
        <tr>
            <td align="left">Parent</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>&quot &quot</b></td>
        <tr>
            <td align="left">Date/Time of Transaction</td>
			<td width="5">&nbsp;</td>
            <td align=left><b><?php echo 
                    $dattimtra = `perl ../bin/getMesaInfo.pl datetime`?></b>
            <!-- Post values of dattimtra secretly -->
            <input type="hidden" name="dattimtra" value="<?=$dattimtra?>">
			</td>
        <tr>
            <td align="left">Entered By</td>
			<td width="5">&nbsp;</td>
            <td align=left><b><?=$entby?></b></td>
        <tr>
            <td align="left">Ordering Provider</td>
			<td width="5">&nbsp;</td>
            <td align=left><select name="ordpro"> 
                <?php  
                    $fn = "../config/ordpro.txt";
                    configFileOptions($fn, $_POST["ordpro"]);
                ?>
            </select>  
			</td>
        <tr>
            <td align="left">Referring Doctor</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>From Selected Visit</b></td>
        <tr>
            <td align="left">Order Effective Date/Time</td>
			<td width="5">&nbsp;</td>
            <!-- same as Date/Time of Transacton -->
            <td align=left><b><?=$dattimtra ?></b></td>
        <tr>
            <td align="left">Entering Organization</td>
			<td width="5">&nbsp;</td>
            <td align=left><b><?=$entorg?></b></td>
        <tr>
            <td align="left">Specimen Source</td>
			<td width="5">&nbsp;</td>
            <td align=left><select name="spesou">
                <?php  
                    $fn = "../config/spesou.txt";
                    configFileOptions($fn, $_POST["spesou"]);
                ?>
                </select>
			</td>
        <tr>
            <td align="left">Order Callback Phone Number</td>
			<td width="5">&nbsp;</td>
            <td align=left><b><?=$ordcalphonum?></b></td>
        <tr>
            <td align="left" valign="top">Transport Arrangement <br>Responsibility</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>&quot &quot</b></td>
        <tr>
            <td align="left">Reason for Study</td>
			<td width="5">&nbsp;</td>
            <td align=left><input type=text name="reaforstu" 
                value="<?=$_POST["reaforstu"]?>"></td>
        <tr>
            <td align="left">Observation Value</td>
			<td width="5">&nbsp;</td>
            <td align=left><b>&quot &quot</b></td>
        <tr>
            <td align="left">Danger Code</td>
			<td width="5">&nbsp;</td>
            <td align=left><select name="dancod">
                <?php  
                    $fn = "../config/dancod.txt";
                    configFileOptions($fn, $_POST["dancod"]);
                ?>
                </select>
			</td>
        <tr>
            <td align="left">Relevant Clinical Info
			<td width="5">&nbsp;</td>
            <td align=left><input type=text name="relcliinf" 
                value="<?=$_POST["relcliinf"]?>"></td>
        <tr>
            <td align="left">Debugging Output</td>
			<td width="5">&nbsp;</td>
            <td align=left><input type="checkbox" name="verbose" value="verbose"
                <?=$_POST["verbose"] ? "checked" : "" ?>></td>
		<tr>
            <td colspan="3" align=center>
			<input type="submit" name="cancel" value="Cancel">&nbsp;&nbsp;&nbsp;<input type="reset" value="Reset">&nbsp;&nbsp;&nbsp;<input type=submit name="submit" value="Create">
			</td>
		</tr>
		<tr>
			<td colspan=3 align=center>
			&nbsp;
			</td>
		</tr>
</table>
</form>
	<?php } ?>

<? include "footer.inc" ?>

</body>
</html>
