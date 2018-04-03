create view reportview as
  select patient.patid, patient.issuer, patient.nam, patient.datbir,
	patient.sex,   patient.patrac,
	reports.rpttype, reports.rpttxt, reports.rptdatetime,
	reports.rptxml, reports.rptpath
  from patient, reports
  where patient.patid = reports.patid and
	patient.issuer = reports.issuer;

