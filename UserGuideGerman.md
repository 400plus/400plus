|<font color='red'><b>WARNING</b>: This guide is at least one major version behind the latest official release, and thus may contain inaccuracies or outdated information.</font>|
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

# Übersetzung #
German translation provided by [Speedy](http://chdk.setepontos.com/index.php?topic=3290.msg63164#msg63164)
Based on english Wiki [r1415](https://code.google.com/p/400plus/source/detail?r=1415)
# Inhaltsangabe #



# Einleitung #

## Was ist 400plus? ##

**400plus** ist eine frei zugängliche Erweiterung der Firmware, welche zusätzliche Funktionalitäten und Möglichkeiten für Ihre Canon 400D/XTi bietet;
dies geschieht sowohl auf nicht zerstörerische, noch auf dauerhafte Art und Weise.
Sie funktioniert, indem sie während des Startvorgangs automatisch in den Speicher der Kamera geschrieben wird um die eigentliche Firmware zu erweitern, ist aber kein dauerhaftes Firmwareupgrade und kann einfach wieder entfernt werden.
Sie wurde speziell für die Canon 400D/XTi entwickelt und wird mit anderen Kameramodellen nicht funktionieren.

## Handbuch ##

Diese Wikiseite dient als Handbuch für 400plus.
Sie geht davon aus, dass 400plus bereits installiert wurde und ordnungsgemäß funktioniert bevor dieses Handbuch gelesen wird.
Für Informationen über die Installation von 400plus lesen Sie bitte [FirmwareHackInstallation](FirmwareHackInstallation.md).

# Das Menü #

## Das Menü aufrufen ##

Um Zugriff auf das Menü zu erhalten, drücken Sie die `DP`-Taste, wenn Sie sich im Hauptdialog der Kamera befinden.
Um das 400plus-Menü wieder zu verlassen, drücken Sie den Auslöser einfach halb durch.
> _ANMERKUNG_: Die `DP`-Taste befindet sich auf der Rückseite der Kamera, links neben dem Sucher (direkt neben dem blauen Druckersymbol mit dem geschwungenem Pfeil an der Seite.

## Durch das Menü navigieren ##

400plus hält ein mehrseitiges Menü bereit, in welchem jede Seite einer bestimmten Aufgabe gewidmet ist.
Um durch die Seiten zu navigieren benutzen Sie das Hauptwahl-Rad oder die `ZOOM IN`-/ `ZOOM OUT`-Tasten (beachten Sie die Symbole `<<` und `>>` in der Kopfzeile).
Es gibt außerdem eine Möglickeit jede Seite schnell zu erreichen: wenn Sie die `AV`-Taste drücken und halten, wird eine Liste aller verfügbaren Seiten angezeigt;
benutzen Sie nun das Hauptwahl-Rad um eine Seite auszuwählen und lassen Sie die `AV`-Taste los um diese zu öffnen.

Um innerhalb einer Seite zu navigieren benutzen Sie die `HOCH` (`ISO`)- und `RUNTER` (`WB`)-Tasten;
benutzen Sie die `LINKS` (`MESSFELD`)- und `RECHTS` (`AF`)-Tasten um den Wert der gewählten Einstellung zu verändern (drücken und halten Sie diese Tasten um die Werte schneller zu verändern). Einstellungen, welche ein Ausrufezeichen '`!`'' auf der linken Seite haben, führen eiine Aktion aus;
aktivieren Sie diese mit der `SET`-Taste.
Einstellungen mit einer schließenden dreieckigen Klammer '`>`' stehen für Untermenüs; öffnen Sie diese mit der `RECHTS`-Taste und kehren Sie mit der ÀV`-Taste ins Ursprungsmenü zurück.
Beachten Sie, dass einige Einstellungen sowohl eine Aktion ausführen, als auch ein Untermenü haben können.

## Das Menü einstellen ##

Während Sie sich auf einer Seite innerhalb des Menüs befinden haben Sie die Möglichkeit die Reihenfolge der Einstellungen nach Belieben anzupassen.
Um dies zu tun drücken Sie einfach die `PLAY`-Taste ume eine Einstellung zu "greifen" (ein kleines ">" wird links der Einstellung angezeigt).
Nun benutzen Sie die `HOCH`- und `RUNTER`-Tasten um die Einstellung im Menü an eine beliebige Stelle zu bewegen. Beenden Sie diesen Vorgang indem Sie erneut die `PLAY`-Taste drücken um die änderugen zu speichern.

## Seiten ##

### Parameter ###

  * _**AutoISO**_: Dieses Untermenü dient dem Einstellen des [AutoISO](#AutoISO.md).
    * Aktivieren: Ja wählen, um AutoISO einzuschalten.
    * Min ISO: niedrigster ISO-Wert den AutoISO benutzen soll.
    * Max ISO: höchster ISO-Wert den AutoISO benutzen soll.
    * Min Tv : niedrigste Verschlusszeit die AutoISO beizubehalten versucht.
    * Max Av : höchste Blendenöffnung die  AutoISO beizubehalten versucht `[*]`.
  * _**ISO**_: Rollen Sie durch die ISO-Werte. Mögliche Werte liegen zwischen 100 - 3000.
  * _**Av Abgleich**_: Bewirkt das Gleiche wie die _Standard_ "Belichtungskorrektur", erweitert die Auswahl aber von -6 bis +6 EV.
  * _**AEB**_: Bewirkt das Gleiche wie die _Standard_ "AEB", erweitert die Auswahl aber von -6 bis +6 EV.
  * _**Farbtemp. (K)**_: Setzt eine benutzerdefinierte Frabtemperaturwert in Kelvin, und setzt WB auf "benutzerdefiniert".
  * _**Spiegelverriegel.**_: (De-)aktiviert "Spiegelverriegelung" (bewirkt das Selbe wie die Custom Function - C.Fn 07).
  * _**Safety shift**_: Falls aktiviert (Ja gewählt) und die Kamera sich im `TV`- bzw. `AV`-Modus befindet, verändert die Kamera die vom Benutzer gewählte  Verschlußzeit bzw. Blendenöffnung um eine Unter- oder Überbelichtung zu vermeiden, falls der gewählte Wert zu klein bzw. groß für die aktuelle Szene ist.
  * _**Blitz**_: Einstellung für das  Blitzgerät
    * Blitz Abgleich: Bewirkt das Gleiche wie die _Standard_"Blitzbe. Korr.", erweitert die Auswahl aber von -6 bis +6 EV.
    * Disable flash: Deaktiviert die Benutzung des Blitzes, selbst wenn der interne Blitz bereits aufgeklappt ist.
    * AF Blitz: (De-)aktiviert die Benutzung des Blitzes (während der Autofokusphase), selbst wenn der interne Blitz bereits aufgeklappt ist. Möglichkeiten: Aktiviert, Deaktiviert, Nur Extern (bewirkt das Selbe wie die Custom Function - C.Fn 05).
    * Blitz 2. Vorhang: Kontrolliert das Synchronisationsverhalten des Blendenvorhangs (bewirkt das Selbe wie die Custom Function - C.Fn 09).
  * _**Infrarot Fernbed.**_: Einstellungen für Infrarotauslöser:
    * IR Fernb. aktiv: aktivieren (Ja wählen), wenn Sie eine IR-Fernbedienung benutzen wollen. Falls Nein gewählt wird, wird dieses Feature deaktiviert.
    * IR Fernb. Verz.: Auswahl ob die Kamera sofort oder um 2 Sekunden verzögert auslösen soll, wenn eine IR-Fernbedienung verwendet wird.

_`[*]` Beachten Sie, dass die auswählbaren Werte die dieser Parameter anbietet in Abhängigkeit zu der physikalischen Beschaffenheit Ihres Objektivs stehen;
Bei einem Zoomobjektiv kann die maximale Blendenöffnung je nach Zoomposition unterschiedlich sein.
Bitte zie´hen Sie diesen Fakt in Betracht wenn Sie den Wert einstellen_.

### Seite: Skripte ###

  * _**Erweitertes AEB**_: Diese Einstellung konfiguriert und startet das [Erweitertes AEB](#Erweitertes_AEB.md) Skript:
    * Verz.: Wählt aus, ob das Skript sofort oder aber mit 2 Sekunden Verzögerung startet.
    * Aufnahmen: Die Anzahl der Aufnahmen die das Skript machen soll. Mögliche Werte liegen zwischen 1 und 9.
    * Schritt (EV): Der EV-Abstand (Belichtungswert) zwischen jeder Aufnahme. Mögliche Werte liegen zwischen +1/3EV und +6EV.
    * Reihenfolge: Beschreibt die _Reihenfolge_ der EAEB Sequenz.
    * Bulb min: Die niedrigste Verschlußzeit im `BULB` mode. Werte reichen von 1/4000 Sekunde bis zu 32 Minuten.
    * Bulb max: Die längste Verschlußzeit im `BULB` mode. Werte reichen von 1/4000 Sekunde bis zu 32 Minuten.
  * _**Blitz AEB**_: Konfiguriert und startet das [Blitz AEB](#Blitz_AEB.md) Skript:
  * _**ISO AEB**_: Diese Einstellung konfiguriert und startet das [ISO AEB](#ISO_AEB.md) Skript; jede Einstellung im Konfigurationsuntermenü gibt an, ob die Kamera für den gewählten ISO-Wert einmal ausgelöst werden muss.
  * _**Interval**_: Konfiguriert und startet das [Intervalometer](#Intervalometer.md) Skript:
    * Verz.: Wählt aus, ob das Skript sofort oder aber mit 2 Sekunden Verzögerung startet.
    * Zeit: Der Zeitraum (in Minuten:Sekunden) zwishcen den einzelnen Aufnahmen (oder Gruppen von Aufnahmen). Werte liegen zwischen 00:01 und 05:00.
    * Aktion: Die auszuführende Aktion (One Shot, Erweitertes AEB, Blitz AEB, ISO AEB, Langzeitbelichtung).
    * Aufnahmen: Die Gesamtanzahl der Aufnahmen die das Skript machen wird. Werte liegen zwischen 1 und 250 und "No Limit" um endlos aufzunehmen.
    * Videoformat (fps): Angestrebte Framerate der Wiedergabe, falls eine Zeitrafferaufnahme vorbereitet wird.
    * Aufnahmezeit: Voraussichtliche Zeit, die die Kamera benötigen wird um die komplette Zeitrafferaufnahme aufzunehmen (nur zur Information).
    * Wiedergabezeit: Voraussichtliche Wiedergabezeit der Zeitrafferaufnahme (nur zur Information).

  * _**Winken**_: Konfiguriert und startet das [Winken](#Winken.md) Skript:
    * Verz.: Wählt aus, ob das Skript sofort oder aber mit 2 Sekunden Verzögerung startet.
    * Aktion: Die auszuführende Aktion (One Shot, Erweitertes AEB, Blitz AEB, ISO AEB, Langzeitbelichtung).
    * Wiederholen: Falls aktiviert (Ja gewählt), wird sich das Skript nach Beendigung von alleine neustarten. Dies erlaubt es Ihnen mit Ihrer Hand erneut zu winken  um das Skript weiter zu benutzen.
    * Instant: Falls aktiviert (Ja gewählt), wird das Skript eine Aufnahme machen, sobald es eine Hand erkennt; ansonsten wartet es auf ein Verschwinden der Hand.
  * _**Timer**_: Konfiguriert und startet das  [#Selbstauslöser Selbstauslöser] Skript:
    * Verz.: Die Zeit (in Minuten:Sekunden) die das Skript warten soll bevor es auslöst. Werte liegen zwischen 00:00 und 05:00.
    * Aktion: Die auszuführende Aktion (One Shot, Erweitertes AEB, Blitz AEB, ISO AEB, Langzeitbelichtung).
  * _**Langzeitbelichtung**_:  Konfiguriert und startet das [Langzeitbelichtungs](#Langzeitbelichtung.md) Skript:
    * Verz.: Wählt aus, ob das Skript sofort oder aber mit 2 Sekunden Verzögerung startet.
    * Time: Die Belichtungszeit (in Minuten:Sekunden). Werte liegen zwischen 00:15 und 100:00.
    * Rechner: Öffnet [den Rechner für Langzeitbelichtungen](#Langzeitbelichtungsrechner.md).
  * _**DOF Rechner**_: Startet den [DOF Rechner](#DOF_Rechner.md):
    * Focal length (mm): Brennweite des Objektivs in mm.
    * Av: Blende des Objektivs.
    * Fokusabstand (m): Entfernung zum Fokuspunkt.
    * Min. DOF (m): Kürzeste Entfernung mit akzeptapler Schärfe (nur zur Information).
    * Max. DOF (m): Längste Entfernung mit akzeptapler Schärfe (nur zur Information)

### Seite: Info ###

  * _**Auslösezähler**_: Die Anzahl der Auslösevorgänge des Kamera-Bodies.
  * _**Body ID**_: Die "BodyID" des Kamera-Bodies (eine einmalige interne Nummer).
  * _**Version**_: Die Versionsnummer der aktuell installierten 400plus-Software.

### Seite: Einstellungen ###

  * _**Sprache**_: Bestimmt die Menüsprache von `400plus`; wenn Sie "`Camera`" wählen, wird die Sprache welche in der Kamera eingestellt ist verwendet.
  * _**ISO in Sucher**_: Falls aktiviert (Ja gewählt), können Sie die Pad-Tasten benutzen um den ISO-Wert anzuzeigen und zu verändern während Sie durch den Sucher schauen;weitere Informationen finden Sie unter [ISO in Sucher](#ISO_in_Sucher.md).
  * _**Entwicklermenü**_: Falls aktiviert (Ja gewählt), ist das Entwicklermenü als Seite aufrufbar.
  * _**Konfig. Skripts**_: Dieses Untermenü konfiguriert das Verhalten [der Skripte](#Die_Skripte.md).
    * Deaktiviere Power-Off: Falls aktiviert (Ja gewählt), wird das automatische Abschalten der Kamera deaktiveiert. Dies wird zurückgesetzt, nachdem das Skript beendet wurde.
    * LCD Display: Stellt die Helligkeit des LCD-Bildschirms während der Ausführung eines Skripts ein.
    * Indikator: Stellt die Häufigkeit ein, wie oft die blaue LED blinkt während ein Skript ausgeführt wird.
  * _**Konfig. Tasten**:_ In diesem Untermenü kann der Benutzer das Verhalten einiger Spezialtasten einstellen:
    * Bessere DISP Taste: Falls aktiviert (Ja gewählt), verändert die `DISP`-Taste die Bildschirmhelligkeit in kleinen Schritten anstatt es lediglich ein- und auszuschalten.
    * JUMP: Zuweisung einer Aktion die bei Betätigung der `JUMP`-Taste aus dem Hauptmenu erfolgen soll:
      * Intermediate ISO: verändert den ISO-Wert um 1/8 EV (lesen Sie hierzu [Notes / Erweiterte ISOs](#Erweiterte_ISOs.md)).
      * Repeat last script: Wiederholt das zuletzt aufgerufene Skript.
      * Mirror lock-up: Schaltet die Spiegelverriegelung ein/aus.
      * AEB: Rollt duch die AEB-Abstände von 0EV zu 1EV, dann 2EV, und wieder zurück zu 0EV (aus).
    * Mülleimer: Hier gilt das Gleiche wie für die `JUMP`-Taste.
  * _**Konfig. Presets**_: Dieses Untermenü konfiguriert [die Presets](#Die_Presets.md):
    * Benutze A-DEP: Falls aktiviert (Ja gewählt), wird der `A-DEP`-Modus für [die Presets](#Die_Presets.md) verwendet. Lesen Sie hierzu [der A-DEP\_Modus](#Der_A-DEP_Modus.md).
    * Camera: Falls aktiviert (Ja gewählt), führt das Laden eines Presets dazu, dass die Aufnahmeparameter der Kamera neu abgefragt werden. (Verschlusszeit, Blende,ISO,...).
    * 400plus: Falls aktiviert (Ja gewählt), führt das Laden eines Presets dazu, dass 400plus' eigene Einstellungen verwendet (Skripts, ...).
    * Einstellungen: Falls aktiviert (Ja gewählt), führt das Laden eines Presets dazu, dass einige der selten geänderten Parameter neu abgefragt werden (Sprache, Videosystem,...).
    * Bild: Falls aktiviert (Ja gewählt), führt das Laden eines Presets dazu, dass Parameter bezüglich des Bildes neu abgefragt werden (RAW/JPEG, Qualität, ...).
    * Custom Fn: Falls aktiviert (Ja gewählt), führt das Laden eines Presets dazu, dass die Custom Functions (C.Fn.) neu abgefragt werden (Spiegelverriegelung, Langzeitbelichung, Rauschreduktion, ...).
  * _**Konfig. Seiten**_: Benutzen Sie dieses Untermenü um einzustellen, in welcher Reihenfolge die Seiten angezeigt werden müssen.

### Seite: Presets ###

Diese Seite dient dazu [Presets](#Die_Presets.md) zu laden, zu sichern und umzubenennen; machen sie Folgendes um ein Preset umzubenennen:

  * Wählen Sie die "Umbenennen"-Option im Presets-Untermenü aus.
  * Benutzen Sie die `HOCH`- / `RUNTER`- / `LINKS`- / `RECHTS`-Tasten um einen Wert auszuwählen.
  * Benutzen Sie die `MENU`-Taste um zwischen Kleinbuchstaben / Ziffern und Großbuchstaben / Symbolen zu wechseln.
  * Benutzen Sie die `JUMP`-Taste um für das gewählte Zeichen zwischen Groß- und Kleinschreibung zu wechseln (Fußzeile).
  * Benutzen Sie die `SET`-Taste um den gewählten Wert zu benutzen und den Zeiger auf die nächste Position zu verschieben.
  * Benutzen Sie das Hauptwahlrad oder die `ZOOM IN`- / `ZOOM OUT`-Tasten um den Zeiger innerhalb des Presetnamens zu verschieben (Fußzeile).
  * Drücken Sie die `AV`-Taste erneut um Ihre änderungen zu speichern und ins vorherige Menü zurückzukehen.

Beachten Sie bitte, dass links von jedem Preset eine Nummer angezeigt wird. Diese Funktion ist praktisch, falls Sie Presets von / auf mehreren CF-Karten kopieren wollen und daher die Dateinamen der jeweiligen Presets wissen müssen: die Nummer auf der linken Seite stimmt mit der Nummer im Dateinamen der Datei auf der CF-Karte überein.

### Seite: Entwickler ###

**ANMERKUNG**: Die Entwicklerseite wird standardmäßig nicht angezeigt. Sie muss auf der  [Einstellungsseite](#Seite:_Einstellungen.md) aktiviert werden um angezeigt werden zu können;
zudem liegt die Entwicklerseite außerhalb der normalen Navigation: drücken Sie die `MÜLLEIMER`-Taste, während Sie sich im Menü befinden um die Entwicklerseite angezeigt zu bekommen.

_Diese Seite wurde bewusst leergelassen._

**WARNUNG**: Die Optionen auf dieser Seite sollten nur mit größter Vorsicht benutzt werden;
so lange Sie nicht gerade an einem eigenen Hack arbeiten, gibt es hier für Sie höschstwahrscheinlich nicht viel zu sehen.

# Die Skripte #

Wenn ein Skript startet oder stoppt ist ein _piep_ zu hören; während ein Skript läuft wird die `DP`-Taste ca. 2 mal pro Sekunde blinken.
Um ein in der Ausführung befindlichse Skript zu stoppen, drücken Sie die `DP`-Taste erneut; es kann vorkommen, dass die Kamera nicht augenblicklich stoppt, darum sollten Sie die `DP`-Taste so lange halten, bis Sie ein _piep_ hören, welches das Ende der Skriptausführung bedeutet.

Ein bereits gestartetes Skript kann außerdem pausiert werden, indem die `DISP`-Taste gedrückt wird. Dies wird die Kamera in einen Energiesparmodus versetzen und alle laufenden Aktivitäten stoppen;
bei nochmaligem Drücken der `DISP`-Taste wird die Kamera wieder aufgeweckt und das Skript wird normal fortgeführt.

Alle Skripte testen vor jeder Aufnahme den verfügbaren Speicherplatz auf der CF-Karte; falls die Anzahl der speicherbaren Aufnahmen eine gewisse Anzahl unterschreitet (3), wird das Skript seine Ausführung stoppen.

## Erweitertes AEB ##

Dieses Skript übernimmt die gleiche Aufgabe wie die _Standard_ AEB Option der Kamera, jedoch enthält sie einige praktische Erweiterungen:
  * Es können bis zu 9 Aufnahmen eingestellt werden.
  * Der Unterschied zwischen den einzelnen Aufnahmen kann bis zu +-6 EV konfiguriert werden.
  * Die Kamera wird die Aufnahmen automatisch in einer Sequenz schießen.
  * Der Benutzer kann die _Reihenfolge_ dieser Sequenz selber festlegen.

Angenommen sei eine Konfiguration von 5 Aufnahmen mit 1EV Unterschied; nachfolgend finden Sie eine Auflistung was die verschiedenen _Reihenfolgen_ bewirken:
  * `+/-` : Eine Aufnahme mit der aktuellen EV und die restlichen darüber und darunter: 0EV, +1EV, -1EV, +2EV, -2EV.
  * ` + ` : Eine Aufnahme mit der aktuellen EV und die restlichen darüber: 0EV, +1EV, +2EV, +3EV, +4EV.
  * ` - ` : Eine Aufnahme mit der aktuellen EV und die restlichen darunter: 0EV, -1EV, -2EV, -3EV, -4EV.

Im 'M'-Modus und einer Belichtungszeit mit Wert `BULB` wird das Skript so oft wie benötigt die Kamera auslösen (in diesem Modus ist die Anzahl der eingestellten Aufnahmen irrelevant). Die genutzten Verschlußzeiten befinden sich zwischen dem Wert für "Bulb min:" und dem Wert für "Bulb max:", wobei jede Aufnahme durch den Wert von "Step (EV)" verändert wird. Beachten Sie bitte auch, dass in diesem Modus Belichtungszeiten von bis zu 32 Minuten eingestellt werden können.

## Blitz AEB ##

Dem [Erweitertes AEB](#Erweitertes_AEB.md)-Skript sehr ähnlich, nur dass hier die Blitzbelichtungskorrektur verändert wird.

## ISO AEB ##

Die Kamera wird eine Aufnahme für jeden eingestellten ISO-Wert machen.
Möglicherweise möchten Sie lieber in den `M`-Modus wechseln bevor Sie dieses Skript benutzen.

## Intervalometer ##

Dieses Skript lässt die Kamera so oft wie eingestellt wurde (oder endlos) auslösen, wobei der zeitliche Abstand zwischen den Aufnahmen einstellbar ist;
Praktisch ist dies zum Beispiel für _Stop-Motion_-Videos.

### Strikte Zeitplanung ###
Beachten Sie bitte, dass `400plus` immer versuchen wird die Aufnahmen in einem gleichmäßigen Rhythmus, unabhängig von der Belichtungszeit, zu machen:
Wenn zum Beispiel eine Intervallänge von 15 Sekunden eingestellt wurdedann wird exakt alle 15 Sekunden eine Aufnahme gemacht, auch wenn eine Belichtungszeit von 10 Sekunden eingestellt wurde.
Falls eine Aufnahme in der Sequenz eine Belichtungszeit hat, welche länger als die Intervallänge ist, wird `400plus` genau so viele Aufnahmen aussetzen wie nötig und die Aufnahmesequenz entsprechend neu planen.
Dies ist auch dann gültig, wenn das Intervalometer für eine beliebige Multi-Aufnahme-Aktion konfiguriert wurde.

Ein Beispiel:
Stellen Sie sich ein Interval von 5 Sekunden und Belichtungszeiten zwischen 1 und 4 Sekunden vor (wir nehmen an, die Kamera befindet sich im Av-Modus und die Lichtverhältnisse verändern sich während des Skripts):

```
Time (s) : # · · · · # · · · · # · · · · # · · · ·
Exposure : * *       * * * *   *         * *
```

Achten Sie darauf, wie die Pausenlänge sich zwischen dem Ende einer Belichtung und dem Start der nächsten sich der Belichtungszeit anpasst, so dass die Aufnahmen immer zu den passenden Intervallen starten. Jetzt stellen Sie sich vor, dass eine der Belichtungen länger dauern wird als 5 Sekunden (nehmen wir 7 Sekunden an):

```
Time (s) : # · · · · # · · · · # · · · · # · · · ·
Exposure : * *       * * * * * * *       * *
```

Achten Sie darauf, dass die dritte Aufnahme nicht 5 Sekunden nach der zweiten, sondern erst zu Sekunde 15 gestartet wird.

**ANMERKUNG**: '400plus' überprüft nicht, ob die Eingaben des Benutzers auch Sinn machen; Es wird sich, zum Beispiel, nicht beschweren wenn Sie zum Beispiel eine Intervallzeit von 10 Sekunden mit einer Belichtungszeit von 15 Sekunden setzen;
es obliegt alleinig dem Benutzer diese Situationen zu erkennen und zu vermeiden.

### Zeitraffer Rechner ###

Falls Sie planen, eine Zeitrafferaufnahme aus den Fotografien, welche durch dieses Skript produziert wurden, zu erstellen, so können Sie die gewünschte Wiedergabe Framerate angeben und das Skript wird die daraus resultierende Wiedergabezeit berechnen. DIese Parameter sind lediglich informativ und haben keinerlei Auswirkungen auf das Skript selber.

## Winken ##

Das Skript löst die Kamera aus, wenn der LCD-Aus-Sensor (auf der Rückseite der Kamera) ausgelöst wird. Benutzen Sie dieses Skript um Bildverwackelungen zu vermeiden und die Kamera eine Aufnahme machen zu lassen ohne dafür eine Fernbedienung zu benötigen.
Falls die "Repeat"-Option aktiviert ist, beendet sich das Skript nicht, nachdem aus ausgelöst wurde, sondern wiederholt sich damit Sie mehr Aufnahmen nacheinander machen können.
Standardmäßig wartet das Skript, bis etwas (wie zum Beispiel Ihre Hand oder Ihr Finger) den Sensor verdeckt und wieder freimacht.
Es ist jedoch möglich, das Skript auszulösen sobald der Sensor blockiert ist, indem Sie die "Instant"-Option aktivieren.

## Selbstauslöser ##

Dieses Skript wartet eine konfigurierbare Zeitspanne bevor die Kamera auslöst.

## Langzeitbelichtung ##

Bietet die Möglichkeit eine von 15 Sekunden bis 100 Minuten einstellbare Langzeitbelichtung zu realisieren.

Beachten Sie bitte, dass die Kamera sich im 'M + Bulb'-Modus befinden muss um eine Langzeitbelichtung durchzuführen; das Skript wird die Kamera automatisch einstellen, allerdings ist es Aufgabe des Benutzers eine passende Blendeneinstellung zu treffen.

### Langzeitbelichtungsrechner ###


Der Rechner für Langzeitbelichtungen ist ein Werkzeug, welches eigens dafür entwickelt wurde, den Fotografen dabei zu unterstützen schnell die passende Belichtungszeit festzustellen, die für eine bestimmte Szene erforderlich ist.
Die Idee hinter diesem Werkzeug ist, dass eine Szene bei Benutzung eines hohen ISO-Werts und offener Blende schnell gemessen werden kann und dann der ISO-Wert heruntergesetzt und die Blende geschlossen werden wobei die Verschlußzeit entsprechend angepasst werden muss.

Ein Beispiel:
Nehmen wir an wir wollten eine Nachtszene fotografieren; wir entscheiden uns für die niedrigste Empfindlichkeit (ISO 100) um Bildrauschen zu vermeiden und eine ziemlich geschloßene Blende (f/8) um die gewünschte Tiefenschärfe zu erreichen.
Mit diesen Parametern kann die Belichtungszeit leicht größer werden als 30 Sekunden, weswegen wir die Kamera nicht für eine verlässliche Messung benutzen können.

Wir können jedoch temporär eine höhere Empfindlichkeit (z.B. ISO 1600 und f/2.8) auswählen, die Szene messen, und feststellen, dass wir eine Belichtungszeit von 15 Sekunden bräuchten, würden wir diese Parameter nutzen.
Nun öffnen wir den Rechner für Langzeitbelichtungen, senken den ISO-Wert auf 100 und schließen die Blende  (f/8); der EV-Indikator wird einen Wert von -9 anzeigen,
was bedeutet, dass die aktuellen Parameter 9 Schritte unter dem gemessenen Wert liegt.
Nun können wir die Belichtungszeit erhöhen, bis der EV-Indikator zurück auf 0 wechselt, was bedeutet, dass die aktuellen Parameter zu der gleichen Belichtung führen wie zu Beginn; in unserem Fall würde dies bedeuten, dass wir die Belichtungszeit von 15 Sekunden auf 3 Minuten erhöhen müssten.
Letztendlich drücken Sie auf einfach auf "Apply" um  diese Parameter in der Kamera einzustellen und starten Sie das Langzeitbelichtungsskript.

ANMERKUNG: Der Rechner für Langzeitbelichtungen wird nur die Einstellungen, welche auf dem Display angezeigt werden, nur dann regeln, wenn die Belichtungszeit (Tv) mindestens eine Minute beträgt; für kürzere Belichtungszeiten ist die "Apply"-Taste einfach inaktiv.

TIPP: Falls Sie vorhaben einen Neutraldichtefilter (ND) zu  verwenden, können Sie die Szene ohne den ND messen;
benutzen Sie nun den Rechner für Langzeitbelichtungen und stellen Sie die Belichtung so ein, dass Sie ein EV-Ergebnis erhalten, welches invers zu dem Wert Ihres ND-Filters ist.
Ein Beispiel:
nehmen wir an, wir hätten einen ND8 Filter (8 Stufen Lichtreduktion): wenn die Kamera 1/120s, f/4.0 und ISO 1600 ohne Filter misst, dann wählen wir 2', f/8.0 ISO 100 um einen EV von +8 zu erhalten.

### DOF Rechner ###

Der DOF-Rechner kann Ihnen dabei helfen den Schärfentiefebereich eine Szene, oder den Abstandsbereich in welchem eine Szene scharf erscheint zu bestimmen;
um mehr Informationen dazu zu erhalten, besuchen Sie bitte die Seite [DOF Master](http://www.dofmaster.com/index.html).

Nach dem Öffnen des DOF-Rechners geben Sie die Brennweite des benutzen Objetivs, die gewünschte Blende und den Abstand der Kamera zum Motiv ein.
Das Skript wird nun die kürzest- und die weitest entfernte Grenze des Bereichs anzeigen, welche eine akzeptable Schärfe besitzt.
Sie können nun die Blende und / oder die Fokusdistanz ändern, bis der angezeigte Schärfebereich mit dem Bereich ihrer Szene, welcher im Fokus liegen soll, übereinstimmt.

Wenn der Eintrag "Max. DOF (m)" den Wert "INF!" anzeigen sollte, wurde die maximale Fokusdistanz erreicht und somit erscheint der gesamte Bereich von der nahegelgenen Grenze bis unendlich weit entfernt scharf.

# Die Presets #

Ein "Preset" ist eine komplette Abbildung der Kameraeinstellungen und Konfigurationsparameter. Presets können dafür verwendet werden, um die Kamera für eine bestimmte Aufnahmesituation vorzukonfigurieren (wie z.B. "Landschaftsaufnahme", "Porträt", "Low Light","Tiere",usw.), und erlauben dadurch einen schnellen Zugriff auf diese Einstellungen während des Shootings. Presets werden auf der CF-Karte gespeichert. Bis zu 9 Presets können so gespeichert werden. Die Anzahl der Presets jedoch ist unbegrenzt, da es möglich ist auf mehreren CF-Karten je 9 unterschiedliche Presets zu sichern.

## Der A-DEP Modus ##

Unter normalen Umständen werden, wenn ein Preset geladen (wiederhergestellt) wird, alle Kameraparameter verändert, selbst der AE-Modus.
Nehmen Sie bitte zur Kenntnis, dass die Kamera daher also in einem anderen AE-Modus arbeiten könnte, als dem, welcer momentan durch das Moduswahlrad ausgewählt ist. Jedoch wird die Kamera, wenn sie aus- und wieder eingeschaltet wird den AE-Modus auf den Wert setzen, welcher mit dem Moduswahlrad ausgewählt ist.

Um dieses Problem zu umgehen gibt es eine Option, um den (zumeist ungenutzten) A-DEP-Modus zu kapern;
wenn diese Option aktiviert ist, werden folgende änderungen durchgeführt:
  * Presets können nur geladen werden, wenn sich die Kamera im A-DEP-Modus befindet. Stellen Sie sich vor, dass an Stelle von A-DEP "Presets" auf dem Wahlrad stehen würde.
  * Wenn die Kamera  im A-DEP-Modus eingeschaltet wurde, oder wenn der Benutzer das Wahlrad auf die Position A-DEP stellt, wird das letztgenutzte Preset geladen.

Wenn diese Option nicht aktiviert ist, startet bei Auswahl von A-DEP auf dem Wahlrad, wie bisher, der A-DEP-Modus.

# AutoISO #

`400plus` unterstützt AutoISO in den Kreativmodi indem es eigene Algorithmen verwendet. Es funktioniert indem die Messungen der Kamera, welche Sie macht wenn Sie den Auslöser halb durchdrücken, gelesen werden wund den ISO-Wert entsprechend angepasst werden.

AutoISO verhält sich anders, je nachdem welcher Kreativmodus ausgewählt ist, jedoch bleibt die Idee stets die gleiche: benutze den niedrigsten ISO-Wert um eine angemessene Verschlußzeit oder Blende zu ermöglichen.

Um AutoISO für die Kreativmodi zu einzuschalten, aktivieren Sie es im Einstellungsmwnü, oder drücken Sie die `DP`-Taste im ISO-Auswahldialog;
um es abzuschalten benutzen Sie das Einstellungsmenü und wählen Sie einen beliebigen ISO-Wert.

## AutoISO und der Av-Modus ##

Der Zweck von AutoISO im AV-Modus ist den niedrigsten ISO-Wert zu verwenden, welcher Bewegungsunschärfe verhindert.

Im _normalen_ AV-Modus wählt der Benutzer ISO und Blende aus und die Kamera bestimmt die Verschlußzeit in Abhängigkeit der Szene.
Wenn AutoISO jedoch aktiviert ist, wird `400plus` versuchen den niedrigsten Wert (konfiguriert in "Min ISO") zu verwenden bis dir Verschlußgeschwindigkeit  zu niedrig wird (konfiguriert in "Min Tv"). Wenn dies der Fall sein sollte, wird AutoISO je nach Bedarf automatisch den ISO-Wert erhöhen (bis zu "Max ISO").

Bitte beachten Sie, dass, wenn sowohl Safety Shift als auch AutoISO zugeschaltet sind, die Kamera die Verschlußgeschwindigkeit,falls "Max ISO" erreicht sein sollte, auch unter den konfigurierten "Min Tv" senken könnte, um ein korrekt belichtetes Bild zu erzielen.

## AutoISO und der Tv-Modus ##

Im Tv-Modus ist der Zweck von AutoISO den niedrigstmögliche ISO-Wert zu benutzen um eine akzeptable Bildtiefenschärfe zu bewahren.

Außerdem wird AutoISO im Tv-Modus versuchen solange den niedrigsten ISO-Wert zu wählen (konfiguriert in "Min ISO"), bis die Szene eine offenere Blende als gewünscht benötigt (konfiguriert in "Max Av");
in diesem Fall wird AutoISO den ISO-Wert erhöhen (bis zu "Max ISO").

Bitte beachten Sie, dass Sie den Wert von "Max Av" zumindest etwas über die maximale Blendenöffnung des Objektivs, welches Sie benutzen, setzen.
Zum Beispiel sollten Sie, falls Sie ein f/4-Objektiv benutzen "Max Av" nicht niedriger als f/5.6 setzen;
bitte ziehen Sie auch in Betracht, dass Zoom-Objektive je nach Brennweite unterschiedliche Maximalblenden haben können.
Sollten Sie dies nicht beachten, wird AutoISO nicht wie gewünscht im Tv-Modus funktionieren.
Des Weiteren gilt der Hinweis bezüglich SafetyShift und AutoISO aus dem Av-Modus auch hier.

## AutoISO und der P-Modus ##

Im P-Modus _versucht_ AutoISO sich exakt so zu verhalten wie im Av-Modus und hebt daher den ISO-Wert an, um eine Mindestverschlußgeschwindigkeit zu halten;
da die Kamera in diesem Modus allerdings sowohl die Blende, als auch die Verschlußgeschwindigkeit kontrolliert, gibt es keine Garantie, dass eine Erhöhung des ISO-Wertes nicht die Verschlußzeit erhöht.
Gewöhnlich funktioniert es korrekt für kleine Werte für "Min Tv", für höhere Werte entscheidet sich die Kamera allerdings in der Regel dafür, die Blende zu schließen anstatt eine höhere Verschlußgeschwindigkeit zu wählen.

## AutoISO und der M.Modus ##

Befindet sich die Kamera im M-Modus, verhält sich AutoISO deutlisch anders als in den anderen Modi:
in diesem Fall wählt der Benutzer sowohl die Blende, als auch die Verschlußzeit aus, und `400plus`setzt einen genauen ISO-Wert um die Szene einzufangen.
Keiner der Konfigurationsparameter beeinflußt AutoISO in diesem Modus; außerdem ist dies der einzige Modus, in dem ISO-Zwischenwerte genutzt werden.
Um die Belichtungsanpassung im M-Modus zu nutzen, benutzen Sie die `LINKS`- und `RECHTS`-Tasten während Sie durch den Sucher schauen.

# ISO in Sucher #

Wenn Sie diese Option aktivieren (auf Ja setzen) und wenn die Kamera sich zusätzlich in einem der Kreativmodi befindet, können Sie den ISO-Wert wechseln, während Sie durch den Sucher schauen; im Tv- und M-Modus wird der neue ISO-Wert zudem im Sucher angezeigt.

  * Versetzen Sie die Kamera in den M- oder Tv-Modus.
  * Schauen Sie durch den Sucher und drücken Sie den Auslöser halb durch; Sie sollten nun die aktuelle Messung sehen können (Verschlußgeschwindigkeit, Blende, etc.).
  * Drücken Sie nun die `LINKS`- und `RECHTS`-Tasten um den ISO-Wert zu verändern, oder `die `HOCH`-Taste um ihn sich nur im Sucher anzeigen zu lassen;
> der neue Wert wird im Sucher genau da angezeigt, wo ansonsten die Verschlußgeschwindigkeit, während die Taste gedrückt wird,  zu finden ist.
  * Im P- und Av-Modus kann der ISO-Wert auch verändert werden, jedoch wird diese änderung nicht im Sucher angezeigt.

**ANMERKUNG**: Falls die Custom FUnction (C.Fn.) "_01_" auf "_4_" gesetzt wurde, wird dieses Feature deaktiviert bleiben, selbst wenn es im Menü aktiviert wurde.

# Die AF-Vorlagenauswahl #

400plus biete eine Vielzahl an zusätzlichen AF-Vorlagen an Stelle der zwei (Manuelle AF-Punktauswahl und autom. Auswahl), weche die Kamera ab Werk liefert.
Diese zusätzlichen AF-Vorlagen bieten eine breite Auswahl an Mehrpunkt-Vorlagen, welche verschiedene Kombinationen der 9 Fokuspunkte, zur kreativen Verwendung der Möglichkeiten des Autofokus,  bereithalten.

Um die zusätzlichen AF-Vorlagen während des Shootings zu benutzen, drücken Sie die `ZOOM IN`-Taste um den _Standard\_dialog zur "AF-Messfeldwahl" zu öffnen und drücken Sie dann erneut die `ZOOM IN`-Taste um den neuen Dialog zur "AF-Messwahl" anzuzeigen.
Benutzen Sie die Tasten `HOCH`, `RUNTER`, `LINKS`, `RECHTS` und `SET`um sich durch die verschiedenen verfügbaren Vorlagen zu navigieren.
Drücken Sie den Auslöser halb durch um den Dialog zu verlassen._

# Die Goodies #

Die folgenden **_Goodies_** wurden der Kamera hinzugefügt um íhre Möglichkeiten zu erweitern.

## In den Motivbereichen ##

  * Benutzen Sie die `AV`-Taste um bei der Einstellung der Bildqualität zwischen `JPEG`, `RAW`, und `JPEG+RAW` zu wechseln. Beachten Sie, dass die Qualität und Bildgröße jedes Mal, wenn Sie diese Option nutzen, auf "HIGH+L" gesetzt werden.

## In den Kreativprogrammen ##

  * Im Dialog zur ISO-Wahl, drücken Sie `DP`um [AutoISO](#AutoISO.md) zu aktivieren; wählen Sie einen beliebigen ISO-Wert um es zu deaktivieren.
  * Im Dialog der Messmodusauswahl, drücken Sie `DP` um Punktmessung zu aktivieren (siehe auch [Punktmessungsmodus](#Punktmessungsmodus.md)).
  * Im Dialog für den Weißabgleich können Sie die `DP`-Taste drücken, um eine benutzerdfinierte Temperatur (in Kelvin) für den Weißabgleich zu nutzen.

# Andere Beigaben #

Weitere änderungen des Kameraverhaltens, welche oberhalb nicht behandelt wurden.

## Das Nasenproblem ##

Während man durch den Sucher schaut werden die beiden Tasten `ISO` und `WB`deaktiviert. Dies geschieht um versehentliche änderungen an den Kameraeinstellungen, die durch versehentliches drücken der Wange oder der Nase gegen den Kamerabody entstehen, zu vermeiden.

## Unterstützung für mehrere Sprachen ##

Momentan unterstützt 400plus neun (9) Sprachen:

  * Englisch
  * Finnisch
  * Französisch
  * Deutsch
  * Italienisch
  * Polnisch
  * Russisch
  * Vereinfachtes Chinesisch
  * Spanisch

Der Wunsch ist, dass 400plus möglichst viele Sprachen unterstützt!
Wenn SIe daran interessiert sind 400plus in eine andere Sprache zu übersetzen, würden wir uns über Ihre Bemühungen sehr freuen.
Lassen Sie uns davon über eine Nachfrage im Forum wissen.

# Anmerkungen #

Einige Anmerkungen und Kommentare

## Das _fehlende_ ISO-3200 ##

Vorherige Verionen von `400plus` unterstützten ISO-3200; genaugenommen _schienen_ sie es zu unterstützen:
obwohl die Kamera "3200" als ISO-Wert angezeigt hatte, wurden die Aufnahmen tatsächlich mit ISO-3000 geschossen. Die neuesten Verionen von `400plus` haben diesen Fehler behoben, weswegen nun nur noch Werde bis ISO-3000 unterstützt werden.

Beachten Sie, dass _eine Aufnahme mit dem neuen ISO-3000 exakt die gleiche ist wie zuvor mit dem alten ISO-3200_.

## Erweiterte ISOs ##

_Nicht-Standard_ ISO-Werte sind rein softwareberechnete Werte, und erzeugen technisch nur sehr wenig bis gar keinen Nutzen gegenüber der Aufnahme mit _Standad_-ISO-Werten und der späteren Bildbearbeitung der Aufnahme. Dennoch sind sie nützlich, falls man keine Zeit für eine Nachbearbeitung hat.

Bitte beachteb Sie, dass die Kamera nicht immer den korrekten ISO-Wert anzeigt; zum Beispiel wird ein mit ISO-3000 aufgenommenes Bild bei der Betrachtng mit ISO-3200 angezeigt.

## Punktmessungsmodus ##

Der Punktmessungsmodus ist dem _Standard\_modus "Selektivmessung" ähnlich, allerdings ist der Messbereich kleiner (ca. 3,5% der Mitte des Sucherbereichs im Gegensatz zu ca. 9% bei der Selektivmessung). Funktioniert gut, wenn man es benötigt._

# Bekannte Probleme #

Die folgenden Probleme wurden gemeldet und bestätigt:

  * Problem #156: Wenn AF-Vorlagen verwendet werden wird der AF-Assist Beam des 430EX nicht ausgelöst.
  * Problem #153: Das Standardmenü blitzt kurz auf, bevor das Shortcutmenü geöffnet wird.
> # Danksagung #
> Danke an [Thebi](http://chdk.setepontos.com/index.php?action=profile;u=23374) für das Korrekturlesen und die daraus resultierende Hilfe.