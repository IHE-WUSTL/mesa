	create table mwl (
        mwl_key     serial PRIMARY KEY,
		stuinsuid	varchar(64),
		refstusopcla	varchar(64),
		refstusopins	varchar(64),
		reqproid	varchar(30),
		plaordnum	varchar(22),
		filordnum	varchar(22),
		accnum		varchar(20),
		quatim		varchar(20),
		everea		varchar(20),
		reqdattim	varchar(20),
		spesou		varchar(20),
		ordpro		varchar(20),
		reqprodes	varchar(64),
		reqprocod	varchar(30),
		occnum		varchar(20),
		apptimqua	varchar(30),
		orduid		int REFERENCES ordr(orduid),
		spsid		varchar(16),
		spsindex	char(16),
		schaet		varchar(16),
		spsstadat	int,
		spsstatim	varchar(16),
		mod		varchar(16),
		schperphynam	varchar(64),
		spsdes		varchar(64),
		spsloc		varchar(16),
		premed		varchar(64),
		reqconage	varchar(64),
		schstanam	varchar(16),
		spssta		varchar(16),
		reqphynam	varchar(64),
		refphynam	varchar(64),
		patid		varchar(20),
		issuer		varchar(100),
		patid2		varchar(20),
		issuer2		varchar(100),
		nam		varchar(64),
		datbir		varchar(8),
		sex		varchar(4),
		pataccnum	varchar(20),
		patrac		varchar(20),
		codmea		varchar(64),
		codval 		varchar(20),
		codschdes       varchar(20),
		pregstat	varchar(4),
		curpatloc	varchar(64),
		admid		varchar(64),
		issueradmid	varchar(64)
	);

