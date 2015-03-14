|<font color='red'><b><i>Note</i></b>: Due to lack of maintenance, this guide has been deprecated; please use the English version of the <a href='UserGuide.md'>user guide</a>.</font>|
|:------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

<a href='Hidden comment: 

<font color="red">
*WARNING*: This guide is at least one major version behind the latest official release, and thus may contain inaccuracies or outdated information.


Unknown end tag for &lt;/font&gt;



== Translation ==
Italian translation provided by [http://chdk.setepontos.com/index.php?topic=3290.msg63149#msg63149 ataru] updated and revised by Scrizza.

= MANUALE UTENTE 400D+ =

= Introduzione =

Questo documento contiene il manuale d"uso per 400D+. Si suppone che, prima di leggere questa guida, l"utente abbia installato 400D+ e che il software funzioni correttamente. Per informazioni sull"installazione di 400D+, vedere [http://code.google.com/p/400plus/wiki/InstallazioneHackFirmware Installazione Hack Firmware].

= Il menu delle impostazioni =

== Accesso al menu delle impostazioni ==

Per accedere al menu delle impostazioni di 400D+, premere il tasto MENU (verrà visualizzato il menu standard della fotocamera) e poi il tasto DP (Direct Print). Verrà visualizzato il menu delle impostazioni di 400D+. Per uscire dal menu delle impostazioni di 400D+, basta premere a metà corsa il pulsante di scatto.

*NOTA: Il tasto DP si trova sul retro della macchina, appena a sinistra del mirino (è un pulsante con un"icona blu di una stampante con una freccia curva vicino).*

== Navigazione nel menu delle impostazioni ==

Per navigare all"interno del menu delle impostazioni, utilizzare i tasti SU (ISO) e GIU" (WB) per spostarsi tra le voci. Quindi utilizzare il SINISTRA (MISURAZIONE) e DESTRA (AF) per cambiarne il valore (premere e tenere premuto questi tasti per cambiare più velocemente). Su alcune voci del menu, il tasto AV può essere utilizzato per cambiare (scorrere) i valori, o una parte di essi (come il segno + e -).

== Navigazione nel sotto-menu ==

I sotto-menu vengono visualizzati come "OGGETTO>OPZIONE"; utilizzare la rotellina frontale o i pulsanti ZOOM IN E ZOOM OUT per scorrere fino alla prossima o alla precedente voce secondaria, poi SINISTRA E DESTRA per modificare il valore (premere e tenere premuto per cambiare più velocemente) della voce selezionata. I tasti su e giù possono essere utilizzati in qualsiasi momento per passare da una voce all’altra.

== Le voci del menu ==

* _*Compensazione AV*_: la stessa funzione della "compensazione AV" standard, ma estende l"escursione tra -6 e +6 EV.
* _*Compensaz. Flash*_: la stessa funzione della "compensazione Flash" standard, ma estende l"escursione tra -6 e +6 EV.
* _*Disattiva  Flash*_: forza la disattivazione del flash, anche se il flash è stato alzato e attivato.
* _*Temp. Colore (K)*_: permette di impostare una temperatura di colore in gradi Kelvin definita dall"utente e attiva automaticamente il bilanciamento del bianco personalizzato.
* _*AEB_*: la stessa funzione della "AEB" standard, ma estende l"escursione tra -6 e +6 EV.
* _*Safety Shift*_: Quando è attivo (impostato su Si), e se in Tv (risp. Av), la fotocamera cambierà la velocità dell"otturatore (risp. apertura del diaframma) impostati dall"utente per evitare una sotto/sovraesposizione, se il valore è troppo piccolo/grande per la scena.
* _*Abilita com.IR_*: attiva sempre telecomando a raggi infrarossi. *<--NEW*
* _*Ritardo com.IR_*: seleziona se la telecamera debba scattare immediatamente oppure aspettare 2 secondi quando viene azionato da un telecomando a raggi infrarossi.
* _*ISO nel mirino*_: Quando è attivo (impostato su Si), e se in modalità P o Tv, è possibile utilizzare i pulsanti SINISTRA e DESTRA per modificare il valore ISO guardando attraverso il mirino.
* _*Accesso Diretto*_: Quando è attivo (impostato su Si), la pressione del tasto DIRECT PRINT nella finestra principale porterà al [#Menu_di_accesso_diretto menu di accesso diretto]; se impostato su "No", il tastoDP cambierà (scorrerà) il valore ISO tra i valori intermedi.
* _*AutoISO*_: Questoi sottomenu configura il comportamento dell"[#AutoISO AutoISO].
* Enabled: quando è attivo (impostato si Sì), l"AutoISO è abilitato.
* Min ISO: il minor valore ISO che verrà usato dall"AutoISO.
* Max ISO: il massimo valore ISO che verrà usato dall"AutoISO.
* Min Tv : il valore minimo di velocità dell"otturatore che l"AutoISO cercherà di mantenere.
* Max Av : l"apertura massima di diaframma che l"AutoISO cercherà di mantenere.
* _*Script*_: Questo menu configura il comportamento degli [#Gli_script script].
* Oscura LCD: se attivato (impostato su Si), la luminosità dello schermo LCD viene abbassata durante lo script, per aumentare la durata della batteria, il valore iniziale viene reimpostato al termine dell"esecuzione dello script.
* No AutoOFF: se attivato (impostato su Si), la funzione di auto spegnimento della camera viene disabilitata durante l"esecuzione dello script. Viene riattivata al termine dell"esecuzione.
* HandWave: questo sottomenu configura lo script [#Hand_Wave Hand Wave].
* Ritardo: seleziona se questo script debba effettuare lo scatto subito o attendere 2 secondi.
* Azione: l"azione da eseguire (Intervallometro, Scatto singolo, AEB Esteso).
* Ripeti: se attivo (impostato su Si), lo script ri riavvierà dopo l"esecuzione, in modo da rimanere attivo e consentire un nuovo scatto col movimento della mano.
* Subito: se attivo (impostato su Si), lo script scatta appena rileva la mano; altrimenti, lo script aspetterà che la mano venga tolta da davanti il sensore.
* _*AEB Est.*_: Questo sottomenu configura lo script [#AEB_Esteso AEB Esteso]:
* Ritardo: seleziona se questo script debba effettuare lo scatto subito, o attendere 2 secondi.
* Immagini: numero di fotogrammi che lo script deve scattare. Può essere impostato un valore tra 1 e 9.
* Stop/EV: la differenza in EV tra ogni scatto. Può essere impostato un valore tra 0 (spento) e +/-6EV
* Bulb min: velocità minima dell’otturatore in modalità BULB. Può essere impostato un valore compreso tra 1/4000 di secondo e 16 minuti ).
* Bulb max: velocità massima dell"otturatore in modalità BULB. Può essere impostato un valore compreso tra 1/4000 di secondo e 16 minuti ).
* _*Interval.*_: Questo sottomenu consente di configurare lo script [#Intervallometro Intervallometro]:
* Ritardo: seleziona se questo script debba effettuare lo scatto immediatamente o attendere 2 secondi.
* Tempo (s): intervallo (in secondi) tra gli scatti. Può essere impostato un valore tra 0 e 250.
* AEB Est.: seleziona se lo script [#AEB_Esteso AEB Esteso] debba essere utilizzato su ogni scatto.
* Scatti: numero di scatti da eseguire. Può essere impostato un valore tra 0 e 250, oppure il valore "X" per scattare all"infinito.
* _*Autoscat.*_: Questo sottomenu configura lo script [#Autoscatto Autoscatto]:
* Ritardo: il tempo (in secondi) che lo script deve aspettare prima di eseguire lo scatto. Può essere impostato un valore tra 0 e 250.
* Azione: l"azione da eseguire (Intervallometro, Scatto singolo, AEB Esteso).
* _*Preset*_: Questo sottomenu configura il comportamento delle [#Le_preselezioni preselezioni]:
* UsaA-DEP: se attivo (impostato su Si), viene utilizzata la modalità A-DEP solo per le [#Le_preselezioni preselezioni]. Consultare la sezione [#La_modalit%C3%A0_A-DEP Modalità A-DEP] per maggiori informazioni.
* Fotocam.: se attivo (impostato su Si), richiamando una preselezione verranno richiamati i parametri di scatto della fotocamera (velocità di scatto, apertura, ISO, ...).
* 400D+   : se attivo (impostato su Si), richiamando una preselezione verranno richiamati i parametri di configurazione di 400D+ (script, ...).
* Impost. : se attivo (impostato su Si), richiamando una preselezione verranno richiamati alcuni parametri di configurazione che vengono cambiati molto di rado (lingua, sistema video, ...).
* Immagine: se attivo (impostato su Si), richiamando una preselezione verranno richiamate le impostazioni relativi all"immagine(RAW/JPEG, qualità, ...).
* Fn pers.: se attivato (impostato su Si), richiamando una preselezione verranno richiamate le impostazioni per le funzioni personalizzate (C.Fn) (blocco specchio, riduzione rumore per le esposizioni lunghe, ...).
* _*Menu Sviluppatori*_: Con la pressione del tasto SET mentre questa voce è evidenziata si entra nel [#Il_menu_degli_sviluppatori Menu degli sviluppatori].

= Menu di accesso diretto =

Per accedere al menu di accesso diretto, è sufficiente premere il tasto DP dalla schermata principale (ovviamente, a meno che nel menu delle impostazioni non sia impostata su Off la voce "Accesso Diretto"). Navigando normalmente all"interno di questo menu, con la pressione del tasto SET viene lanciato uno script:

* _*ISO Intermedi*_: Scorre tra i valori ISO intermedi. i valori sono compresi tra 100 e 3200.
* _*ISO*_: Roll through the intermediate ISO values. Values are 100 - 3000.
* _*Color Temp. (K)*_: Lo stesso del [#Il_menu_delle_impostazioni menu delle impostazioni].
* _*Temp. Colore (K)*_: permette di impostare una temperatura di colore in gradi Kelvin definita dall"utente e attiva automaticamente il bilanciamento del bianco personalizzato. (Stessa voce [#Il_menu_delle_impostazioni del menu impostazioni)
* _*AEB Esteso*_: Avvia lo script [#AEB_Esteso AEB Esteso].
* _*Intervallometro*_: Avvia lo script [#Intervallometro Intervallometro].
* _*Hand Wave*_: Avvia lo script [#Hand_Wave Hand Wave].
* _*Autoscatto*_: Avvia lo script [#Autoscatto Autoscatto].
* _*Flash Aiuto AF*_: Abilita o disabilita l"attivazione del flash (durante la fase di AF), anche se il flash è alzato e attivato. I possibili valori sono: Enabled, Disabled, Ext Only (come nella C.Fn 05).
* _*Blocco Specchio*_: Abilita o Disabilita la funzione personalizzata "mirror lock-up" (blocco dello specchio) come nella C.Fn 07.
* _*Flash 2a Tendina*_: Abilita / Disabilita la funzione personalizzata "sync flash to the second curtain" (sincronizzazione del flash in seconda tendina) come nella C.Fn 09.

Per uscire dal menu di accesso diretto, basta premere a metà corsa il pulsante di scatto.

== Configurazione del Menu di accesso diretto ==

All"interno del Menu di accesso diretto, c"è la possibilità di personalizzare l"ordine delle voci secondo le preferenze personali. Per fare ciò, nel menu di accesso diretto, premere il tasto PLAY per "prendere" una voce (una piccola ">" comparirà a destra della voce stessa); con la pressione di SU e GIU" si seleziona la nuova posizione, e con una nuova pressione del tasto PLAY si termina lo spostamento e si salvano le impostazioni.

= Gli script =

Tutti gli script vengono attivati dal menu dei [#Menu_dei_collegamenti_rapidi collegamenti rapidi]. Quindi, per avviare uno script, bisogna assicurarsi che nel menu delle impostazioni di 400D+ sia impostata su Si la voce Accesso Diretto.
Quando si avvia o si ferma uno script, si sentirà un _bip_, e mentre uno script è in esecuzione, il pulsante di stampa diretta lampeggia (due volte al secondo, circa). Per fermare uno script in esecuzione, è sufficiente premere nuovamente il pulsante DP; qualche volta la macchina potrebbe non fermarsi immediatamente, in tal caso bisogna premere e tenere premuto il pulsante DP finché non si sentirà un _bip_ che annuncia l"effettiva chiusura dello script.

== AEB Esteso ==

Questo script esegue la stessa attività dell"opzione standard AEB dalla macchina fotografica, ma aggiunge alcune migliorie:
* Possono essere effettuati fino a 9 scatti.
* La differenza tra gli scatti può essere configurata fino a +-6 EV.
* La fotocamera effettuerà tutti i colpi in sequenza, automaticamente.
In modalità M col tempo impostato a BULB, questo script farà scattare la fotocamera tutte le volte che servono, con tempi di scatto vanno dal valore "Bulb min" al valore "Bulb max", e separando ogni scatto in base al valore "Step (EV)". Da notare anche che in questa modalità possono essere usati tempi di esposizione lunghi fino a 16 minuti.

== Intervallometro ==

Questo script fa scattare la fotocamera il numero di volte configurato (o all"infinito), aspettando il tempo specificato tra uno scatto e l’altro. Questo script può essere utilizzato per creare filmati in stop-motion. Per esempio, impostando "AEB Est." a "Si" si esegue lo script [#AEB_Esteso AEB Esteso] su ogni scatto.

== Hand Wave ==

Questo script fa scattare la fotocamera quando viene innescato il sensore display-off (sul retro della fotocamera). Si può utilizzare questo script per far scattare la fotocamera senza l"aiuto di un telecomando per evitare micromovimenti. E’ possibile far eseguire gli script [#AEB_Esteso AEB Esteso] o [#Intervallometro Intervallometro], se opportunamente configurato nella voce "Azione". Se è attivata l"opzione "Repeat", questo script non verrà terminato una volta attivato, ma si riavvierà in modo da poter effettuare altri scatti con la stessa modalità. Di default, lo script aspetterà che il sensore venga innescato e poi rilasciato (ovvero scatterà appena viene tolta la mano). Se, però, è selezionata l"opzione "Subito", lo script scatterà appena il sensore viene coperto.

== Autoscatto ==

Questo script aggiunge semplicemente una pausa configurabile prima di far scattare la fotocamera. E" possibile eseguire gli script AEB Extended o Intervallometro, se opportunamente configurato nella voce "Azione".


= Le preselezioni =

Una "Preselezione" è una immagine completa di tutte le preferenze di scatto e parametri di configurazione della fotocamera. Le preselezioni possono essere usate per preconfigurare la fotocamera in maniera specifica per una determinata situazione di scatto (e.g. "Panorama", "Ritratto", etc.), ed avere in seguito la possibilità di richiamare velocemente tale configurazione in fase di scatto.

Si possono immagazzinare nella scheda di memoria fino a 9 preselezioni.
Il numero di preselezioni è comunque pressoché illimitato, in quanto è possibile usare più schede di memoria, ognuna contenente 9 preselezioni.

Per salvare una preselezione, bisogna premere DP nel [#Il_menu_delle_impostazioni menu delle impostazioni di 400D+]; poi bisogna selezionare una posizione e premere il tasto SET (se una posizione è già stata usata, il suo contenuto sarà sovrascritto). Per richiamare una preselezione, bisogna premere il tasto DP all"interno del [#Menu_di_accesso_diretto menu di accesso diretto] (ovviamente, per usare questa funzione, il menu di accesso diretto deve essere abilitato); poi bisogna selezionare una preselezione e premere il tasto SET. Una volta attivata la preselezione, le preferenze di scatto e i parametri saranno richiamati e diventeranno immediatamente attivi (se la posizione è vuota, ovviamente, non si avranno effetti).

== La modalità A-DEP ==

In circostanze normali, quando viene richiamata una preselezione, vengono modificati tutti i parametri della fotocamera, anche la modalità di scatto (AE mode), se non specificato diversamente nel [#Il_menu_delle_impostazioni menu delle impostazioni di 400D+]; bisogna tener conto che la fotocamera potrebbe operare in una modalità di scatto diversa da quella selezionata con la ghiera di selezione.
Però, quando la fotocamera viene spenta e poi riaccesa, si reimposterà sulla modalità di scatto selezionata dalla ghiera di selezione.

Per ovviare a questo problema, nel [#Il_menu_delle_impostazioni menu delle impostazioni di 400D+] è presente un"opzione per utilizzare la (pressoché inutile) modalità A-DEP; quando questa opzione è abilitata (Preset>UsaA-DEP: Si), si avranno i seguenti cambiamenti:
* Le preselezioni possono essere usate solo se la fotocamera è in modalità di scatto A-DEP. Immaginiamo che nella ghiera delle modalità di scatto ci sia la parola "Preset" invece di "A-DEP".
* Se la fotocamera viene accesa in modalità di scatto A-DEP, o l"utente posiziona la ghiera delle modalità su A-DEP, l"ultima preselezione usata viene automaticamente richiamata.
* Quando questa opzione è disabilitata (Preset>UsaA-DEP: No), se viene selezionata la posizione A-DEP nella ghiera delle modalità di scatto, la fotocamera userà in maniera normale la modalità A-DEP.

== Configurazione del menu delle preselezioni ==

Come nel menu [#Menu_di_accesso_diretto di accesso diretto], le preselezioni possono essere riordinate a piacimento. Per farlo, mentre si è nel menu per salvare o richiamare una preselezione, premere il tasto PLAY per "prendere" una voce (una piccola ">" comparirà a destra della voce stessa); con la pressione di SU e GIU" si seleziona la nuova posizione, e con una nuova pressione del tasto PLAY si termina lo spostamento e si salvano le impostazioni.

Inoltre, è anche possibile cambiare il nome delle preselezioni rispetto agli standard "Preset 1", "Preset 2", etc. Per fare ciò, nel menu per salvare o richiamare una preselezione:
* Premere il tasto JUMP per entrare nel menu di rinominazione.
* Premere i tasti SU/ GIU"/DESTRA/ SINISTRA" per selezionare una voce.
* Premere il tasto MENU per alternare minuscolo / numeri e maiuscolo / simboli.
* Premere il tasto AV per cambiare in maiuscolo / minuscolo il valore selezionato nel riga del nome della preselezione.
* Premere SET per accettare il valore selezionato e muovere in avanti il cursore.
* Usare rotellina frontale o i tasti ZOOM IN e ZOOM OUT per spostare il cursore avanti e indietro.
* Premere nuovamente il tasto JUMP per salvare le modifiche e tornare nel menu delle preselezioni.

= AutoISO =

Per abilitare l"AutoISO nelle modalità creative, bisogna attivarlo nel [#Il_menu_delle_impostazioni menu delle impostazioni], oppure si può premere il tasto DP nel menu di selezione degli ISO; si può disabilitare sempre tramite [#Il_menu_delle_impostazioni il menu delle impostazioni] o selezionando un qualsiasi valore nel menu di selezione degli ISO.

== AutoISO e modalità Av ==

L"obiettivo dell"AutoISO nella modalità AV è quello di utilizzare il più basso valore ISO che assicuri l"assenza dimosso nella foto; probabilmente, questa è la modalità dove l"AutoISO ha più motivo di essere usato.

Nella modalità AV _normale_, l"utente seleziona ISO e apertura del diaframma, e la fotocamera decide la velocità dell"otturatore misurando la scena. Quando l"AutoISO è attivato, 400plus sceglierà sempre il valore ISO minore (come impostato in "Min ISO"), a meno che la velocità dell"otturatore non sia troppo bassa (il valore impostato su "Min Tv"); quando ciò accade, 400plus aumenterà quanto necessario il valore ISO (fino al valore "Max ISO").

Se è abilitata la funzione safety shift, per mantenere la corretta esposizione in modalità AV, la velocità dell"otturatore potrà essere abbassata sotto il valore "Min Tv" se iene superato il valore ISO "Max ISO".

== AutoISO e modalità Tv ==

In queto caso, l"obiettivoè quello di usare il valore ISO più basso che però assicuri una profondità di campo accettabile: AutoISO aumenterà il valorte ISO quando l"apertura del diaframma sarà più larga di un valore configurato ("Max Av").

Si dovrà impostare "Max Av" appena sotto l"apertura massima della lente che si sta usando. Per esempio, se la lente è una F4.0-F5.6, il valore "Max Av" dovrebbe essere imostato non più basso di F4.5. Altrimenti, AutoISO non funzionerà in modalità Tv.

== AutoISO e modalità P ==

In modalità P, l"AutoISO _prova_ a funzionare come in modalità Av mode; però, siccome la fotocamera decide sia l"apertura del diaframma che la velocità dell"otturatore, non è garantito che aumentando il valore ISO aumenterà anche la velocità dell"otturatore: tende a funzionare bene per valori bassi in "Min Tv", ma per valori più alti la fotocamera tende a decidere invece di chiudere il diaframma.

== AutoISO e modalità M ==

In modalità M, l"obiettivo dell"AutoISO è completamente differente che nelle altre modalità: in questo caso, l"utnte seleziona una coppia tempo-diaframma, e 400plus deciderà il valore ISO giusto per una corretta esposizione. Nessun parametro di configurazione verrà preso in considerazione dall"AutoISO in modalità M, e questo è l"unica modalità in cui l"AutoISO utilizza i valori intermedi degli ISO.

Mentre si guarda nel mirino, è possibile utilizzare i tasti SINISTRA e DESTRAT per variare la compensazione dell"esposizione.

= La selezione dell’AF-Pattern =

In fase di scatto, premere il tasto ZOOM IN per entrare nel menu "selezione punto AF" standard, quindi premere di nuovo il tasto ZOOM IN per entrare nel nuovo menu "selezione pattern AF". Usare i tasti SU, GIU, SINISTRA, DESTRA, e pulsanti SET per spostarsi tra i vari pattern disponibili, quindi premere a metà il pulsante di scatto per uscire dalla finestra di dialogo (rimane impostato anche dopo aver riavviato con una card senza 400D+).

= Le chicche e altre funzioni=

Sono state aggiunte le seguenti *_chicche_* alla fotocamera assieme ad altre modifiche al comportamento della fotocamera, non descritti in precedenza.


== Nella zona AUTO ==

* Il pulsante AV serve per commutare tra JPEG, RAW, and JPEG+RAW. Notice that qualità e dimensione verranno impostate a "HIGH+L" ogni volta che si usa quest"opzione. (rimane impostato anche dopo aver riavviato con una card senza 400D+). *<--NEW*

== Nella zona creativa ==

Nella zona creativa le _chicche_ attivabili sono i seguenti:
* Il pulsante JUMP serve per commutare tra ISO estesi con la ossibilità di incrmentare i valori di 1/8EV stop (vedi [#Estensione_ISO Estensione ISO]). *<--NEW*
* Nella finestra di dialogo di selezione ISO, premere il tasto DP per attivare Auto ISO (vedi [#AutoISO AutoISO]); select any ISO value to deactivate it..
* Nella finestra di selezione della modalità di misurazione, premere DP per impostare la misurazione spot (vedi [#Modalit%C3%A0_di_misurazione_spot Note / modalità di misurazione spot]).
* Nella finestra di dialogo di selezione del bilanciamento bianco, premere DP per impostare la temperatura del colore definito dall"utente.

== Informazioni aggiuntive ==

Nella schermata delle impostazioni della fotocamera (ci si arriva premendo DISP nel menu standard della fotocamera), l"ultima riga mostrerà le seguenti informazioni (al posto dello spazio libero nella scheda di memoria):
* Il numero totale di scatti fatti dalla fotocamera.
* La versione di 400D+ correntemente installata.
* Il "BodyID" (un numero interno, unico per ogni fotocamera).
L"uso dei tasti SET, SINISTRA o DESTRA per cambiare il valore visualizzato.

*NOTA che questa funzione è disponibile solo nella zona creativa (P, Tv, Av, M, A-DEP).

== Il problema "naso" ==

Mentre si guarda attraverso il mirino, i pulsanti ISO e WB non sono più attivi, per prevenire modifiche accidentali con il naso dell"utente.

== Il menu degli sviluppatori ==

*ATTENZIONE*: Queste opzioni dovrebbero essere utilizzate con molta attenzione, probabilmente c"è molto poco da vedere qui, a meno che tu non stia sviluppando un tuo hack personalizzato.

Per entrare nel menu degli sviluppatori dal menu 400D+, andare giù sulla voce "Menu Sviluppatori" e premere il tasto SET. Saranno disponibili le seguenti opzioni:
* _*Entra factory mode*_: Fa entrare la fotocamera nel "factory mode"; inoltre attiva il "Menu Factory".
* _*Esci  factory mode*_: Esce dal "factory mode" e ritorna al "normal mode".
* _* Avvia modal. debug*_: La fotocamera scriverà una notevole quantità di informazioni sulla scheda di memoria, in due (2) file chiamati STDOUT.TXT e STDERR.TXT.
* _*Modalità File Log*_:  Imposta come salvare il log tra: un file nuovo oppure sostituendo o aggiungendo il log al precedente. *<--NEW*

*NOTA*: Dopo essere entrato nel "factory mode", il "Menu Factory" rimarrà disponibile finché non viene spenta la fotocamera. Uscire dal "factory mode" non disabiliterà il "Menu Factory".

*NOTA*: Ricordati di uscire dal "factory mode" prima di usare la fotocamera, poiché le fotografie non possono essere scaricate su un computer mentre la fotocamera è in questa modalità.

== Supporto Multilingua ==

Attualmente 400D+ è tradotto in cinque (5) lingue:

* Francese  *<--NEW*
* Inglese
* Italiano
* Spagnolo
* Tedesco

La conversione in altre lingue è possibile e caldeggiata. Se vuoi fornire assistenza per convertire 400D+ in un altra lingua, per favore fai richiesta nel forum!

= Note =

Alcune note e commenti.

== Estensione ISO ==

I valori di ISO non standard sono ottenuti solo tramite software, e tecnicamente non producono vantaggi per gli scatti rispetto all’uso delle ISO di base abbinata al post-processing dell"immagine

Please, notice that the camera will not always display the correct ISO value; for example, an image shot at ISO-3000 will show as ISO-3200 during the review.

== Modalità di misurazione spot ==

Le modalità di misurazione spot è simile alla modalità standard "misurazione parziale", ma l"area inclusa nel calcolo è più piccola (approssimativamente il 3.5% del centro del mirino, contro il 9% della "misurazione parziale" standard. Funziona abbastanza bene, quando serve.

= Malfunzionamenti conosciuti =

Sono stati riportati e confermati i seguenti malfunzionamenti di una certa rilevanza:

* Issue #15: Cambi di esposizione nell"esecuzione dell"AEB Est. .
* Issue #130: non vengono ripristinate le configurazioni se la camera viene spenta mentre uno script è attivo.

'></a>